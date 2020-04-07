#ifndef GAMEDISPLAY_H_INCLUDED
#define GAMEDISPLAY_H_INCLUDED

#include "../function/GameFunction.h"
#include "../../../app_src/gamesystem_ext/GameSystemExtended.h"
#include "../../../app_src/language/GameLanguage.h"

#if defined(__ANDROID__)
#if defined(IS_ENGINE_USE_ADMOB)
#include "../android/AdmobManager.h"
#endif
#endif // defined

namespace is
{
//////////////////////////////////////////////////////
/// \brief Class for manage game scene
///
//////////////////////////////////////////////////////
class GameDisplay;

sf::Vector2f getMapPixelToCoords(GameDisplay const *scene, sf::Vector2i pixelPos);

class GameDisplay
{
public:
    bool m_isClose;

    GameDisplay(sf::RenderWindow &window, sf::View &view, sf::RenderTexture &surface, GameSystemExtended &gameSysExt, sf::Color bgColor);
    virtual ~GameDisplay();

#if defined(__ANDROID__)
#if defined(IS_ENGINE_USE_ADMOB)
    virtual void setAdmob(AdmobManager *admob)
    {
        m_admobManager = admob;
    }

    ////////////////////////////////////////////////////////////
    /// \brief Display the reward video ads (run only when the request is successful)
    ///
    /// \return 1 if the reward video has been read correctly 0 if not
    ////////////////////////////////////////////////////////////
    virtual int rewardVideoStep()
    {
        int result(0);
        if (checkAdState(firebase::admob::rewarded_video::LoadAdLastResult()))
        {
            bool stopGameTread(true);
            firebase::admob::rewarded_video::Show(m_admobManager->m_activity->clazz);
            showTempLoading();

            if (checkAdState(firebase::admob::rewarded_video::ShowLastResult()))
            {
                while (stopGameTread)
                {
                    float dTime = getDeltaTime();
                    if (firebase::admob::rewarded_video::presentation_state() ==
                        firebase::admob::rewarded_video::kPresentationStateHidden)
                        stopGameTread = false;
                    sf::Event ev;
                    while (m_window.pollEvent(ev))
                    {
                        if (ev.type == sf::Event::Closed)
                        {
                            m_window.close();
                            std::terminate();
                        }
                    }
                    m_window.clear(sf::Color::Black);
                    m_window.display();
                }

                // End of video
                result = 1;
                m_admobManager->checkAdRewardObjReinitialize();
            }
        }
        else m_admobManager->loadRewardVideo();
        return result;
    }
#endif // definded
#endif // defined

    /// Update scene behavior
    virtual void step() = 0;

    /// Draw scene
    virtual void drawScreen();

    /// Draw temporal loading (simulation)
    virtual void showTempLoading(float time = 3.f * 59.f);

    /// Load message box resource and fonts
    virtual bool loadParentResources();

    /// Load scene resources
    virtual bool loadResources() = 0;

    /// Check is scene is running
    virtual bool isRunning() const;

    /// Return scene view
    virtual sf::View& getView() const {return m_view;}

    /// Return render window
    virtual sf::RenderWindow& getRenderWindow() const {return m_window;}

    /// Return render texture
    virtual sf::RenderTexture& getRenderTexture() const {return m_surface;}

    /// Return game system controller
    virtual GameSystemExtended& getGameSystem() {return m_gameSysExt;}

    /// Return Cancel sound
    virtual sf::Sound& getSndCancel() {return m_sndCancel;}

    /// Return Switch sound
    virtual sf::Sound& getSndSwitch() {return m_sndSwitch;}

    /// Return SelectOption sound
    virtual sf::Sound& getSndSelectOption() {return m_sndSelectOption;}

    /// Return the delta time elapsed independent of the main rendering loop
    float getDeltaTime();

    /// Return view X
    virtual float getViewX() const {return m_viewX;}

    /// Return view Y
    virtual float getViewY() const {return m_viewY;}

    /// Return view W
    virtual float getViewW() const {return m_viewW;}

    /// Return view H
    virtual float getViewH() const {return m_viewH;}

    /// Return the scene background color
    virtual sf::Color& getBgColor() {return m_windowBgColor;}

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
        // A rectangle that will allow to test with the SFML object
        sf::RectangleShape cursor(sf::Vector2f(3.f, 3.f));
        is::centerSFMLObj(cursor);

