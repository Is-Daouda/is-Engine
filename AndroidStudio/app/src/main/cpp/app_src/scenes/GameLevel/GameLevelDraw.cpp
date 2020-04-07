#include "GameLevel.h"

void GameLevel::draw()
{
    bool const SHOW_WIDGETS(true);

    // draw background
    m_surface.draw(m_sprLevelBg);

    // draw tile
    WITH (m_levelBackTile.size())
    {
        if (is::instanceExist(m_levelBackTile[_I]))
        {
            if (m_levelBackTile[_I]->inViewRec(*this, false))
            {
                m_surface.draw((*m_levelBackTile[_I]));
            }

            if (clearObject(m_levelBackTile[_I]->getX()))
            {
                m_levelBackTile[_I].reset();
            }
        }
    }

    // draw bonus
    WITH (m_bonusList.size())
    {
        if (is::instanceExist(m_bonusList[_I]))
        {
            //if (!isInPlayerRay(*m_bonusList[_I])) continue;
            if (m_bonusList[_I]->inViewRec(*this))
            {
                m_bonusList[_I]->draw(m_surface);
            }
        }
    }

    // draw blocks
    WITH(m_blockList.size())
    {
        if (is::instanceExist(m_blockList[_I]))
        {
            //if (!isInPlayerRay(m_blockList[_I])) continue;
            if (m_blockList[_I]->inViewRec(*this) && m_blockList[_I]->hasTexture())
            {
                m_blockList[_I]->draw(m_surface);
            }
        }
    }

    // draw enemy
    auto lowE = std::lower_bound(m_enemyList.begin(), m_enemyList.end(), m_player);
    auto upE  = std::upper_bound(m_enemyList.begin(), m_enemyList.end(), m_player);
    for (auto it = lowE; it != upE; ++it)
    {
        if (is::instanceExist(*it))
        {
            if ((*it)->inViewRec(*this))
            {
                (*it)->draw(m_surface);
            }
        }
    }

    if (is::instanceExist(m_electroShock))
    {
        m_electroShock->draw(m_surface);
    }

    // draw player
    if (m_playerInvicibilityTime % 2 == 0)
    {
        m_player.draw(m_surface);
    }

    // draw finish flag
    m_finishObject.draw(m_surface);

    // draw level title
    if (is::instanceExist(m_levelTitle))
    {
        m_levelTitle->draw(m_surface);
    }

    // draw HUD
    if (SHOW_WIDGETS)
    {
        if (m_isPlaying)
        {
            m_gameHud.draw(m_surface);
        }
    }

    // draw cancel button
    if (SHOW_WIDGETS)
    {
        if (!m_levelCompleted)
        {
            if (m_levelStart && m_isPlaying)
            {
                m_cancelBt.draw(m_surface);
            }
        }
    }

    // draw dialog box
    m_gameDialog.draw(m_surface);

    if (SHOW_WIDGETS)
    {
        #if defined(__ANDROID__)
        // draw game pad (only for mobile)
        if (m_isPlaying)
        {
            m_gameKey.draw(m_surface);
        }
        #endif

        // game pause
        if (!m_isPlaying && m_levelStart)
        {
            m_surface.draw(m_recPauseBG);
            if (m_optionIndex != 0) m_surface.draw(m_sprPad1);
            if (m_optionIndex != 1) m_surface.draw(m_sprPad2);
            if (m_optionIndex != 2) m_surface.draw(m_sprPad3);
            m_surface.draw(m_sprButtonSelect);
            m_surface.draw(m_txtContinue);
            m_surface.draw(m_txtRestart);
            m_surface.draw(m_txtQuit);
            if (is::instanceExist(m_pauseOption))
            {
                if (m_pauseObjMove < 450.f) m_pauseOption->draw(m_surface);
            }
        }
    }

    ///////////////////////////////////////
    // message box
    drawMsgBox();
    ///////////////////////////////////////
}
