#include "GameLevel.h"
void GameLevel::updateObjView()
{
    // move the view
    if (m_player.isActive())
    {
        if (m_player.getX() > (VIEW_W / 2) && m_player.getX() < (static_cast<float>(m_levelWidth * 32) - VIEW_W / 2))
            m_viewX = m_player.getX();
        if (m_player.getY() > (VIEW_H / 2) && m_player.getY() < (static_cast<float>(m_levelHeight * 32) - VIEW_H / 2))
            m_viewY = m_player.getY();
    }
    m_view.setCenter(m_viewX, m_viewY);
    m_app.setView(m_view);
}

void GameLevel::joystickController()
{
    // joystick controller
    bool mouseOnLJoystick(false);
    bool mouseOnRJoystick(false);

    // position joystick sprite
    is::setSFMLObjX_Y(m_sprJoystick[0], m_viewX - 260.f, m_viewY + 180.f);
    is::setSFMLObjX_Y(m_sprJoystick[1], m_viewX + 260.f, m_viewY + 180.f);

    // position joystick mask in relation to joystick sprite
    for (int i(0); i < 2; i++)
        is::setSFMLObjX_Y(m_recJoystickMask[i], is::getSFMLObjX(m_sprJoystick[i]), is::getSFMLObjY(m_sprJoystick[i]));

    // enable joystick when level start
    if (m_levelStart)
    {
        // check collision with left joystick
        if (is::mouseCollision(m_app, m_recJoystickMask[0])
            #if defined(__ANDROID__)
            || is::mouseCollision(m_app, m_recJoystickMask[0], 1)
            #endif // defined
            ) mouseOnLJoystick = true;

        // check collision with right joystick
        if (is::mouseCollision(m_app, m_recJoystickMask[1])
            #if defined(__ANDROID__)
            || is::mouseCollision(m_app, m_recJoystickMask[1], 1)
            #endif // defined
            ) mouseOnRJoystick = true;

        // avoid press key loop
        bool ignoreKeyPressedL = false;
        bool ignoreKeyPressedR = false;
        if (!mouseOnLJoystick && !mouseOnRJoystick && (m_gameSysExt.isPressed()
                                                        #if defined(__ANDROID__)
                                                        || m_gameSysExt.isPressed(1)
                                                        #endif // defined
                                                       )) m_gameSysExt.m_keyIsPressed = true;
        else
        {
            if (mouseOnLJoystick && m_rotationKeyPressed) ignoreKeyPressedL = true;
            if (mouseOnRJoystick && m_speedKeyPression) ignoreKeyPressedR = true;
        }

        // if left joystick mask pressed make rotation movement
        if ((m_gameSysExt.isPressed()
            #if defined(__ANDROID__)
            || m_gameSysExt.isPressed(1)
            #endif // defined
             ) && mouseOnLJoystick)
        {
            if (!ignoreKeyPressedL)
            {
                m_player.setRotationRight(!m_player.getRotationRight());
                is::setSFMLObjScaleX_Y(m_sprJoystick[0], ((m_player.getRotationRight()) ? -0.8f : 0.8f), 0.8f);
                m_rotationKeyPressed = true;
            }
        }
        else
        {
            is::setSFMLObjScaleX_Y(m_sprJoystick[0], ((!m_player.getRotationRight()) ? -1.f : 1.f), 1.f);
            m_rotationKeyPressed = false;
        }

        // if left joystick mask pressed make speed up
        if ((m_gameSysExt.isPressed()
            #if defined(__ANDROID__)
            || m_gameSysExt.isPressed(1)
            #endif // defined
             ) && mouseOnRJoystick)
        {
            if (!ignoreKeyPressedR)
            {
                is::setSFMLObjScale(m_sprJoystick[1], 0.8f);
                m_gameSysExt.playSound(m_sndSpeedUp);
                m_speedKeyPression = true;
            }
        }
        else
        {
            is::setSFMLObjScale(m_sprJoystick[1], 1.f);
            m_gameSysExt.stopSound(m_sndSpeedUp);
            m_speedKeyPression = false;
        }
    }
}

void GameLevel::updateObjPause(const float &DELTA_TIME)
{
    // update menu pause button
    m_buttonY = -80.f;
    for (int i(0); i < 3; i++) is::setSFMLObjX_Y(m_sprButton[i], m_viewX, m_viewY + m_buttonY + (48.f * i));
    is::setSFMLObjX_Y(m_txtContinue,     is::getSFMLObjX(m_sprButton[0]), is::getSFMLObjY(m_sprButton[0]) - 8.f);
    is::setSFMLObjX_Y(m_txtRestart,      is::getSFMLObjX(m_sprButton[1]), is::getSFMLObjY(m_sprButton[1]) - 8.f);
    is::setSFMLObjX_Y(m_txtQuit,         is::getSFMLObjX(m_sprButton[2]), is::getSFMLObjY(m_sprButton[2]) - 8.f);

    // position the pause background
    is::setSFMLObjX_Y(m_recPauseBg, m_viewX, m_viewY);

    // update pause button (locate in right-top corner)
    is::setSFMLObjX_Y(m_pauseBt, m_viewX + 285.f, m_viewY - 214.f);
    m_pauseBt.step(DELTA_TIME);
}

