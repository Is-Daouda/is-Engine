#ifndef GAMEKEYDATA_H_INCLUDED
#define GAMEKEYDATA_H_INCLUDED

#include "../entity/MainObject.h"

//////////////////////////////////////////////////////
/// \brief Class for manage game command
/// (Keyboard / Virtual Game Pad for Android)
///
//////////////////////////////////////////////////////
class GameKeyData : public is::MainObject
{
public:
    //////////////////////////////////////////////////////
    /// \brief Represent game command key
    ///
    //////////////////////////////////////////////////////
    enum VirtualKeyIndex
    {
        V_KEY_LEFT,  ///< Represents the Left directional button
        V_KEY_RIGHT, ///< Represents the Right directional button
        V_KEY_UP,    ///< Represents the Up directional button
        V_KEY_DOWN,  ///< Represents the Down directional button
        V_KEY_A,     ///< Represents the A button
        V_KEY_B,     ///< Represents the B button
        V_KEY_NONE   ///< Represents no button press
    };

    bool m_keyPausePressed,
         m_keyLeftPressed,
         m_keyRightPressed,
         m_keyUpPressed,
         m_keyDownPressed,
         m_keyAPressed,
         m_keyBPressed,
         m_keyAUsed,
         m_keyBUsed,
         m_disableAllKey,
         m_hideGamePad;

    sf::Keyboard::Key m_keyboardA,
        m_keyboardB,
        m_keyboardLeft,
        m_keyboardRight,
        m_keyboardUp,
        m_keyboardDown;

    VirtualKeyIndex m_moveKeyPressed,   ///< Used to find out whether a directional key is pressed
                    m_actionKeyPressed; ///< Used to find out whether a action key (A or B) is pressed

    GameKeyData(is::GameDisplay *scene);

    /// Load the image that will serve as Virtual Game Pad (only for Android)
    void loadResources(sf::Texture &tex);

    /// Manages the positioning of the Virtual Game Pad relative to the screen (only for Android)
    void step(float const &DELTA_TIME);

    /// Draw the Virtual Game Pad on the screen (only for Android)
    void draw(sf::RenderTexture &surface);

    /// Check if the Left directional button is pressed
    bool keyLeftPressed();

    /// Check if the Right directional button is pressed
    bool keyRightPressed();

    /// Check if the Up directional button is pressed
    bool keyUpPressed();

    /// Check if the Down directional button is pressed
    bool keyDownPressed();

    /// Check if the A button is pressed
    bool keyAPressed();

    /// Check if the B button is pressed
    bool keyBPressed();

private:
    bool virtualKeyPressed(VirtualKeyIndex virtualKeyIndex);
    float m_moveObj;
    is::GameDisplay *m_scene;

    sf::Sprite m_sprJoystick[2];
    sf::RectangleShape m_recJoystickMask[2];
    sf::RectangleShape m_recKeyLeftMask, m_recKeyRightMask, m_recKeyUpMask, m_recKeyDownMask, m_recKeyAMask, m_recKeyBMask;
    sf::RectangleShape m_recLeft, m_recRight;
};

#endif // GAMEKEYDATA_H_INCLUDED
