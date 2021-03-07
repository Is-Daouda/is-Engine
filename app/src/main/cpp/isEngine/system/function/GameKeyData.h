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

#ifndef GAMEKEYDATA_H_INCLUDED
#define GAMEKEYDATA_H_INCLUDED

#include "../display/GameDisplay.h"

namespace is
{
//////////////////////////////////////////////////////
/// \brief Class for manage game command
/// (Keyboard / Virtual Game Pad for Android)
///
//////////////////////////////////////////////////////
class GameKeyData : public MainObject
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
         m_keyLeftUsed,
         m_keyRightUsed,
         m_keyUpUsed,
         m_keyDownUsed,
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
    virtual void loadResources();

    /// Manages the positioning of the Virtual Game Pad relative to the screen (only for Android)
    virtual void step(float const &DELTA_TIME);

    /// Draw the Virtual Game Pad on the screen (only for Android)
    virtual void draw(is::Render &surface);

    /// Check if the Left directional button is pressed
    virtual bool keyLeftPressed();

    /// Check if the Right directional button is pressed
    virtual bool keyRightPressed();

    /// Check if the Up directional button is pressed
    virtual bool keyUpPressed();

    /// Check if the Down directional button is pressed
    virtual bool keyDownPressed();

    /// Check if the A button is pressed
    virtual bool keyAPressed();

    /// Check if the B button is pressed
    virtual bool keyBPressed();

private:
    bool virtualKeyPressed(VirtualKeyIndex virtualKeyIndex);
    #if defined(__ANDROID__)
    float m_moveObj;
    #endif
    is::GameDisplay *m_scene;

    sf::Sprite m_sprJoystick[2];
    sf::RectangleShape m_recJoystickMask[2];
    sf::RectangleShape m_recKeyLeftMask, m_recKeyRightMask, m_recKeyUpMask, m_recKeyDownMask, m_recKeyAMask, m_recKeyBMask;
};
};

#endif // GAMEKEYDATA_H_INCLUDED
