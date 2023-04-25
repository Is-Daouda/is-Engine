/*
  is::Engine (Infinity Solutions Engine)
  Copyright (C) 2018-2023 Is Daouda <isdaouda.n@gmail.com>

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

#include "GameSystem.h"

namespace is
{
const short MOUSE = 0;
const short KEYBOARD = -1;
const short ALL_BUTTONS = -2;

GameSystem::GameSystem(sf::RenderWindow &window):
    m_window(window)
{
    srand((unsigned int)time(0));
    m_gameLanguage = 0; // 0 = default language
    m_validationMouseKey    = &GameConfig::KEY_VALIDATION_MOUSE;
    m_validationKeyboardKey = &GameConfig::KEY_VALIDATION_KEYBOARD;
    m_disableKey = false;
    m_enableSound = true;
    m_enableMusic = true;
    m_enableVibrate = true;
    m_loadParentResources = false;
    m_keyIsPressed = false;
}

bool GameSystem::isPressed(int finger) const
{
    if (m_disableKey) return false;
    //////////////////////////////////////////////////////////
    // Android version code
if (is::IS_ENGINE_MOBILE_OS)
{
    // Exclude the keyboard test when we are on Android
    if (finger == -1) return false;

    // When testing the mouse validation buttons on PC then consider it as a touch
    if (finger == -2) finger = 0;
    if (sf::Touch::isDown(finger)) return true;
}
else
{
    //////////////////////////////////////////////////////////
    switch (finger)
    {
        case MOUSE:
            if (sf::Mouse::isButtonPressed(*m_validationMouseKey)) return true;
        break;
        case KEYBOARD:
            if (sf::Keyboard::isKeyPressed(*m_validationKeyboardKey)) return true;
        break;
        case ALL_BUTTONS:
            if (sf::Mouse::isButtonPressed(*m_validationMouseKey)) return true;
            else if (sf::Keyboard::isKeyPressed(*m_validationKeyboardKey)) return true;
        break;
    }
}
    return false;
}

bool GameSystem::isPressed(ValidationButton validationButton) const
{
    int value = validationButton;
    return isPressed(value);
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

bool GameSystem::fileExist(const std::string &fileName)
{
    return is::fileExist(fileName);
}

void GameSystem::removeFile(const std::string &fileName)
{
    remove(fileName.c_str());
#if defined(IS_ENGINE_HTML_5)
        EM_ASM(FS.syncfs(false, function(err){console.log(err)});, 0);
#endif
}

void GameSystem::playSound(sf::Sound &obj)
{
    if (m_enableSound) is::playSFMLSnd(obj);
}

void GameSystem::playSound(sf::Sound *obj)
{
    if (m_enableSound) is::playSFMLSnd(obj);
}

void GameSystem::playMusic(sf::Music &obj)
{
    if (m_enableMusic) is::playSFMLSnd(obj);
}

void GameSystem::playMusic(sf::Music *obj)
{
    if (m_enableMusic) is::playSFMLSnd(obj);
}

void GameSystem::stopSound(sf::Sound &obj)
{
    if (m_enableSound)
    {
        if (is::checkSFMLSndState(obj, SFMLSndStatus::Playing)) is::stopSFMLSnd(obj);
    }
}

void GameSystem::stopMusic(sf::Music &obj)
{
    if (m_enableMusic)
    {
        if (is::checkSFMLSndState(obj, SFMLSndStatus::Playing)) is::stopSFMLSnd(obj);
    }
}

void GameSystem::useVibrate(short ms)
{
    if (m_enableVibrate) is::vibrate(ms);
}

void GameSystem::saveConfig(const std::string &fileName)
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
#if defined(IS_ENGINE_HTML_5)
        EM_ASM(FS.syncfs(false, function(err){console.log(err)});, 0);
#endif
    }
}

void GameSystem::loadConfig(const std::string &fileName)
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

void GameSystem::savePadConfig(const std::string &fileName)
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
#if defined(IS_ENGINE_HTML_5)
        EM_ASM(FS.syncfs(false, function(err){console.log(err)});, 0);
#endif
    }
}

void GameSystem::loadPadConfig(const std::string &fileName)
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

void GSMplaySound(const std::string& name, std::vector<std::shared_ptr<GameSound>> &GSMsound, GameSystem &gameSystem)
{
    bool soundExist(false);
    WITH(GSMsound.size())
    {
        if (GSMsound[_I].get() != nullptr)
        {
            if (GSMsound[_I]->getName() == name)
            {
                soundExist = true;
                if (GSMsound[_I]->getFileIsLoaded()) gameSystem.playSound(GSMsound[_I]->getSound());
                else is::showLog("ERROR: Can't play <" + name + "> sound!");
                break;
            }
        }
    }
    if (!soundExist) is::showLog("ERROR: Can't play <" + name + "> sound because sound does not exist!");
}

void GSMplayMusic(const std::string& name, std::vector<std::shared_ptr<
//#if !defined(__ANDROID__)
                  GameMusic
//#else
//                  GameSound
//#endif
                  >> &GSMmusic, GameSystem &gameSystem)
{
//#if defined(__ANDROID__)
//    GSMplaySound(name, GSMmusic, gameSystem);
//#else
    bool musicExist(false);
    WITH(GSMmusic.size())
    {
        if (GSMmusic[_I].get() != nullptr)
        {
            if (GSMmusic[_I]->getName() == name)
            {
                musicExist = true;
                if (GSMmusic[_I]->getFileIsLoaded()) gameSystem.playMusic(GSMmusic[_I]->getMusic());
                else is::showLog("ERROR: Can't play <" + name + "> music!");
                break;
            }
        }
    }
    if (!musicExist) is::showLog("ERROR: Can't play <" + name + "> music because music does not exist!");
//#endif
}
}
