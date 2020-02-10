#ifndef ADMOBMANAGER_H_INCLUDED
#define ADMOBMANAGER_H_INCLUDED

#include "firebase/admob.h"
#include "firebase/admob/types.h"
#include "firebase/app.h"
#include "firebase/future.h"
#include "firebase/admob/banner_view.h"
#include <android/native_activity.h>

static bool ProcessEvents(int msec)
{
    sf::Time _msec = sf::milliseconds(msec);
    sf::sleep(_msec);
    return true;
}

/// check ad object state
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

class AdmobManager
{
private:
    // The AdMob app IDs for the test app.
    const char* kAdMobAppID = "ca-app-pub-3940256099942544~3347511713";

    // These ad units IDs have been created specifically for testing, and will
    // always return test ads.
    const char* kBannerAdUnit = "ca-app-pub-3940256099942544/6300978111";
    const char* kInterstitialAdUnit = "ca-app-pub-3940256099942544/1033173712";
    //const char* kRewardedVideoAdUnit = "ca-app-pub-3940256099942544/2888167318";

    // Standard mobile banner size is 320x50.
    static const int kBannerWidth = 320;
    static const int kBannerHeight = 32;

    // Sample birthday value to use in making the request.
    static const int kBirthdayDay = 1;
    static const int kBirthdayMonth = 1;
    static const int kBirthdayYear = 1990;

public:
    firebase::App* app;
    firebase::admob::AdRequest request;
    firebase::admob::BannerView* banner;
    firebase::admob::InterstitialAd* interstitial;
    sf::RenderWindow &m_app;
    bool m_changeBannerPos, m_showBanner;

    ~AdmobManager()
    {
        delete banner;
        delete interstitial;
        firebase::admob::Terminate();
        delete app;
    }

    AdmobManager(sf::RenderWindow &m_app, ANativeActivity* activity, JNIEnv* env, JavaVM* vm) :
            m_app(m_app),
            m_changeBannerPos(false),
            m_showBanner(false)
    {
        app = ::firebase::App::Create(firebase::AppOptions(), env, activity->clazz);
        firebase::admob::Initialize(*app, kAdMobAppID);

        // If the app is aware of the user's gender, it can be added to the targeting
        // information. Otherwise, "unknown" should be used.
        request.gender = firebase::admob::kGenderUnknown;

        // This value allows publishers to specify whether they would like the request
        // to be treated as child-directed for purposes of the Children’s Online
        // Privacy Protection Act (COPPA).
        // See http://business.ftc.gov/privacy-and-security/childrens-privacy.
        request.tagged_for_child_directed_treatment = firebase::admob::kChildDirectedTreatmentStateTagged;

        // The user's birthday, if known. Note that months are indexed from one.
        request.birthday_day = kBirthdayDay;
        request.birthday_month = kBirthdayMonth;
        request.birthday_year = kBirthdayYear;

        // Sample keywords to use in making the request.
        static const char* kKeywords[] = {"Football", "Game", "Music", "Applications"};

        // Sample test device IDs to use in making the request.
        static const char* kTestDeviceIDs[] = {"2077ef9a63d2b398840261c8221a0c9b",
                                               "098fe087d987c9a878965454a65654d7"};

        // Additional keywords to be used in targeting.
        request.keyword_count = sizeof(kKeywords) / sizeof(kKeywords[0]);
        request.keywords = kKeywords;

        // "Extra" key value pairs can be added to the request as well. Typically
        // these are used when testing new features.
        static const firebase::admob::KeyValuePair kRequestExtras[] = {{"the_name_of_an_extra", "the_value_for_that_extra"}};
        request.extras_count = sizeof(kRequestExtras) / sizeof(kRequestExtras[0]);
        request.extras = kRequestExtras;

        // This example uses ad units that are specially configured to return test ads
        // for every request. When using your own ad unit IDs, however, it's important
        // to register the device IDs associated with any devices that will be used to
        // test the app. This ensures that regardless of the ad unit ID, those
        // devices will always m_receive test ads in compliance with AdMob policy.
        //
        // Device IDs can be obtained by checking the logcat or the Xcode log while
        // debugging. They appear as a long string of hex characters.
        request.test_device_id_count = sizeof(kTestDeviceIDs) / sizeof(kTestDeviceIDs[0]);
        request.test_device_ids = kTestDeviceIDs;

        // Create an ad size for the BannerView.
        firebase::admob::AdSize banner_ad_size;
        banner_ad_size.ad_size_type = firebase::admob::kAdSizeStandard;
        banner_ad_size.width = kBannerWidth;
        banner_ad_size.height = kBannerHeight;

        banner = new firebase::admob::BannerView();
        banner->Initialize(activity->clazz, kBannerAdUnit, banner_ad_size);

        interstitial = new firebase::admob::InterstitialAd();
        interstitial->Initialize(activity->clazz, kInterstitialAdUnit);
    }

    void loadBannerAd()
    {
        if (checkAdState(banner->InitializeLastResult()))
        {
            banner->LoadAd(request);
        }
    };

    void showBannerAd()
    {
        if (checkAdState(banner->LoadAdLastResult()))
        {
            if (!checkAdState(banner->ShowLastResult()) || checkAdState(banner->HideLastResult()))
            {
                if (!m_showBanner)
                {
                    if (!m_changeBannerPos)
                    {
                        banner->MoveTo(firebase::admob::BannerView::kPositionTop);
                        m_changeBannerPos = true;
                    }
                    banner->Show();
                    WaitForFutureCompletion(banner->ShowLastResult());
                    m_showBanner = true;
                }
            }
        }
    };

    void hideBannerAd()
    {
        if (checkAdState(banner->LoadAdLastResult()))
        {
            m_showBanner = false;
            banner->Hide();
        }
    };

    void loadInterstitialAd()
    {
        if (checkAdState(interstitial->InitializeLastResult()))
            interstitial->LoadAd(request);
    };

    auto updateSFMLApp(bool whiteColor)
    {
        sf::Event m_event;
        while (m_app.pollEvent(m_event));
        m_app.clear((whiteColor) ? sf::Color::White : sf::Color::Black);
        m_app.display();
    };

    void showInterstitialAd()
    {
        if (checkAdState(interstitial->LoadAdLastResult()))
        {
            bool reloadItAd(false);
            interstitial->Show();
            WaitForFutureCompletion(interstitial->ShowLastResult());
            while (interstitial->presentation_state() !=
                   firebase::admob::InterstitialAd::PresentationState::kPresentationStateHidden) {
                reloadItAd = true;
                updateSFMLApp(false);
            }
            if (reloadItAd) interstitial->LoadAd(request);
        }
    };

    void checkAdObjInit()
    {
        while (!checkAdState(banner->InitializeLastResult()) && !checkAdState(interstitial->InitializeLastResult()))
        {
            updateSFMLApp(true);
        }
    }
};

#endif // ADMOBMANAGER_H_INCLUDED