        #if defined(__ANDROID__)
        sf::Vector2i pixelPos = sf::Touch::getPosition(finger, m_window);
        #else
        sf::Vector2i pixelPos = sf::Mouse::getPosition(m_window);
        #endif // defined

        sf::Vector2f worldPos = getMapPixelToCoords(this, pixelPos);
        float dx = pointDistance(m_viewX, m_viewY, worldPos.x, m_viewY);
        float dy = pointDistance(m_viewX, m_viewY, m_viewX, worldPos.y);

        if (worldPos.x < m_viewX) dx *= -1;
        if (worldPos.y < m_viewY) dy *= -1;

        is::setSFMLObjX_Y(cursor, m_viewX + dx, m_viewY + dy);
        if (obj.getGlobalBounds().intersects(cursor.getGlobalBounds())) return true;
        else return false;
    }

    //////////////////////////////////////////////////////
    /// \brief Test the collision of the SFML objects which are in the
    /// scene with the mouse cursor on PC platform / touch on mobile
    ///
    /// \param obj SFML object with which we want to test
    /// \param cursor Allows to get the position of the collision point
    /// \param finger Finger index (on Android)
    //////////////////////////////////////////////////////
    template <class T>
    bool mouseCollision(T const &obj, sf::RectangleShape &cursor
                        #if defined(__ANDROID__)
                        , unsigned int finger = 0
                        #endif // defined
                        )
    {
        // A rectangle that will allow to test with the SFML object
        // If size is empty set default value
        if (static_cast<int>(is::getSFMLObjWidth(cursor)) == 0 && static_cast<int>(is::getSFMLObjHeight(cursor)) == 0)
            is::setSFMLObjSize(cursor, sf::Vector2f(3.f, 3.f));
        is::centerSFMLObj(cursor);

        #if defined(__ANDROID__)
        sf::Vector2i pixelPos = sf::Touch::getPosition(finger, m_window);
        #else
        sf::Vector2i pixelPos = sf::Mouse::getPosition(m_window);
        #endif // defined

        sf::Vector2f worldPos = getMapPixelToCoords(this, pixelPos);
        float dx = pointDistance(m_viewX, m_viewY, worldPos.x, m_viewY);
        float dy = pointDistance(m_viewX, m_viewY, m_viewX, worldPos.y);

        if (worldPos.x < m_viewX) dx *= -1;
        if (worldPos.y < m_viewY) dy *= -1;

        is::setSFMLObjX_Y(cursor, m_viewX + dx, m_viewY + dy);
        if (obj.getGlobalBounds().intersects(cursor.getGlobalBounds())) return true;
        else return false;
    }
protected:
    /// Represent the answers return by message box
    enum MsgAnswer
    {
        QUIT = -1,
        YES = 1,
        NO = 0
    };

    /// Allows to manage focus and closing events
    void controlEventFocusClosing();

