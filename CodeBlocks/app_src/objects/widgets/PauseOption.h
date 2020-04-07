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
    PauseOption(is::GameDisplay *scene, sf::Texture &tex);

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
    bool m_keyIsLocked;

    void step(float const &DELTA_TIME);
    void draw(sf::RenderTexture &surface);

private:
    is::GameDisplay *m_scene;
    float m_sprSFXScale, m_sprVibrateScale;
    PauseOptionType m_answer;
    sf::Sprite m_sprIcoSFX, m_sprIcoVibrate;
    sf::RectangleShape m_sprMask[4];
};

#endif // PAUSEOPTION_H_INCLUDED
