#ifndef PAUSEOPTION_H_INCLUDED
#define PAUSEOPTION_H_INCLUDED

#include "../../../isEngine/system/entity/MainObject.h"
#include "../gamelevel/HUD.h"

////////////////////////////////////////////////////////////
/// Displays widgets for sound, music, vibration options (Android only)
/// during the pause menu
////////////////////////////////////////////////////////////
class PauseOption : public is::MainObject
{
public:
    PauseOption(is::GameDisplay *scene, sf::Texture &texIcon, sf::Texture &texPad);

    ////////////////////////////////////////////////////////////
    /// \brief Enum represents a option of the pause menu
    ///
    ////////////////////////////////////////////////////////////
    enum PauseOptionType
    {
        PAUSE_OPTION_SFX,
        PAUSE_OPTION_MSC,
        PAUSE_OPTION_VIBRATE
    };
    bool m_keyIsLocked, m_useMoveAnimation, m_mouseInCollison;

    void step(float const &DELTA_TIME);
    void draw(sf::RenderTexture &surface);

private:
    is::GameDisplay *m_scene;

    float m_sprSFXScale, m_sprVibrateScale, m_pauseObjMove;
    PauseOptionType m_answer;
    sf::Sprite m_sprIcoSFX, m_sprIcoVibrate;
    sf::Sprite m_sprPad1, m_sprPad2, m_sprPad3;
    sf::RectangleShape m_recPauseBG, m_sprMask[4];
    sf::Text m_txtContinue, m_txtQuit, m_txtRestart;
};

#endif // PAUSEOPTION_H_INCLUDED
