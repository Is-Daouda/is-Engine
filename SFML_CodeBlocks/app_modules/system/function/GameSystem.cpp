#include "../function/GameSystem.h"

namespace is
{
GameSystem::GameSystem()
{
    m_enableSound = true;
    m_enableMusic = true;
    m_enableVibrate = true;
    m_keyIsPressed = false;
    m_keyboard = sf::Keyboard::W;
    m_keyMouse = sf::Mouse::Left;
}

bool GameSystem::actionKeyPressed(
                               #if defined(__ANDROID__)
                               unsigned int finger
                               #endif // defined
                               ) const
{
    if (sf::Mouse::isButtonPressed(m_keyMouse)) return true;
    else if (sf::Keyboard::isKeyPressed(m_keyboard)) return true;
    //////////////////////////////////////////////////////////
    /// Android version code
    #if defined(__ANDROID__)
    else if (sf::Touch::isDown(finger)) return true;
    #endif // defined
    //////////////////////////////////////////////////////////
    else return false;
}

bool GameSystem::isPressed(
                           #if defined(__ANDROID__)
                           unsigned int finger
                           #endif // defined
                           ) const
{
    if (sf::Mouse::isButtonPressed(m_keyMouse)) return true;
    //////////////////////////////////////////////////////////
    // Android version code
    #if defined(__ANDROID__)
    else if (sf::Touch::isDown(finger)) return true;
    #endif // defined
    //////////////////////////////////////////////////////////
    else return false;
}

bool GameSystem::fileExist(std::string const &fileName) const
{
    std::ifstream file(fileName.c_str());
    return !file.fail();
}

void GameSystem::playSound(sf::Sound &m_snd)
{
    if (m_enableSound) m_snd.play();
}

void GameSystem::stopSound(sf::Sound &m_snd)
{
    if (m_enableSound)
    {
        if (m_snd.getStatus() == sf::Sound::Playing) m_snd.stop();
    }
}

#if defined(__ANDROID__)
void GameSystem::useVibrate(short ms)
{
    if (m_enableVibrate) is::vibrate(sf::milliseconds(ms));
}
#endif // defined
}
