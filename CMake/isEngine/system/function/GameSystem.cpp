#include "../function/GameSystem.h"

namespace is
{
GameSystem::GameSystem()
{
    m_validationMouseKey    = GameConfig::KEY_VALIDATION_MOUSE;
    m_validationKeyboardKey = GameConfig::KEY_VALIDATION_KEYBOARD;
    m_disableKey = false;
    m_enableSound = true;
    m_enableMusic = true;
    m_enableVibrate = true;
    m_keyIsPressed = false;
}

bool GameSystem::isPressed(
                           #if defined(__ANDROID__)
                           int finger
                           #else
                           ValidationButton validationButton
                           #endif // defined
                           ) const
{
    if (m_disableKey) return false;
    //////////////////////////////////////////////////////////
    // Android version code
    #if defined(__ANDROID__)
    // Exclude the keyboard test when we are on Android
    if (finger == -1) return false;

    // When testing the two validation buttons on PC then consider it as a touch
    if (finger == -2) finger = 0;
    if (sf::Touch::isDown(finger)) return true;
    #else
    //////////////////////////////////////////////////////////
    switch (validationButton)
    {
        case ValidationButton::MOUSE :
            if (sf::Mouse::isButtonPressed(m_validationMouseKey)) return true;
        break;
        case ValidationButton::KEYBOARD :
            if (sf::Keyboard::isKeyPressed(m_validationKeyboardKey)) return true;
        break;
        case ValidationButton::ALL_BUTTONS :
            if (sf::Mouse::isButtonPressed(m_validationMouseKey)) return true;
            else if (sf::Keyboard::isKeyPressed(m_validationKeyboardKey)) return true;
        break;
    }
    #endif // defined
    return false;
}

bool GameSystem::keyIsPressed(sf::Keyboard::Key key) const
{
    if (m_disableKey) return false;
    if (sf::Keyboard::isKeyPressed(key)) return true;
    return false;
}

bool GameSystem::keyIsPressed(sf::Mouse::Button button) const
{
    if (m_disableKey) return false;
    if (sf::Mouse::isButtonPressed(button)) return true;
    return false;
}

bool GameSystem::fileExist(std::string const &fileName) const
{
    std::ifstream file(fileName.c_str());
    return !file.fail();
}

void GameSystem::useVibrate(short ms)
{
    if (m_enableVibrate) is::vibrate(sf::milliseconds(ms));
}


void GameSystem::saveConfig(std::string const &fileName)
{
    FILE *file = NULL;
    file = fopen(fileName.c_str(), "wb");

    if (file != NULL)
    {
        fwrite(&m_enableSound, sizeof(bool), 1, file);
        fwrite(&m_enableMusic, sizeof(bool), 1, file);
        fwrite(&m_enableVibrate, sizeof(bool), 1, file);
        fwrite(&m_gameLanguage, sizeof(int), 1, file);
        fwrite(&m_firstLaunch, sizeof(bool), 1, file);
        fclose(file);
    }
}

void GameSystem::loadConfig(std::string const &fileName)
{
    FILE *file = NULL;
    file = fopen(fileName.c_str(), "rb");

    if (file != NULL)
    {
        fread(&m_enableSound, sizeof(bool), 1, file);
        fread(&m_enableMusic, sizeof(bool), 1, file);
        fread(&m_enableVibrate, sizeof(bool), 1, file);
        fread(&m_gameLanguage, sizeof(int), 1, file);
        fread(&m_firstLaunch, sizeof(bool), 1, file);
        fclose(file);
    }
}

void GameSystem::savePadConfig(std::string const &fileName)
{
    FILE *file = NULL;
    file = fopen(fileName.c_str(), "wb");

    if (file != NULL)
    {
        fwrite(&m_padDirXPos, sizeof(float), 1, file);
        fwrite(&m_padDirYPos, sizeof(float), 1, file);
        fwrite(&m_padActionXPos, sizeof(float), 1, file);
        fwrite(&m_padActionYPos, sizeof(float), 1, file);
        fwrite(&m_padAlpha, sizeof(int), 1, file);
        fwrite(&m_permutePadAB, sizeof(bool), 1, file);
        fclose(file);
    }
}

void GameSystem::loadPadConfig(std::string const &fileName)
{
    FILE *file = NULL;
    file = fopen(fileName.c_str(), "rb");

    if (file != NULL)
    {
        fread(&m_padDirXPos, sizeof(float), 1, file);
        fread(&m_padDirYPos, sizeof(float), 1, file);
        fread(&m_padActionXPos, sizeof(float), 1, file);
        fread(&m_padActionYPos, sizeof(float), 1, file);
        fread(&m_padAlpha, sizeof(int), 1, file);
        fread(&m_permutePadAB, sizeof(bool), 1, file);
        fclose(file);
    }
}
}
