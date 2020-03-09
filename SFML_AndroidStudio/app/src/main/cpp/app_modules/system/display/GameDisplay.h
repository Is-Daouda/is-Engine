#ifndef GAMEDISPLAY_H_INCLUDED
#define GAMEDISPLAY_H_INCLUDED

#include "../../core/GameSystemExtended.h"
#include "../function/GameFunction.h"

namespace is
{
//////////////////////////////////////////////////////
/// \brief Class for manage game scene
//////////////////////////////////////////////////////
class GameDisplay
{
public:

    /// represent the state of scene
    enum DisplayOption
    {
        INTRO,
        RESTART_LEVEL,
        GAME_RESTART, // when player restart the level
        NEXT_LEVEL,
        MAIN_MENU,
        GAME_LEVEL,
        GAME_OVER,
        GAME_END_SCREEN
    };

    GameDisplay(sf::RenderWindow &window, DisplayOption &m_launchOption, GameSystemExtended &gameSysExt, sf::Color bgColor);
    virtual ~GameDisplay();

    /// update scene behavior
    virtual void step() = 0;

    /// draw scene
    virtual void drawScreen();

    /// load message box resource and fonts
    virtual bool loadParentResources();

    /// load scene resources
    virtual bool loadResources() = 0;

    /// check is scene is running
    virtual bool isRunning() const;

protected:
    /// represent the answers return by message box
    enum MsgAnswer
    {
        QUIT = -1,
        YES = 1,
        NO = 0
    };

    /// return the delta time elapsed
    float getDeltaTime();

    /// allow to manage focus and closing events
    void controlEventFocusClosing();

    /// show message box according to type
    void showMessageBox(std::string const &msgBody, bool mbYesNo = true);

    /// update message box components
    void updateMsgBox(float const &_DELTA_TIME, sf::Color textDefaultColor = sf::Color::Green, sf::Color textSelectedColor = sf::Color::White);

    /// show message box
    void drawMsgBox();

    /// allow to animate SFML text and sprite in relation to a option
    void setTextAnimation(sf::Text &txt, sf::Sprite &spr, int val);

    /// allow to animate SFML text in relation to a option
    void setTextAnimation(sf::Text &txt, int &var, int val);

    /// abstract method to implement drawing code
    virtual void draw() = 0;

    sf::RenderWindow &m_app;
    sf::View m_view;
    DisplayOption &m_launchOption;
    GameSystemExtended &m_gameSysExt;

    sf::Font m_font1, m_font2;
    sf::Sprite m_sprButtonSelect;
    sf::RectangleShape m_recTransition;
    sf::Clock m_clock;
    sf::Color m_windowBgColor;
    sf::SoundBuffer m_sbWitch, m_sbCancel, m_sbSelectOption;
    sf::Sound m_sndSwitch, m_sndCancel, m_sndSelectOption;

    sf::Event m_event;

    #if defined(__ANDROID__)
    // represent the time of vibration (ms) on Android
    short const m_vibrateTimeDuration;
    #endif // defined

    int m_optionIndex;
    int m_alphaRec, m_waitTime, m_msgWaitTime;
    float const VIEW_W, VIEW_H;
    float m_viewX, m_viewY, m_sprButtonSelectScale;
    MsgAnswer m_msgAnswer;

    bool m_isRunning;
    bool m_appIsActive;
    bool m_keyBackPressed;
    bool m_showMsg, m_mbYesNo, m_msgBoxMouseInCollison;

private:
    sf::Texture m_texMsgBox, m_sprMsgButton;
    sf::Sprite m_sprMsgBox, m_sprMsgBoxButton1, m_sprMsgBoxButton2, m_sprMsgBoxButton3;
    sf::Text m_txtMsgBox, m_txtMsgBoxYes, m_txtMsgBoxNo, m_txtMsgBoxOK;
    sf::RectangleShape m_recMsgBox;
};
}

#endif // GAMEDISPLAY_H_INCLUDED
