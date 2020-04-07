#include "GameLevel.h"

/*
 * This file contains the implementation of the functions which update game play
 * objects (view, enemy, bonus, ..)
*/

void GameLevel::updateObjBonusList()
{
    WITH(m_bonusList.size())
    {
        if (is::instanceExist(m_bonusList[_I]))
        {
            //if (!isInPlayerRay(m_bonusList[_I])) continue;

            if (m_bonusList[_I]->inViewRec(*this, true))
            {
                if (m_player.getIsActive())
                {
                     if (is::pointDistance(m_player.getSpriteX(), m_player.getSpriteY(),
                                       m_bonusList[_I]->getX() + 16.f, m_bonusList[_I]->getY()+ 16.f) < 34.f && !m_bonusList[_I]->getTouchPlayer())
                    {
                        switch (m_bonusList[_I]->getType())
                        {
                            case Bonus::BonusType::BONUS_NORMAL:
                                m_gameSysExt.m_currentBonus++;
                                m_gameSysExt.m_currentScore += m_bonusList[_I]->getScorePoint();

                                // add life if bonus > 99
                                if (m_gameSysExt.m_currentBonus > 99)
                                {
                                    m_gameSysExt.playSound(m_sndHaveLife);
                                    m_gameSysExt.useVibrate(60);
                                    m_gameSysExt.m_currentLives++;
                                    m_gameSysExt.m_currentBonus = 0;
                                }
                                m_gameSysExt.playSound(m_sndHaveBonus);
                            break;

                            case Bonus::BonusType::BONUS_HEALTH:
                                if (m_player.getHealth() < 4) m_player.addHealth();
                                else m_gameSysExt.m_currentScore += m_bonusList[_I]->getScorePoint() * 5;
                                m_gameSysExt.playSound(m_sndHaveHealth);
                            break;

                            case Bonus::BonusType::BONUS_1_UP:
                                m_gameSysExt.m_currentLives++;
                                m_gameSysExt.playSound(m_sndHaveLife);
                            break;
                        }
                        m_bonusList[_I]->setTouchPlayer(true);
                    }
                }

                m_bonusList[_I]->step(DELTA_TIME);

                // destruction
                if (m_bonusList[_I]->isDestroyed())
                {
                    m_bonusList[_I].reset();
                }
            }
        }
    }
}

void GameLevel::updateObjEnemyList()
{
    auto lowB = std::lower_bound(m_enemyList.begin(), m_enemyList.end(), m_player);
    auto upB  = std::upper_bound(m_enemyList.begin(), m_enemyList.end(), m_player);

    for (auto it = lowB; it != upB; ++it)
    {
        if (is::instanceExist((*it)))
        {
            // collision with player
            if (m_player.placeMetting(0, 0, (*it)))
            {
                if (playerIsVulnerable()) playerHurt();
            }

            // collision with player electro shock
            if (is::instanceExist(m_electroShock))
            {
                if (m_electroShock->distantToObject((*it), false) < 32.f && (*it)->getIsDestructible())
                {
                    m_gameSysExt.playSound(m_sndEnemyDestroy);
                    (*it)->setDestroyed();
                    m_electroShock->setDestroyed();
                }
            }

            (*it)->step(DELTA_TIME);

            // destruction
            if ((*it)->isDestroyed())
            {
                if ((*it)->getScorePoint() > 0) m_gameSysExt.m_currentScore += (*it)->getScorePoint();
                (*it).reset();
            }
        }
    }
}

void GameLevel::updateObjView()
{
    // move the view if player is active
    if (!m_player.getIsKO())
    {
        if (m_player.getX() > m_viewW / 2.f && m_player.getX() < static_cast<float>(m_levelWidth * 32) - m_viewW / 2.f)
            m_viewX = m_player.getX();

        if (m_player.getY() > static_cast<float>(m_levelHeight * 32) - m_viewH / 2.f)
            m_viewY = static_cast<float>(m_levelHeight * 32) - m_viewH / 2.f;
        else if (m_player.getY() > m_viewH / 2.f && m_player.getY() < static_cast<float>(m_levelHeight * 32) - m_viewH / 2.f)
            m_viewY = m_player.getY();
        else if (m_player.getY() < m_viewH / 2.f) m_viewY = m_viewH / 2.f;
    }

    // update view
    setView();
}

void GameLevel::updateObjFinish()
{
    if (m_finishObject.getStep() == 0)
    {
        if (m_finishObject.placeMetting(0, 0, &m_player))
        {
            m_gameSysExt.playSound(m_sndPlayerWin);
            m_gameKey.m_disableAllKey = true;
            m_finishObject.addStep();
        }
    }
}

void GameLevel::updateBackground()
{
    if ((is::isBetween(CURRENT_LEVEL, is::level::LEVEL_1, is::level::LEVEL_3)))
    {
        is::setSFMLObjX_Y(m_sprLevelBg, m_viewX * 0.98f - 390.f, m_viewY - 240.f);
    }
}

void GameLevel::updatePauseObj(bool useMoveAnimation)
{
    if (useMoveAnimation)
    {
        if (m_pauseObjMove > 35.f) m_pauseObjMove -= ((30.f * is::VALUE_CONVERSION) * DELTA_TIME);
        else m_pauseObjMove = 0.f;
    }
    else m_pauseObjMove = 480.f;

    is::setSFMLObjX_Y(m_sprPad1, m_viewX + m_pauseObjMove, m_viewY - 64.f);
    is::setSFMLObjX_Y(m_sprPad2, m_viewX + (160.f + m_pauseObjMove), m_viewY);
    is::setSFMLObjX_Y(m_sprPad3, m_viewX - (160.f - m_pauseObjMove), m_viewY);
    if (!useMoveAnimation) is::setSFMLObjX_Y(m_sprButtonSelect, m_viewX + m_pauseObjMove, m_viewY);

    float const TXT_Y_POS(6.f);
    is::setSFMLObjX_Y(m_txtContinue, is::getSFMLObjX(m_sprPad1), is::getSFMLObjY(m_sprPad1) - TXT_Y_POS);
    is::setSFMLObjX_Y(m_txtRestart, is::getSFMLObjX(m_sprPad2), is::getSFMLObjY(m_sprPad2) - TXT_Y_POS);
    is::setSFMLObjX_Y(m_txtQuit, is::getSFMLObjX(m_sprPad3), is::getSFMLObjY(m_sprPad3) - TXT_Y_POS);

    m_pauseOption->setPosition(m_viewX - 10.f, (m_viewY - 175.f) - m_pauseObjMove);
    is::setSFMLObjX_Y(m_recPauseBG, m_viewX, m_viewY);
}

void GameLevel::updateObjGameplayController()
{
    m_gameHud.step(DELTA_TIME, m_gameTime, m_player, m_levelCompleted);

    updatePauseObj(false);

    m_cancelBt.setPosition(m_viewX + 280.f, m_viewY - 200.f);
    m_cancelBt.step(DELTA_TIME);
}
