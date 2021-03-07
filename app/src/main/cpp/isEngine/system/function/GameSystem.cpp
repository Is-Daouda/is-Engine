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

#include "../function/GameSystem.h"

namespace is
{
GameSystem::GameSystem(sf::RenderWindow &window):
    m_window(window)
{
    m_gameLanguage = 0; // 0 = default language
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
    //#elif defined(IS_ENGINE_HTML_5)
    //if (m_window.input().IsCursorHold()) return true;
    #else
    //////////////////////////////////////////////////////////
    switch (validationButton)
    {
        case ValidationButton::MOUSE :
            if (
                #if !defined(IS_ENGINE_HTML_5)
                sf::Mouse::isButtonPressed(m_validationMouseKey)
                #else
                //m_window.input().IsMousePressed
                m_window.input().IsCursorHold()
                #endif
                ) return true;
        break;
        case ValidationButton::KEYBOARD :
            if (
                #if !defined(IS_ENGINE_HTML_5)
                sf::Keyboard::isKeyPressed
                #else
                m_window.input().IsKeyHold
                #endif
                (m_validationKeyboardKey)) return true;
        break;
        case ValidationButton::ALL_BUTTONS :
            if (
                #if !defined(IS_ENGINE_HTML_5)
                sf::Mouse::isButtonPressed(m_validationMouseKey)
                #else
                //m_window.input().IsMousePressed
                m_window.input().IsCursorHold()
                #endif
                ) return true;
            else if (
                     #if !defined(IS_ENGINE_HTML_5)
                     sf::Keyboard::isKeyPressed
                     #else
                     m_window.input().IsKeyHold
                     #endif
                     (m_validationKeyboardKey)) return true;
        break;
    }
    #endif
    return false;
}

bool GameSystem::keyIsPressed(
                              #if !defined(IS_ENGINE_HTML_5)
                              sf::Keyboard::Key
                              #else
                              short
                              #endif
                              key
                              ) const
{
    if (m_disableKey) return false;
    #if !defined(IS_ENGINE_HTML_5)
    if (sf::Keyboard::isKeyPressed(key)) return true;
    #else
    if ((key >= 0 && key <= 7) && m_window.input().IsMousePressed(key)) return true;
    if ((key > 7 || key == -1) && m_window.input().IsKeyHold(key)) return true;
    #endif
    return false;
}

#if !defined(IS_ENGINE_HTML_5)
bool GameSystem::keyIsPressed(sf::Mouse::Button button) const
{
    if (m_disableKey) return false;
    if (sf::Mouse::isButtonPressed(button)) return true;
    return false;
}
#endif

bool GameSystem::fileExist(std::string const &fileName)
{
    return is::fileExist(fileName);
}

void GameSystem::removeFile(std::string const &fileName)
{
#if defined(GAME_FULL_VERSION)
    remove(fileName.c_str());
#endif // defined
}

void GameSystem::useVibrate(short ms)
{
    if (m_enableVibrate) is::vibrate(ms);
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