void GameLevel::updateObjBlockList()
{
    auto lowA = std::lower_bound(m_blockList.begin(), m_blockList.end(), m_player);
    auto upA  = std::upper_bound(m_blockList.begin(), m_blockList.end(), m_player);
    for (auto it = lowA; it != upA; ++it)
    {
        if (is::instanceExist(*it))
        {
            if (m_player.placeMetting(0, 0, (*it)))
            {
                m_player.setHurt(true);
            }
        }
    }
}

void GameLevel::updateObjBonusList(float const &DELTA_TIME)
{
    auto lowG = std::lower_bound(m_bonusList.begin(), m_bonusList.end(), m_player);
    auto upG  = std::upper_bound(m_bonusList.begin(), m_bonusList.end(), m_player);

    for (auto it = lowG; it != upG; ++it)
    {
        if (is::instanceExist((*it)))
        {
            if ((*it)->inViewRec(m_view, true))
            {
                if (m_player.isActive())
                {
                     if (is::pointDistance(m_player.getSprite().getPosition().x, m_player.getSprite().getPosition().y,
                                       (*it)->getX() + 16.f, (*it)->getY()+ 16.f) < 34.f && !(*it)->getTouchPlayer())
                    {
                        m_gameSysExt.m_currentBonus++;
                        m_gameSysExt.playSound(m_sndHaveBonus);

                        ////////////////////////////////////////////////////////////
                        // Android version code
                        #if defined(__ANDROID__)
                        m_gameSysExt.useVibrate(60);
                        #endif
                        ////////////////////////////////////////////////////////////
                        (*it)->setTouchPlayer(true);
                    }
                }
                (*it)->step(DELTA_TIME);

                // destroy bonus after get it
                if ((*it)->isDestroyed())
                {
                    delete (*it);
                    (*it) = 0;
                }
            }
        }
    }
}

void GameLevel::updateObjPlayer(float const &DELTA_TIME)
{
    if (m_player.isActive())
    {
        joystickController();

        if (m_gameSysExt.m_currentBonus == static_cast<int>(m_bonusList.size())) m_goal.setVisible(true);

        // player win when goal object is visible and he touch it
        if (!m_levelCompleted)
        {
            if (m_goal.getVisible())
            {
                if (is::pointDistance(is::getSFMLObjX(m_player.getSprite()), is::getSFMLObjY(m_player.getSprite()),
                                      m_goal.getX() + 16.f, m_goal.getY()+ 16.f) < 32.f)
                {
                    m_gameSysExt.stopSound(m_sndSpeedUp);
                    m_gameSysExt.playSound(m_sndPlayerWin);
                    m_levelCompleted = true;
                }
            }
        }
        else
        {
            m_player.setActive(false);
        }

        // level chronometer
        if (!m_timeUp)
        {
            m_gameTime.step(DELTA_TIME, is::VALUE_CONVERSION);
            if (m_gameTime.getTimeValue() == 0) m_timeUp = true;
        }
        else // player lose when chronometer attained zero
        {
            m_player.setHurt(true);
        }
    }

    // play explosion sound
    if (m_player.getHurt())
    {
        if (!m_playerExploseSnd)
        {
            ////////////////////////////////////////////////////////////
            #if defined(__ANDROID__)
            if (!m_keyBackPressed) m_gameSysExt.useVibrate(m_vibrateTimeDuration);
            #endif
            ////////////////////////////////////////////////////////////

            m_gameSysExt.stopSound(m_sndSpeedUp);
            m_gameSysExt.playSound(m_sndExplosion);
            m_playerExploseSnd = true;
        }
    }

    // update player
    m_player.step(DELTA_TIME, m_rotationKeyPressed, m_speedKeyPression);
}

void GameLevel::updateObjGameplayController(float const &DELTA_TIME)
{
    // update Goal
    m_goal.step(DELTA_TIME);

    // update and position HUD
    is::setSFMLObjX_Y(m_gameHud, m_viewX - 300.f, m_viewY - 220.f);
    m_gameHud.step(m_gameTime, static_cast<int>(m_bonusList.size()), m_gameSysExt);

    // update pause objects
    updateObjPause(DELTA_TIME);
}