    /// Show message box according to type
    template<class T>
    void showMessageBox(T const &msgBody, bool mbYesNo = true)
    {
        m_showMsg = true;
        m_mbYesNo = mbYesNo;
        if (m_mbYesNo) m_msgAnswer = MsgAnswer::NO;
        m_msgWaitTime = 0;
        m_msgBoxMouseInCollison = false;
        m_txtMsgBoxYes.setString(is::lang::pad_answer_yes[m_gameSysExt.m_gameLanguage]);
        m_txtMsgBoxNo.setString(is::lang::pad_answer_no[m_gameSysExt.m_gameLanguage]);
        m_txtMsgBoxOK.setString(is::lang::pad_answer_ok[m_gameSysExt.m_gameLanguage]);

        is::centerSFMLObj(m_txtMsgBoxYes);
        is::centerSFMLObj(m_txtMsgBoxNo);
        is::centerSFMLObj(m_txtMsgBoxOK);

        is::setSFMLObjX_Y(m_recMsgBox, sf::Vector2f(m_view.getCenter().x, m_view.getCenter().y));
        is::setSFMLObjX_Y(m_sprMsgBox, sf::Vector2f(m_view.getCenter().x, m_view.getCenter().y));
        const float dim(6.f),
                    boxXOrigin(is::getSFMLObjOriginX(m_sprMsgBox)),
                    boxYOrigin(is::getSFMLObjOriginY(m_sprMsgBox));
        is::setSFMLObjX_Y(m_sprMsgBoxButton1,
                          is::getSFMLObjX(m_sprMsgBox) - boxXOrigin + is::getSFMLObjOriginX(m_sprMsgBoxButton1) + dim,
                          is::getSFMLObjY(m_sprMsgBox) + boxYOrigin - is::getSFMLObjHeight(m_sprMsgBoxButton1) + dim);
        is::setSFMLObjX_Y(m_sprMsgBoxButton2,
                          is::getSFMLObjX(m_sprMsgBox) + boxXOrigin - is::getSFMLObjOriginX(m_sprMsgBoxButton2) - dim,
                          is::getSFMLObjY(m_sprMsgBox) + boxYOrigin - is::getSFMLObjHeight(m_sprMsgBoxButton2) + dim);
        is::setSFMLObjX_Y(m_sprMsgBoxButton3,
                          is::getSFMLObjX(m_sprMsgBox),
                          is::getSFMLObjY(m_sprMsgBox) + boxYOrigin - is::getSFMLObjHeight(m_sprMsgBoxButton1) + dim);
        is::setSFMLObjX_Y(m_txtMsgBox,
                          is::getSFMLObjX(m_sprMsgBox)- boxXOrigin + 16.f,
                          is::getSFMLObjY(m_sprMsgBox) - boxYOrigin + 8.f);
        m_txtMsgBox.setString(msgBody);

        // Adjust the text on button
        float const adjustVal(8.f);
        is::setSFMLObjX_Y(m_txtMsgBoxYes, is::getSFMLObjX(m_sprMsgBoxButton1),
                          is::getSFMLObjY(m_sprMsgBoxButton1) - adjustVal);
        is::setSFMLObjX_Y(m_txtMsgBoxNo, is::getSFMLObjX(m_sprMsgBoxButton2),
                          is::getSFMLObjY(m_sprMsgBoxButton2) - adjustVal);
        is::setSFMLObjX_Y(m_txtMsgBoxOK, is::getSFMLObjX(m_sprMsgBoxButton3),
                          is::getSFMLObjY(m_sprMsgBoxButton3) - adjustVal);

        is::setSFMLObjAlpha(m_sprMsgBoxButton1, m_msgWaitTime);
        is::setSFMLObjAlpha(m_sprMsgBoxButton2, m_msgWaitTime);
        is::setSFMLObjAlpha(m_sprMsgBoxButton3, m_msgWaitTime);
        is::setSFMLObjAlpha(m_sprMsgBox, m_msgWaitTime);
        is::setSFMLObjAlpha2(m_txtMsgBoxNo, m_msgWaitTime);
        is::setSFMLObjAlpha2(m_txtMsgBoxYes, m_msgWaitTime);
        is::setSFMLObjAlpha2(m_txtMsgBoxOK, m_msgWaitTime);
        is::setSFMLObjAlpha2(m_txtMsgBox, m_msgWaitTime);

        setView();
    }

    /// Update message box components
    void updateMsgBox(float const &DELTA_TIME, sf::Color textDefaultColor = sf::Color::White, sf::Color textSelectedColor = sf::Color::Red);

    /// Update time wait
    void updateTimeWait(float const &DELTA_TIME);

    /// Show message box
    void drawMsgBox();

    /// Allows to change an option by playing a sound and making an animation
    void setOptionIndex(int optionIndexValue, bool callWhenClick, float buttonScale = 1.3f);

    /// Allows to animate SFML text and sprite in relation to a option
    void setTextAnimation(sf::Text &txt, sf::Sprite &spr, int val);

    /// Allows to animate SFML text in relation to a option
    void setTextAnimation(sf::Text &txt, int &var, int val);

    /// Update view position
    void setView();

    /// Abstract method to implement drawing code
    virtual void draw() = 0;

    sf::RenderWindow &m_window;
    sf::View &m_view;

    sf::RenderTexture &m_surface;
    GameSystemExtended &m_gameSysExt;

    sf::Font m_fontSystem, m_fontMsg;
    sf::Sprite m_sprButtonSelect;
    sf::Clock m_clock;
    sf::Color m_windowBgColor;
    sf::SoundBuffer m_sbSwitch, m_sbCancel, m_sbSelectOption;
    sf::Sound m_sndSwitch, m_sndCancel, m_sndSelectOption;

    sf::Event m_event;

    short const m_vibrateTimeDuration; ///< Represent the time of vibration (ms)

