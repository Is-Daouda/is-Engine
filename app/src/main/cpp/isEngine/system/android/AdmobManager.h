/*
  is::Engine (Infinity Solutions Engine)
  Copyright (C) 2018-2022 Is Daouda <isdaouda.n@gmail.com>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef ADMOBMANAGER_H_INCLUDED
#define ADMOBMANAGER_H_INCLUDED

#include "../function/GameFunction.h"
#include "../../../app_src/config/GameConfig.h"

#if defined(__ANDROID__)
#if defined(IS_ENGINE_USE_ADMOB)
#include "firebase/admob.h"
#include "firebase/admob/types.h"
#include "firebase/app.h"
#include "firebase/future.h"
#include "firebase/admob/banner_view.h"
#include "firebase/admob/rewarded_video.h"
#include <android/native_activity.h>

using namespace is::GameConfig::AdmobConfig;

static bool ProcessEvents(int msec)
{
    sf::Time _msec = sf::milliseconds(msec);
    sf::sleep(_msec);
    return true;
}

/// Check ad object state
static bool checkAdState(firebase::FutureBase future)
{
    return (future.status() == firebase::kFutureStatusComplete &&
            future.error() == firebase::admob::kAdMobErrorNone);
}

static void WaitForFutureCompletion(firebase::FutureBase future)
{
    while (!ProcessEvents(1000))
    {
        if (future.status() != firebase::kFutureStatusPending) break;
    }
    if (future.error() != firebase::admob::kAdMobErrorNone)
    {
        is::showLog("ERROR: Action failed with error code " + is::numToStr(future.error()) +
                    " and message : " + future.error_message());
    }
}

////////////////////////////////////////////////////////////
/// \brief Class to manage ad components
///
////////////////////////////////////////////////////////////
class AdmobManager
{
public:
    firebase::App *m_admobApp = nullptr;
    firebase::admob::AdRequest m_request;
    firebase::admob::BannerView *m_banner = nullptr;
    ANativeActivity* m_activity;
    sf::RenderWindow &m_window;
    bool m_changeBannerPos;
    bool m_showBanner;
    bool m_showRewardVideo;
    bool m_relaunchAd;

    ~AdmobManager()
    {
        delete m_admobApp;
        delete m_banner;
        firebase::admob::rewarded_video::Destroy();
        firebase::admob::Terminate();
    }

    AdmobManager(sf::RenderWindow &window, ANativeActivity* activity, JNIEnv* env) :
            m_activity(activity),
            m_window(window),
            m_changeBannerPos(false),
            m_showBanner(false),
            m_showRewardVideo(false),
            m_relaunchAd(false)
    {
        m_admobApp = ::firebase::App::Create(firebase::AppOptions(), env, m_activity);
        firebase::admob::Initialize(*m_admobApp, kAdMobAppID);

        // If the app is aware of the user's gender, it can be added to the targeting
        // information. Otherwise, "unknown" should be used.
        m_request.gender = firebase::admob::kGenderUnknown;

        // This value allows publishers to specify whether they would like the request
        // to be treated as child-directed for purposes of the Children’s Online
        // Privacy Protection Act (COPPA).
        // See http://business.ftc.gov/privacy-and-security/childrens-privacy.
        m_request.tagged_for_child_directed_treatment = firebase::admob::kChildDirectedTreatmentStateTagged;

        // The user's birthday, if known. Note that months are indexed from one.
        m_request.birthday_day = kBirthdayDay;
        m_request.birthday_month = kBirthdayMonth;
        m_request.birthday_year = kBirthdayYear;

        // Sample test device IDs to use in making the request.
        static const char* kTestDeviceIDs[] = {"2077ef9a63d2b398840261c8221a0c9b",
                                               "098fe087d987c9a878965454a65654d7"};

        // Additional keywords to be used in targeting.
        m_request.keyword_count = sizeof(kKeywords) / sizeof(kKeywords[0]);
        m_request.keywords = kKeywords;

        // "Extra" key value pairs can be added to the request as well. Typically
        // these are used when testing new features.
        static const firebase::admob::KeyValuePair kRequestExtras[] = {{"the_name_of_an_extra", "the_value_for_that_extra"}};
        m_request.extras_count = sizeof(kRequestExtras) / sizeof(kRequestExtras[0]);
        m_request.extras = kRequestExtras;

        // This example uses ad units that are specially configured to return test ads
        // for every request. When using your own ad unit IDs, however, it's important
        // to register the device IDs associated with any devices that will be used to
        // test the app. This ensures that regardless of the ad unit ID, those
        // devices will always m_receive test ads in compliance with AdMob policy.
        //
        // Device IDs can be obtained by checking the logcat or the Xcode log while
        // debugging. They appear as a long string of hex characters.
        m_request.test_device_id_count = sizeof(kTestDeviceIDs) / sizeof(kTestDeviceIDs[0]);
        m_request.test_device_ids = kTestDeviceIDs;

        // Create an ad size for the BannerView.
        firebase::admob::AdSize banner_ad_size;
        banner_ad_size.ad_size_type = firebase::admob::kAdSizeStandard;
        banner_ad_size.width = kBannerWidth;
        banner_ad_size.height = kBannerHeight;

        m_banner = new firebase::admob::BannerView();
        m_banner->Initialize(m_activity, kBannerAdUnit, banner_ad_size);

        firebase::admob::rewarded_video::Initialize();
    }

    /// Make a request to have ads that will be displayed in the ad banner
    void loadBannerAd()
    {
        if (checkAdState(m_banner->InitializeLastResult()))
        {
            m_banner->LoadAd(m_request);
        }
    };

    /// Display the ad banner (run only when the request is successful)
    void showBannerAd()
    {
        if (checkAdState(m_banner->LoadAdLastResult()))
        {
            if (!checkAdState(m_banner->ShowLastResult()) || checkAdState(m_banner->HideLastResult()))
            {
                if (!m_showBanner)
                {
                    if (!m_changeBannerPos)
                    {
                        m_changeBannerPos = true;
                    }
                    m_banner->Show();
                    WaitForFutureCompletion(m_banner->ShowLastResult());
                    m_showBanner = true;
                }
            }
            m_relaunchAd = false;
        }
        else m_relaunchAd = true;
    };

    /// Hide ad banner
    void hideBannerAd()
    {
        if (checkAdState(m_banner->LoadAdLastResult()))
        {
            m_showBanner = false;
            m_banner->Hide();
        }
    };

    /// Make a request to have ads that will be displayed in the reward video
    void loadRewardVideo()
    {
        if (checkAdState(firebase::admob::rewarded_video::InitializeLastResult()))
        {
            firebase::admob::rewarded_video::LoadAd(kRewardedVideoAdUnit, m_request);
        }
    };

    ////////////////////////////////////////////////////////////
    /// \brief Display the reward video ads (run only when the request is successful)
    ///
    /// \return 1 if the reward video has been read correctly 0 if not
    ////////////////////////////////////////////////////////////
    virtual int showRewardVideo()
    {
        int result(0);
        if (checkAdState(firebase::admob::rewarded_video::LoadAdLastResult()))
        {
            sf::Clock clock;
            bool stopGameTread(true);
            firebase::admob::rewarded_video::Show(m_activity);

            if (checkAdState(firebase::admob::rewarded_video::ShowLastResult()))
            {
                while (stopGameTread)
                {
                    float dTime = clock.restart().asSeconds();
                    if (dTime > is::MAX_CLOCK_TIME) dTime = is::MAX_CLOCK_TIME;

                    if (firebase::admob::rewarded_video::presentation_state() ==
                        firebase::admob::rewarded_video::kPresentationStateHidden) stopGameTread = false;

                    sf::Event ev;
                    while (m_window.pollEvent(ev))
                    {
                        if (ev.type == sf::Event::Closed) is::closeApplication();
                    }
                    m_window.clear(sf::Color::Black);
                    m_window.display();
                }

                // End of the video
                result = 1;
                checkAdRewardObjReinitialize();
            }
        }
        else loadRewardVideo();
        return result;
    }

    ////////////////////////////////////////////////////////////
    /// This function allows to avoid the loss of the window handle
    /// when the ad components are used because they use a different
    /// rendering loop from that of the engine
    ///
    /// \param whiteColor true displays white and false display black background color
    ////////////////////////////////////////////////////////////
    auto updateSFMLApp(bool whiteColor)
    {
        sf::Event m_event;
        while (m_window.pollEvent(m_event));
        m_window.clear((whiteColor) ? sf::Color::White : sf::Color::Black);
        m_window.display();
    };

    /// Check if ad components are initialized
    void checkAdObjInit()
    {
        while (!checkAdState(m_banner->InitializeLastResult()) &&
                !checkAdState(firebase::admob::rewarded_video::InitializeLastResult())
                )
        {
            updateSFMLApp(true);
        }
    }

    /// Reinitialize ad components
    void checkAdRewardObjReinitialize()
    {
        firebase::admob::rewarded_video::Destroy();
        firebase::admob::rewarded_video::Initialize();
        while (!checkAdState(firebase::admob::rewarded_video::InitializeLastResult())) updateSFMLApp(true);
        loadRewardVideo();
    }
};
#endif
#endif
#endif // ADMOBMANAGER_H_INCLUDED
