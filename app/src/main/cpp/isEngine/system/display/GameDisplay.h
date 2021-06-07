/*
  is::Engine (Infinity Solution Engine)
  Copyright (C) 2018-2021 Is Daouda <isdaouda.n@gmail.com>

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

#ifndef GAMEDISPLAY_H_INCLUDED
#define GAMEDISPLAY_H_INCLUDED

#include "../../../app_src/gamesystem_ext/GameSystemExtended.h"
#include "../../../app_src/language/GameLanguage.h"

#if defined(IS_ENGINE_USE_SDM)
#include "SDM.h"
#else
#include "../entity/MainObject.h"
#endif // defined

#include "../sound/GSM.h"
#include "../graphic/GRM.h"

namespace is
{
#if !defined(IS_ENGINE_HTML_5)
class GameDisplay;
sf::Vector2f getMapPixelToCoords(GameDisplay const *scene, sf::Vector2i pixelPos);
#endif

//////////////////////////////////////////////////////
/// \brief Class for manage game scene
///
//////////////////////////////////////////////////////
class GameDisplay
#if defined(IS_ENGINE_USE_SDM)
    : public SDM, public GSM, public GRM
#else
    : public GSM, public GRM
#endif // defined
{
public:
    bool m_isClose;

    /*  					/!\ WARNING! /!\
     * This constructor is no longer supported in this version of the engine. Use the one below.
     *
     * GameDisplay(sf::RenderWindow &window, sf::View &view, is::Render &surface, GameSystemExtended &gameSysExt, sf::Color bgColor);
     */
    GameDisplay(GameSystemExtended &gameSysExt, sf::Color bgColor);
    virtual ~GameDisplay();

    ////////////////////////////////////////////////////////////
    /// \brief Update scene behavior
    ///
    /// When the SDM is activated and the user does not overload
    /// this function the SDM takes care of calling this method to
    /// automatically update the objects of the scene and the
    /// events of the window.
    ////////////////////////////////////////////////////////////
    virtual void step()
    #if !defined(IS_ENGINE_USE_SDM)
     = 0;
    #else
    {
        SDMmanageScene(); // Let SDM manage the scene
    }
    #endif // defined

    ////////////////////////////////////////////////////////////
    /// \brief Method to implement drawing code
    ///
    /// When the SDM is activated and the user does not overload
    /// this function the SDM takes care of calling this method to
    /// automatically draw the objects of the scene.
    ////////////////////////////////////////////////////////////
    virtual void draw()
    #if !defined(IS_ENGINE_USE_SDM)
    = 0;
    #else
    {
        SDMdraw(); // Let SDM manage the display of objects
    }
    #endif

    /// Draw scene
    virtual void drawScreen();

    /// Draw temporal loading (simulation)
    virtual void showTempLoading(float time = 3.f * is::SECOND);

    /// Allows to change an option by playing a sound and making an animation
    virtual void setOptionIndex(int optionIndexValue, bool callWhenClick, float buttonScale = 1.3f);

    /// Set option index
    virtual void setOptionIndex(int optionIndexValue);

    /// Allows to animate SFML text and sprite in relation to a option
    virtual void setTextAnimation(sf::Text &txt, sf::Sprite &spr, int val);

    /// Allows to animate SFML text in relation to a option
    virtual void setTextAnimation(sf::Text &txt, int &var, int val);

    /// Set sprButtonSelectScale
    virtual void setSprButtonSelectScale(float val);

    /// Update view position
    virtual void setView(sf::Vector2f v);

    /// Update view position
    virtual void setView(float x, float y);

    /// Update view position
    virtual void setView();

    /// Set view x variable
    virtual void setViewVarX(float val);

    /// Set view y variable
    virtual void setViewVarY(float val);

    /// Set view x and y variable
    virtual void setViewVarXY(float x, float y);

    /// Set view size
    virtual void setViewSize(sf::Vector2f v);

    /// Set view size
    virtual void setViewSize(float x, float y);

    /// Set window size
    virtual void setWindowSize(sf::Vector2u v, bool updateViewSize = false);

    /// Set window title
    virtual void setWindowTitle(const std::string &title);

    /// Set background color
    virtual void setWindowBgColor(sf::Color color);

    /// Load message box resource and fonts
    virtual void loadParentResources();

    /// Load scene resources
    virtual void loadResources() = 0;

    /// Set is running
    virtual void setIsRunning(bool val);

    /// Set is playing
    virtual void setIsPlaying(bool val);

    /// Allows access to another scene. If no scene is entered the application stops.
    virtual void quitScene(int nextScene = -1);

    /// Set scene start
    virtual void setSceneStart(bool val);

    /// Set scene end
    virtual void setSceneEnd(bool val);

    /// Set key back (CANCEL) state
    virtual void setKeyBackPressed(bool val);

    /// Check if scene is running
    virtual bool getIsRunning() const;

    /// Return m_isPlaying
    virtual bool getIsPlaying() const {return m_isPlaying;}

    /// Return scene start
    virtual bool getSceneStart() const {return m_sceneStart;}

    /// Return scene end
    virtual bool getSceneEnd() const {return m_sceneEnd;}

    /// Return window focus state
    virtual bool getWindowIsActive() const {return m_windowIsActive;}

    /// Return key back (CANCEL) state
    virtual bool getKeyBackPressed() const {return m_keyBackPressed;}

    /// Return scene view
    virtual const sf::View& getView() const noexcept {return m_view;}

    /// Return render window
    virtual sf::RenderWindow& getRenderWindow() const {return m_window;}

    /// Return render texture
    virtual is::Render& getRenderTexture() const {return m_surface;}

    /// Return game system controller
    virtual GameSystemExtended& getGameSystem() {return m_gameSysExt;}

    /// Return font system
    virtual sf::Font& getFontSystem() {return GRMgetFont("font_system");}

    /// Return font msg
    virtual sf::Font& getFontMsg() {return GRMgetFont("font_msg");}

    /// Return Button Select sprite
    virtual sf::Sprite& getSprButtonSelect() {return m_sprButtonSelect;}

    /// Return option index
    virtual int getOptionIndex() const {return m_optionIndex;}

    /// Return wait time
    virtual int getWaitTime() const {return m_waitTime;}

    /// Return scene width
    virtual unsigned int getSceneWidth() const {return m_sceneWidth;}

    /// Return scene height
    virtual unsigned int getSceneHeight() const {return m_sceneHeight;}

    /// Return vibrate time duration
    virtual short getVibrateTimeDuration() const {return m_timeVibrateDuration;}

    /// Return the delta time elapsed independent of the main rendering loop
    virtual float getDeltaTime();

    /// Return DELTA_TIME variable
    virtual float getDELTA_TIME() const {return DELTA_TIME;}

    /// Return sprButtonSelectScale variable
    virtual float& getSprButtonSelectScale() {return m_sprButtonSelectScale;}

    /// Return view X
    virtual float getViewX() const {return m_viewX;}

    /// Return view Y
    virtual float getViewY() const {return m_viewY;}

    /// Return view W
    virtual float getViewW() const {return m_viewW;}

    /// Return view H
    virtual float getViewH() const {return m_viewH;}

    /// Return Cursor Position
    virtual sf::Vector2f getCursor(
                                    #if defined(__ANDROID__)
                                    unsigned int finger = 0
                                    #endif // defined
                                   ) const;

    /// Return the scene background color
    virtual sf::Color& getBgColor() {return m_windowBgColor;}

    /// Check if the scene object is in view surface
    virtual bool inViewRec(is::MainObject *obj, bool useTexRec = true);

    //////////////////////////////////////////////////////
    /// \brief Test the collision of the SFML objects which are in the
    /// scene with the mouse cursor on PC platform / touch on mobile
    ///
    /// \param obj SFML object with which we want to test
    /// \param finger Finger index (on Android)
    //////////////////////////////////////////////////////
    template <class T>
    bool mouseCollision(T const &obj
                        #if defined(__ANDROID__)
                        , unsigned int finger = 0
                        #endif // defined
                        )
    {
        return is::mouseCollision(m_window, obj
#if defined(__ANDROID__)
                                  , finger
#endif
                                  );
    }

    //////////////////////////////////////////////////////
    /// \brief Test the collision of the SFML objects which are in the
    /// scene with the mouse cursor on PC platform / touch on mobile
    ///
    /// \param obj SFML object with which we want to test
    /// \param position Allows to get the position of the collision point
    /// \param finger Finger index (on Android)
    //////////////////////////////////////////////////////
    template <class T>
    bool mouseCollision(T const &obj, sf::Vector2f &position
                        #if defined(__ANDROID__)
                        , unsigned int finger = 0
                        #endif // defined
                        )
    {
        return is::mouseCollision(m_window, obj, position
#if defined(__ANDROID__)
                                 , finger
#endif
                                 );
    }

    #if defined(IS_ENGINE_USE_SDM)
    /// Allows to manage all the parts of the scene (event, update, display, dialog box)
    virtual void SDMmanageScene();

    /// Allows to define the way in which the SDM will manage the events
    /// To change the mechanism override this method
    virtual void SDMmanageSceneEvents()
    {
        sf::Event event;
        #if !defined(IS_ENGINE_HTML_5)
        while (m_window.pollEvent(event)) // even loop
        {
        #endif
            controlEventFocusClosing(event);
            if (
                #if !defined(IS_ENGINE_HTML_5)
                event.type == sf::Event::KeyReleased
                #else
                m_window.input().IsKeyReleased(is::GameConfig::KEY_CANCEL)
                #endif
                )
            {
                if (
                    #if !defined(IS_ENGINE_HTML_5)
                    event.key.code == is::GameConfig::KEY_CANCEL
                    #else
                    m_gameSysExt.keyIsPressed(is::GameConfig::KEY_CANCEL)
                    #endif
                    )
                {
                    if (!m_showMsg) showMessageBox(is::lang::msg_quit_game[m_gameSysExt.m_gameLanguage]);
                    else m_keyBackPressed = true;
                }
            }
        #if !defined(IS_ENGINE_HTML_5)
            SDMcallObjectsEvents(event);
        }
        #endif
    }

    /// Allows to define how the answers of the dialog box will be handled
    /// To change the mechanism override this method
    virtual void SDMmanageSceneMsgAnswers()
    {
        if (m_msgAnswer == MsgAnswer::YES) // if answers is YES close application
        {
            m_window.close();
            m_isRunning = false;
        }
        else // if answers is NO continue execution
        {
            m_waitTime = 20;
        }
    }

    /// Method to call objects events
    virtual void SDMcallObjectsEvents(sf::Event &event);

    /// Method to update scene objects
    virtual void SDMstep();

    /// Method to draw scene objects
    virtual void SDMdraw();
    #endif // defined

    /// Allows to play sound in container by his name
    virtual void GSMplaySound(const std::string& name);

    /// Allows to pause sound in container by his name
    virtual void GSMpauseSound(const std::string& name);

    /// Allows to stop sound in container by his name
    virtual void GSMstopSound(const std::string& name);

    /// Allows to play music in container by his name
    virtual void GSMplayMusic(const std::string& name);

    /// Allows to pause music in container by his name
    virtual void GSMpauseMusic(const std::string& name);

    /// Allows to stop music in container by his name
    virtual void GSMstopMusic(const std::string& name);

    /// Show message box according to type
    template<class T1>
    void showMessageBox(T1 const &msgBody, bool mbYesNo = true)
    {
        m_showMsg = true;
        m_mbYesNo = mbYesNo;
        if (m_mbYesNo) m_msgAnswer = MsgAnswer::NO;
        m_msgWaitTime = 0;
        m_msgBoxMouseInCollison = false;
        m_txtMsgBoxYes.setString(is::lang::pad_answer_yes[m_gameSysExt.m_gameLanguage]);
        m_txtMsgBoxNo.setString(is::lang::pad_answer_no[m_gameSysExt.m_gameLanguage]);
        m_txtMsgBoxOK.setString(is::lang::pad_answer_ok[m_gameSysExt.m_gameLanguage]);

        centerSFMLObj(m_txtMsgBoxYes);
        centerSFMLObj(m_txtMsgBoxNo);
        centerSFMLObj(m_txtMsgBoxOK);
        setView();
        setSFMLObjX_Y(m_recMsgBox, sf::Vector2f(m_view.getCenter().x, m_view.getCenter().y));
        setSFMLObjX_Y(m_sprMsgBox, sf::Vector2f(m_view.getCenter().x, m_view.getCenter().y));
        const float dim(6.f),
                    boxXOrigin(is::getSFMLObjOriginX(m_sprMsgBox)),
                    boxYOrigin(is::getSFMLObjOriginY(m_sprMsgBox));
        setSFMLObjX_Y(m_sprMsgBoxButton1,
                          is::getSFMLObjX(m_sprMsgBox) - boxXOrigin + is::getSFMLObjOriginX(m_sprMsgBoxButton1) + dim,
                          is::getSFMLObjY(m_sprMsgBox) + boxYOrigin - is::getSFMLObjHeight(m_sprMsgBoxButton1) + dim);
        setSFMLObjX_Y(m_sprMsgBoxButton2,
                          is::getSFMLObjX(m_sprMsgBox) + boxXOrigin - is::getSFMLObjOriginX(m_sprMsgBoxButton2) - dim,
                          is::getSFMLObjY(m_sprMsgBox) + boxYOrigin - is::getSFMLObjHeight(m_sprMsgBoxButton2) + dim);
        setSFMLObjX_Y(m_sprMsgBoxButton3,
                          is::getSFMLObjX(m_sprMsgBox),
                          is::getSFMLObjY(m_sprMsgBox) + boxYOrigin - is::getSFMLObjHeight(m_sprMsgBoxButton1) + dim);
        setSFMLObjX_Y(m_txtMsgBox,
                          is::getSFMLObjX(m_sprMsgBox)- boxXOrigin + 16.f,
                          is::getSFMLObjY(m_sprMsgBox) - boxYOrigin + 8.f);
        m_txtMsgBox.setString(msgBody);

        // Adjust the text on button
        float const adjustVal(8.f);
        setSFMLObjX_Y(m_txtMsgBoxYes, is::getSFMLObjX(m_sprMsgBoxButton1),
                          is::getSFMLObjY(m_sprMsgBoxButton1) - adjustVal);
        setSFMLObjX_Y(m_txtMsgBoxNo, is::getSFMLObjX(m_sprMsgBoxButton2),
                          is::getSFMLObjY(m_sprMsgBoxButton2) - adjustVal);
        setSFMLObjX_Y(m_txtMsgBoxOK, is::getSFMLObjX(m_sprMsgBoxButton3),
                          is::getSFMLObjY(m_sprMsgBoxButton3) - adjustVal);

        is::setSFMLObjAlpha(m_sprMsgBoxButton1, m_msgWaitTime);
        is::setSFMLObjAlpha(m_sprMsgBoxButton2, m_msgWaitTime);
        is::setSFMLObjAlpha(m_sprMsgBoxButton3, m_msgWaitTime);
        is::setSFMLObjAlpha(m_sprMsgBox, m_msgWaitTime);
        is::setSFMLObjAlpha2(m_txtMsgBoxNo, m_msgWaitTime);
        is::setSFMLObjAlpha2(m_txtMsgBoxYes, m_msgWaitTime);
        is::setSFMLObjAlpha2(m_txtMsgBoxOK, m_msgWaitTime);
        is::setSFMLObjAlpha2(m_txtMsgBox, m_msgWaitTime);
    }

    /// Allows to manage focus and closing events
    virtual void controlEventFocusClosing(sf::Event &event);

