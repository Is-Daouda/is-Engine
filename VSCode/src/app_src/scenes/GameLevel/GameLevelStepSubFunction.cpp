#include "GameLevel.h"

/*
 * This file contains the implementation of the functions which manage the mechanisms of
 * the game (key management, pause action, ...)
*/

void GameLevel::commandController()
{
    if (!m_gameSysExt.isPressed()) m_gameSysExt.m_keyIsPressed = false;
    if (!m_gameKey.keyAPressed()) m_gameKey.m_keyAUsed = false;
    if (!m_gameKey.keyBPressed()) m_gameKey.m_keyBUsed = false;

    m_gameKey.m_keyLeftPressed = m_gameKey.keyLeftPressed();
    m_gameKey.m_keyRightPressed = m_gameKey.keyRightPressed();
    m_gameKey.m_keyUpPressed = m_gameKey.keyUpPressed();
    m_gameKey.m_keyDownPressed = m_gameKey.keyDownPressed();
    m_gameKey.m_keyAPressed = m_gameKey.keyAPressed();
    m_gameKey.m_keyBPressed = m_gameKey.keyBPressed();

    if (m_gameKey.m_keyLeftPressed)
    {
        m_gameKey.m_keyRightPressed = false;
        m_gameKey.m_keyUpPressed = false;
        m_gameKey.m_keyDownPressed = false;
    }
    else if (m_gameKey.m_keyRightPressed)
    {
        m_gameKey.m_keyLeftPressed = false;
        m_gameKey.m_keyUpPressed = false;
        m_gameKey.m_keyDownPressed = false;
    }
    else if (m_gameKey.m_keyUpPressed)
    {
        m_gameKey.m_keyLeftPressed = false;
        m_gameKey.m_keyRightPressed = false;
        m_gameKey.m_keyDownPressed = false;
    }
    else if (m_gameKey.m_keyDownPressed)
    {
        m_gameKey.m_keyLeftPressed = false;
        m_gameKey.m_keyRightPressed = false;
        m_gameKey.m_keyUpPressed = false;
    }
    m_gameKey.step(DELTA_TIME);
}

void GameLevel::pauseGame()
{
    if (((((m_gameSysExt.isPressed(is::GameSystem::ValidationButton::KEYBOARD) && !m_gameSysExt.m_keyIsPressed) || m_keyBackPressed) && !m_gameKey.m_keyPausePressed) ||
         (m_gameSysExt.isPressed(is::GameSystem::ValidationButton::MOUSE) && m_cancelBt.isOn())) &&
         (m_levelStart && !m_levelEnd && m_finishObject.getStep() == 0 && m_player.getHealth() != 0))
    {
        m_gameSysExt.playSound(m_sndSelectOption);
        if (!m_keyBackPressed) m_gameSysExt.useVibrate(m_vibrateTimeDuration);
        stopSounds(true);
        m_isPlaying = false;
        m_gameKey.m_keyPausePressed = true;
        m_gameSysExt.m_keyIsPressed = true;
        m_keyBackPressed = false;
    }
}

void GameLevel::stopSounds(bool val)
{
    if (m_gameSysExt.m_enableSound)
    {
        if (val)
        {
            if (m_sndLose.getStatus() == sf::Sound::Playing)      m_sndLose.pause();
            if (m_sndPlayerWin.getStatus() == sf::Sound::Playing) m_sndPlayerWin.pause();
        }
        else
        {
            if (m_sndLose.getStatus() == sf::Sound::Paused)      m_gameSysExt.playSound(m_sndLose);
            if (m_sndPlayerWin.getStatus() == sf::Sound::Paused) m_gameSysExt.playSound(m_sndPlayerWin);
        }
        m_player.stopAllSounds(val);
    }
    if (m_gameSysExt.m_enableMusic)
    {
        if (val)
        {
            if (m_mscLevel.getStatus() == sf::Sound::Playing) m_mscLevel.pause();
        }
        else
        {
            if (m_mscLevel.getStatus() == sf::Sound::Paused) m_mscLevel.play();
        }
    }
}

float GameLevel::getPlayerOtherObjPtDir(std::shared_ptr<is::MainObject> &obj)
{
    return is::pointDirection<float>(m_player.getSpriteX(), m_player.getSpriteY(), obj->getSpriteX(), obj->getSpriteY());
}

bool GameLevel::clearObject(float const &x) const
{
    return (x < m_viewX - 3200.f);
}

bool GameLevel::isInPlayerRay(std::shared_ptr<is::MainObject> &obj) const
{
    return (is::isBetween(m_player.getSpriteX(), obj->getX() + 500.f, obj->getX() - 500.f));
}

bool GameLevel::playerIsVulnerable() const
{
    return (m_playerInvicibilityTime == 0 && m_player.getIsActive());
}
