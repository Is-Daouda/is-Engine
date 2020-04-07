#ifndef GAMESYSTEM_H_INCLUDED
#define GAMESYSTEM_H_INCLUDED

#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <typeinfo>

#include "GameFunction.h"
#include "../../../app_src/config/GameConfig.h"

//////////////////////////////////////////////////////
// is::Engine version
//////////////////////////////////////////////////////
#define IS_ENGINE_VERSION_MAJOR 2
#define IS_ENGINE_VERSION_MINOR 0
#define IS_ENGINE_VERSION_PATCH 0

namespace is
{
//////////////////////////////////////////////////////
/// \brief Class for manage game system
///
//////////////////////////////////////////////////////
class GameSystem
{
public:
    //////////////////////////////////////////////////////
    /// \brief Represent validation key on PC Platform
    ///
    /// It is used to know that button will be used for
    /// validation during a test
    //////////////////////////////////////////////////////
    enum ValidationButton
    {
        MOUSE = 0,        ///< Represent Mouse validation button (If it is used then it becomes touch action on android)
        KEYBOARD = -1,    ///< Represent Keyboard validation button
        ALL_BUTTONS = -2, ///< Represent Mouse and Keyboard validation button (If it is used then it becomes touch action on android)
    };
    GameSystem();

    //////////////////////////////////////////////////////
    /// On PC Platform check if mouse / keyboard validation key button is pressed
    /// On Android check if user touch screen
    /// validation key is set in GameConfig.h
    ///
    /// \param finger Finger index (on Android)
    /// \param validationButton Represents the validation button to use to take the test
    //////////////////////////////////////////////////////
    bool isPressed(
                   #if defined(__ANDROID__)
                   int finger = 0
                   #else
                   ValidationButton validationButton = ALL_BUTTONS
                   #endif // defined
                   ) const;

    //////////////////////////////////////////////////////
    /// \brief Check if keyboard key is pressed
    ///
    /// \return true if key is pressed false if not
    //////////////////////////////////////////////////////
    bool keyIsPressed(sf::Keyboard::Key key) const;

    //////////////////////////////////////////////////////
    /// \brief Check if mouse button is pressed
    ///
    /// \return true if button is pressed false if not
    //////////////////////////////////////////////////////
    bool keyIsPressed(sf::Mouse::Button button) const;

    //////////////////////////////////////////////////////
    /// \brief Check if file exist
    ///
    /// \return true is file is found false if not
    //////////////////////////////////////////////////////
    bool fileExist(std::string const &fileName) const;

    /// Allows to play a sound if the option is activated
    void playSound(sf::Sound &snd);

    /// Allows to stop a sound
    void stopSound(sf::Sound &snd);

    /// Allows to use vibrate if the option is activated (only for Android)
    /// \param ms representing the duration of the vibrator in millisecond
    void useVibrate(short ms);

    /// Save game configuration data
    void saveConfig(std::string const &fileName);

    /// Load game configuration data
    void loadConfig(std::string const &fileName);

    /// Save virtual game pad configuration data
    void savePadConfig(std::string const &fileName);

    /// Load virtual game pad configuration data
    void loadPadConfig(std::string const &fileName);

    ////////////////////////////////////////////////////////////
    // Do not touch these variables unless you know what you are doing
    bool  m_disableKey;    ///< If it is @a true all the engine functions that manage the inputs are deactivated (keyboard, mouse, touch)
    bool  m_enableSound;   ///< Used to find out if sound is enabled in option
    bool  m_enableMusic;   ///< Used to find out if music is enabled in option
    bool  m_enableVibrate; ///< Used to find out if vibrate is enabled in option
    bool  m_keyIsPressed;  ///< Used to find out if a key / button has been pressed
    bool  m_firstLaunch;   ///< Lets check if the game has been launched once

    /// Represent the variable that stores the option validation key with the Mouse
    sf::Mouse::Button m_validationMouseKey;

    /// Represent the variable that stores the option validation key with the Keyboard
    sf::Keyboard::Key m_validationKeyboardKey;

    int m_gameLanguage; ///< Represents the index of the chosen language
    int m_padAlpha;     ///< Use to change the transparency of the Virtual Game Pad

    // These variable allows to position the Virtual Game Pad
    float m_padDirXPos, m_padDirYPos, m_padActionXPos, m_padActionYPos;
    float m_defaultPadDirXPos, m_defaultPadDirYPos, m_defaultPadActionXPos, m_defaultPadActionYPos;
    bool  m_permutePadAB;
    ////////////////////////////////////////////////////////////
};
}
#endif // GAMESYSTEM_H_INCLUDED
