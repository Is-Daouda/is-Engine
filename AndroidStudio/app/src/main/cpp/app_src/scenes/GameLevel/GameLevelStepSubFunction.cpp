#include "GameLevel.h"

/*
 * This file contains the implementation of the functions which manage the mechanisms of
 * the game (special action, pause action, ...)
*/

void GameLevel::pauseGame()
{
    // We call the object which is in the SDM container
    auto gameKey = static_cast<is::GameKeyData*>(SDMgetObject("GameKeyData"));
    auto cancelBt = static_cast<CancelButton*>(SDMgetObject("CancelButton"));
    auto finishObject = static_cast<FinishObject*>(SDMgetObject("FinishObject"));
    auto player = static_cast<Player*>(SDMgetObject("Player"));

    if (((((m_gameSysExt.isPressed(is::GameSystem::ValidationButton::KEYBOARD) && !m_gameSysExt.m_keyIsPressed) ||
           m_keyBackPressed) && !gameKey->m_keyPausePressed) ||
         (m_gameSysExt.isPressed(is::GameSystem::ValidationButton::MOUSE) && cancelBt->isOn())) &&
        (m_sceneStart && !m_sceneEnd && finishObject->getStep() == 0 && player->getHealth() != 0))
    {
        GSMplaySound("select_option"); // We play this sound
        if (!m_keyBackPressed) m_gameSysExt.useVibrate(m_vibrateTimeDuration);
        stopSounds(true);
        m_isPlaying = false;
        gameKey->m_keyPausePressed = true;
        m_gameSysExt.m_keyIsPressed = true;
        m_keyBackPressed = false;
    }
}

void GameLevel::levelSpecialAction()
{
    // We call the object which is in the SDM container
    auto gameDialog = static_cast<GameDialog*>(SDMgetObject("GameDialog"));
    if (CURRENT_LEVEL == is::level::LevelId::LEVEL_1)
    {
        if (gameDialog->getDialogIndex() == GameDialog::DIALOG_NONE)
        {
            gameDialog->setDialog(GameDialog::DIALOG_PLAYER_MOVE);
        }
    }
    if (CURRENT_LEVEL == is::level::LevelId::LEVEL_3)
    {
        if (gameDialog->getDialogIndex() == GameDialog::DIALOG_NONE)
        {
            gameDialog->setDialog(GameDialog::DIALOG_PLAYER_ATTACK);
        }
    }
}

void GameLevel::stopSounds(bool val)
{
    if (m_gameSysExt.m_enableSound)
    {
        if (val)
        {
            GSMpauseSound("lose");
            GSMpauseSound("finish");
        }
        else
        {
            if (is::getSFMLSndState(GSMgetSound("lose"), sf::Sound::Paused))   GSMpauseSound("lose");
            if (is::getSFMLSndState(GSMgetSound("finish"), sf::Sound::Paused)) GSMpauseSound("finish");
        }
        static_cast<Player*>(SDMgetObject("Player"))->stopAllSounds(val);
    }
    if (m_gameSysExt.m_enableMusic)
    {
        if (val)
        {
            if (is::getSFMLSndState(GSMgetMusic("level_music"), sf::Sound::Playing)) GSMgetMusic("level_music")->pause();
        }
        else
        {
            if (is::getSFMLSndState(GSMgetMusic("level_music"), sf::Sound::Paused)) GSMgetMusic("level_music")->play();
        }
    }
}
