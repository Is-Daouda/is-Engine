#include "GameLevel.h"

void GameLevel::draw()
{
    // draw tile
    WITH (m_levelTile.size())
    {
        if (is::instanceExist(m_levelTile[_I]))
        {
            if (m_levelTile[_I]->inViewRec(m_view, false))
            {
                m_app.draw((*m_levelTile[_I]));
            }
        }
    }

    // draw bonus
    auto lowA = std::lower_bound(m_bonusList.begin(), m_bonusList.end(), m_player);
    auto upA  = std::upper_bound(m_bonusList.begin(), m_bonusList.end(), m_player);
    for (auto it = lowA; it != upA; ++it)
    {
        if (is::instanceExist(*it))
        {
            if ((*it)->inViewRec(m_view))
            {
                (*it)->draw(m_app);
            }
        }
    }

    // draw advice only in LEVEL 1
    if (CURRENT_LEVEL == LevelId::LEVEL_1)
    {
        m_app.draw(m_txtAdvice);
    }

    // draw goal
    m_goal.draw(m_app);

    // draw player
    m_player.draw(m_app);

    // draw the HUD
    m_gameHud.draw(m_app);

    // draw pause button
    if (!m_levelCompleted)
    {
        if (m_levelStart)
        {
            m_pauseBt.draw(m_app);
        }
    }

    // draw joystick
    for (int i(0); i < 2; i++) m_app.draw(m_sprJoystick[i]);

    // pause menu
    if (!m_isPlaying && m_levelStart)
    {
        m_app.draw(m_recPauseBg);
        for (int i(0); i < 3; i++) m_app.draw(m_sprButton[i]);
        m_app.draw(m_sprButtonSelect);
        m_app.draw(m_txtContinue);
        m_app.draw(m_txtRestart);
        m_app.draw(m_txtQuit);
    }

    // message box
    drawMsgBox();

    // transition rectangle
    if (!m_levelStart || m_levelEnd)
    {
        m_app.draw(m_recTransition);
    }
}
