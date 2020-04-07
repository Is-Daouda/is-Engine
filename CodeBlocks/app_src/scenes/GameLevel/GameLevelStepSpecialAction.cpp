#include "GameLevel.h"

/*
 * This file contains the implementation of trigger functions i.e. functions which must perform
 * an action at a specific moment in the game.
*/

void GameLevel::levelSpecialAction()
{
    if (CURRENT_LEVEL == is::level::LevelId::LEVEL_1)
    {
        if (m_gameDialog.getDialogIndex() == GameDialog::DIALOG_NONE)
        {
            m_gameDialog.setDialog(GameDialog::DIALOG_PLAYER_MOVE);
        }
    }

    if (CURRENT_LEVEL == is::level::LevelId::LEVEL_3)
    {
        if (m_gameDialog.getDialogIndex() == GameDialog::DIALOG_NONE)
        {
            m_gameDialog.setDialog(GameDialog::DIALOG_PLAYER_ATTACK);
        }
    }
}

void GameLevel::playerHurt(bool canContinue)
{
    if (canContinue)
    {
        if (m_player.getHealth() > 1)
        {
            m_gameSysExt.playSound(m_sndHurt);
            m_gameSysExt.useVibrate(60);
            m_player.addHealth(-1);
            m_playerInvicibilityTime = 60;
        }
        else
        {
            if (m_player.getIsActive())
            {
                m_gameSysExt.playSound(m_sndLose);
                m_gameSysExt.useVibrate(60);
                m_player.setHealth(0);
                m_restartTime++;
                m_player.setIsActive(false);
            }
        }
    }
    else
    {
        if (m_player.getIsActive())
        {
            m_gameSysExt.playSound(m_sndLose);
            m_gameSysExt.useVibrate(60);
            m_player.setHealth(0);
            m_restartTime++;
            m_player.setIsActive(false);
        }
    }
}
