#ifndef GAMESYSTEM_H_INCLUDED
#define GAMESYSTEM_H_INCLUDED

#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <cstdio>
#include <iostream>

////////////////////////////////////////////////////////////
/// uncomment to enable Linux export
// #define LINUX_VERSION

#if defined(__ANDROID__)
/// uncomment to enable showLog function on Android Log cat
// #define ENABLE_SHOW_LOG

/// uncomment this line to use Admob
// #define ENABLE_ADMOB
// if you enable Admob you need to uncomment line in
// CMakeLists and Gradle files to link the Firebase library on project
#endif // defined
////////////////////////////////////////////////////////////

#include "GameFunction.h"

namespace is
{
class GameSystem
{
public:
    GameSystem();
    bool actionKeyPressed(
                       #if defined(__ANDROID__)
                       unsigned int finger = 0
                       #endif // defined
                       ) const;
    bool isPressed(
                   #if defined(__ANDROID__)
                   unsigned int finger = 0
                   #endif // defined
                   ) const;
    bool fileExist(std::string const &fileName) const;
    void playSound(sf::Sound &m_snd);
    void stopSound(sf::Sound &m_snd);

    #if defined(__ANDROID__)
    void useVibrate(short ms);
    #endif // defined

    bool  m_enableSound;
    bool  m_enableMusic;
    bool  m_enableVibrate;
    bool  m_keyIsPressed;

    sf::Mouse::Button m_keyMouse;
    sf::Keyboard::Key m_keyboard;
};
}
#endif // GAMESYSTEM_H_INCLUDED