    int m_optionIndex;
    int m_waitTime, m_msgWaitTime;
    float DELTA_TIME;
    float m_viewW, m_viewH, m_viewX, m_viewY, m_sprButtonSelectScale;
    MsgAnswer m_msgAnswer;

    bool m_isRunning;
    bool m_windowIsActive;
    bool m_keyBackPressed;
    bool m_showMsg, m_mbYesNo, m_msgBoxMouseInCollison;

    sf::Texture m_texMsgBox, m_sprMsgButton;
    sf::Sprite m_sprMsgBox, m_sprMsgBoxButton1, m_sprMsgBoxButton2, m_sprMsgBoxButton3;
    sf::Text m_txtMsgBox, m_txtMsgBoxYes, m_txtMsgBoxNo, m_txtMsgBoxOK;
    sf::RectangleShape m_recMsgBox, m_recCursor;

#if defined(__ANDROID__)
#if defined(IS_ENGINE_USE_ADMOB)
    AdmobManager *m_admobManager;
#endif // defined
#endif // defined
};

//////////////////////////////////////////////////////
/// \brief Test the collision of the SFML objects
/// with the mouse cursor on PC platform / touch on mobile
///
/// \param obj SFML object with which we want to test
/// \param finger Finger index (on Android)
//////////////////////////////////////////////////////
template <class T>
bool mouseCollision(sf::RenderWindow &window, T const &obj
                    #if defined(__ANDROID__)
                    , unsigned int finger = 0
                    #endif // defined
                    )
{
    // A rectangle that will allow to test with the SFML object
    sf::RectangleShape cursor(sf::Vector2f(3.f, 3.f));
    is::centerSFMLObj(cursor);

    #if defined(__ANDROID__)
    sf::Vector2i pixelPos = sf::Touch::getPosition(finger, window);
    #else
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    #endif // defined

    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, window.getView());
    float dx = pointDistance(window.getView().getCenter().x, window.getView().getCenter().y,
                             worldPos.x, window.getView().getCenter().y);
    float dy = pointDistance(window.getView().getCenter().x, window.getView().getCenter().y,
                             window.getView().getCenter().x, worldPos.y);

    if (worldPos.x < window.getView().getCenter().x) dx *= -1;
    if (worldPos.y < window.getView().getCenter().y) dy *= -1;

    is::setSFMLObjX_Y(cursor, window.getView().getCenter().x + dx, window.getView().getCenter().y + dy);
    if (obj.getGlobalBounds().intersects(cursor.getGlobalBounds())) return true;
    else return false;
}

//////////////////////////////////////////////////////
/// \brief Test the collision of the SFML objects which are in the
/// scene with the mouse cursor on PC platform / touch on mobile
///
/// This function is used when the test is done outside the
/// scene concerned
/// \param obj SFML object with which we want to test
/// \param cursor Allows to get the position of the collision point
/// \param finger Finger index (on Android)
//////////////////////////////////////////////////////
template <class T>
bool mouseCollision(sf::RenderWindow &window, T const &obj, sf::RectangleShape &cursor
                    #if defined(__ANDROID__)
                    , unsigned int finger = 0
                    #endif // defined
                    )
{
    // A rectangle that will allow to test with the SFML object
    // If size is empty set default value
    if (static_cast<int>(is::getSFMLObjWidth(cursor)) == 0 && static_cast<int>(is::getSFMLObjHeight(cursor)) == 0)
        is::setSFMLObjSize(cursor, sf::Vector2f(3.f, 3.f));
    is::centerSFMLObj(cursor);

    #if defined(__ANDROID__)
    sf::Vector2i pixelPos = sf::Touch::getPosition(finger, window);
    #else
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    #endif // defined

    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, window.getView());
    float dx = pointDistance(window.getView().getCenter().x, window.getView().getCenter().y,
                             worldPos.x, window.getView().getCenter().y);
    float dy = pointDistance(window.getView().getCenter().x, window.getView().getCenter().y,
                             window.getView().getCenter().x, worldPos.y);

    if (worldPos.x < window.getView().getCenter().x) dx *= -1;
    if (worldPos.y < window.getView().getCenter().y) dy *= -1;

    is::setSFMLObjX_Y(cursor, window.getView().getCenter().x + dx, window.getView().getCenter().y + dy);
    if (obj.getGlobalBounds().intersects(cursor.getGlobalBounds())) return true;
    else return false;
}
}

#endif // GAMEDISPLAY_H_INCLUDED