protected:
    /// Represent the answers return by message box
    enum MsgAnswer
    {
        QUIT = -1,
        YES = 1,
        NO = 0
    };

    /// Update message box components
    void updateMsgBox(int sliderDirection = 0, bool rightSideValidation = false,
                      sf::Color textDefaultColor = is::GameConfig::DEFAULT_MSG_BOX_TEXT_COLOR,
                      sf::Color selectedTextColor = is::GameConfig::DEFAULT_MSG_BOX_SELECTED_TEXT_COLOR);

    /// Update time wait
    void updateTimeWait();

    /// Show message box
    void drawMsgBox();

    sf::RenderWindow &m_window;
    sf::View m_view;

    is::Render &m_surface;
    GameSystemExtended &m_gameSysExt;

    sf::Sprite m_sprButtonSelect;
    sf::Clock m_clock;
    sf::Color m_windowBgColor;

    short const m_timeVibrateDuration; ///< Represent the time of vibration (ms)

    int m_optionIndex;
    int m_waitTime, m_msgWaitTime;
    unsigned int m_sceneWidth, m_sceneHeight;
    float DELTA_TIME;
    float m_viewW, m_viewH, m_viewX, m_viewY, m_sprButtonSelectScale;
    MsgAnswer m_msgAnswer;

    bool m_isRunning;
    bool m_windowIsActive;
    bool m_isPlaying, m_sceneStart, m_sceneEnd;
    bool m_keyBackPressed;
    bool m_showMsg, m_mbYesNo, m_msgBoxMouseInCollison;

    sf::Sprite m_sprMsgBox, m_sprMsgBoxButton1, m_sprMsgBoxButton2, m_sprMsgBoxButton3;
    sf::Sprite m_sprLoading;
    sf::Text m_txtMsgBox, m_txtMsgBoxYes, m_txtMsgBoxNo, m_txtMsgBoxOK;
    sf::RectangleShape m_recMsgBox;
};
}

#endif // GAMEDISPLAY_H_INCLUDED
