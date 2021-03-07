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

#include "GameKeyData.h"

namespace is
{
GameKeyData::GameKeyData(is::GameDisplay *scene) :
    MainObject(),
    m_keyPausePressed(false),
    m_keyLeftPressed(false),
    m_keyRightPressed(false),
    m_keyUpPressed(false),
    m_keyDownPressed(false),
    m_keyAPressed(false),
    m_keyBPressed(false),
    m_keyAUsed(false),
    m_keyBUsed(false),
    m_keyLeftUsed(false),
    m_keyRightUsed(false),
    m_keyUpUsed(false),
    m_keyDownUsed(false),
    m_disableAllKey(false),
    m_hideGamePad(false),
#if defined(__ANDROID__)
    m_moveObj(0.f),
#endif
    m_scene(scene)
{
    m_strName = "GameKeyData";

    m_moveKeyPressed   = V_KEY_NONE;
    m_actionKeyPressed = V_KEY_NONE;
    m_keyboardA        = is::GameConfig::KEY_A;
    m_keyboardB        = is::GameConfig::KEY_B;
    m_keyboardLeft     = is::GameConfig::KEY_LEFT;
    m_keyboardRight    = is::GameConfig::KEY_RIGHT;
    m_keyboardUp       = is::GameConfig::KEY_UP;
    m_keyboardDown     = is::GameConfig::KEY_DOWN;
    loadResources();
}

void GameKeyData::loadResources()
{
    auto &tex = m_scene->GRMaddTexture("game_pad", is::GameConfig::GUI_DIR + "game_pad.png");
    is::createSprite(tex, m_sprJoystick[0], sf::IntRect(0, 0, 134, 134), sf::Vector2f(0.f, 0.f), sf::Vector2f(67.f, 67.f));
    is::createSprite(tex, m_sprJoystick[1], sf::IntRect(134, ((!m_scene->getGameSystem().m_permutePadAB) ? 0 : 67), 144, 67),
                     sf::Vector2f(0.f, 0.f), sf::Vector2f(72.f, 37.f));
    is::setSFMLObjSize(m_recJoystickMask[0], 134.f, 134.f);
    is::setSFMLObjSize(m_recJoystickMask[1], 144.f, 74.f);

    for (int i(0); i < 2; i++)
    {
        is::setSFMLObjFillColor(m_recJoystickMask[i], sf::Color::Blue);
        is::centerSFMLObj(m_recJoystickMask[i]);
    }

    float const OBJ_SIZE(40.f), _ADD_SIZE(24.f), _ADD_ACT_SIZE(24.f), _ADD_W(16.f);
    is::setSFMLObjSize(m_recKeyLeftMask, OBJ_SIZE + _ADD_W, OBJ_SIZE + _ADD_SIZE);
    is::setSFMLObjSize(m_recKeyRightMask, OBJ_SIZE + _ADD_W, OBJ_SIZE + _ADD_SIZE);
    is::setSFMLObjSize(m_recKeyUpMask, OBJ_SIZE + _ADD_SIZE, OBJ_SIZE + _ADD_W);
    is::setSFMLObjSize(m_recKeyDownMask, OBJ_SIZE + _ADD_SIZE, OBJ_SIZE + _ADD_W);

    is::setSFMLObjSize(m_recKeyAMask, OBJ_SIZE + _ADD_ACT_SIZE, OBJ_SIZE + _ADD_ACT_SIZE);
    is::setSFMLObjSize(m_recKeyBMask, OBJ_SIZE + _ADD_ACT_SIZE, OBJ_SIZE + _ADD_ACT_SIZE);

    is::centerSFMLObj(m_recKeyLeftMask);
    is::centerSFMLObj(m_recKeyRightMask);
    is::centerSFMLObj(m_recKeyUpMask);
    is::centerSFMLObj(m_recKeyDownMask);
    is::centerSFMLObj(m_recKeyAMask);
    is::centerSFMLObj(m_recKeyBMask);
}

void GameKeyData::step(float const &DELTA_TIME)
{
    if (!keyAPressed()) m_keyAUsed = false;
    if (!keyBPressed()) m_keyBUsed = false;
    if (!keyLeftPressed()) m_keyLeftUsed = false;
    if (!keyRightPressed()) m_keyRightUsed = false;
    if (!keyUpPressed()) m_keyUpUsed = false;
    if (!keyDownPressed()) m_keyDownUsed = false;

    m_keyLeftPressed = keyLeftPressed();
    m_keyRightPressed = keyRightPressed();
    m_keyUpPressed = keyUpPressed();
    m_keyDownPressed = keyDownPressed();
    m_keyAPressed = keyAPressed();
    m_keyBPressed = keyBPressed();

    if (m_keyLeftPressed)
    {
        m_keyRightPressed = false;
        m_keyUpPressed = false;
        m_keyDownPressed = false;
#if !defined(__ANDROID__)
        m_moveKeyPressed = V_KEY_LEFT;
#endif
    }
    else if (m_keyRightPressed)
    {
        m_keyLeftPressed = false;
        m_keyUpPressed = false;
        m_keyDownPressed = false;
#if !defined(__ANDROID__)
        m_moveKeyPressed = V_KEY_RIGHT;
#endif
    }
    else if (m_keyUpPressed)
    {
        m_keyLeftPressed = false;
        m_keyRightPressed = false;
        m_keyDownPressed = false;
#if !defined(__ANDROID__)
        m_moveKeyPressed = V_KEY_UP;
#endif
    }
    else if (m_keyDownPressed)
    {
        m_keyLeftPressed = false;
        m_keyRightPressed = false;
        m_keyUpPressed = false;
#if !defined(__ANDROID__)
        m_moveKeyPressed = V_KEY_DOWN;
#endif
    }

#if defined(__ANDROID__)
    if (m_hideGamePad)
    {
        if (m_moveObj < 320.f) m_moveObj += (10.f * is::VALUE_CONVERSION) * DELTA_TIME;
    }
    else
    {
        is::decreaseVar(DELTA_TIME, m_moveObj, 8.f, 0.f, 10.f);
    }
    float moveMaskOnX(0.f), _LIMIT(-19.f), _POS(37.f);
    float const _W_SIZE(48.f);
    if (m_moveKeyPressed == V_KEY_LEFT)  moveMaskOnX = -6.f;
    if (m_moveKeyPressed == V_KEY_RIGHT) moveMaskOnX = 6.f;

    is::setSFMLObjX_Y(m_sprJoystick[0],
                      m_scene->getViewX() + m_scene->getGameSystem().m_padDirXPos,
                      m_scene->getViewY() + m_scene->getGameSystem().m_padDirYPos + m_moveObj);
    is::setSFMLObjX_Y(m_sprJoystick[1],
                      m_scene->getViewX() + m_scene->getGameSystem().m_padActionXPos,
                      m_scene->getViewY() + m_scene->getGameSystem().m_padActionYPos + m_moveObj);

    is::setSFMLObjX_Y(m_recKeyLeftMask, (is::getSFMLObjX(m_sprJoystick[0]) - _W_SIZE / 2.f) + _LIMIT,
                      is::getSFMLObjY(m_sprJoystick[0]));
    is::setSFMLObjX_Y(m_recKeyRightMask, (is::getSFMLObjX(m_sprJoystick[0]) + _W_SIZE / 2.f) - _LIMIT,
                      is::getSFMLObjY(m_sprJoystick[0]));
    is::setSFMLObjX_Y(m_recKeyUpMask, is::getSFMLObjX(m_sprJoystick[0]),
                      (is::getSFMLObjY(m_sprJoystick[0]) - _W_SIZE / 2.f) + _LIMIT);
    is::setSFMLObjX_Y(m_recKeyDownMask, is::getSFMLObjX(m_sprJoystick[0]),
                      (is::getSFMLObjY(m_sprJoystick[0]) + _W_SIZE / 2.f) - _LIMIT);

    is::setSFMLObjX_Y(m_recKeyAMask, is::getSFMLObjX(m_sprJoystick[1]) + (_POS * ((!m_scene->getGameSystem().m_permutePadAB) ? -1.f : 1.f)),
                      is::getSFMLObjY(m_sprJoystick[1]));
    is::setSFMLObjX_Y(m_recKeyBMask, is::getSFMLObjX(m_sprJoystick[1]) + (_POS * ((!m_scene->getGameSystem().m_permutePadAB) ? 1.f : -1.f)),
                      is::getSFMLObjY(m_sprJoystick[1]));

    for (int i(0); i < 2; i++)
    {
        is::setSFMLObjX_Y(m_recJoystickMask[i], is::getSFMLObjX(m_sprJoystick[i]) + ((i == 0) ? moveMaskOnX : 0.f), is::getSFMLObjY(m_sprJoystick[i]));
        is::setSFMLObjAlpha(m_sprJoystick[i], m_scene->getGameSystem().m_padAlpha);
    }
#else
    if (m_keyAPressed) m_actionKeyPressed = V_KEY_A;
    else if (m_keyBPressed) m_actionKeyPressed = V_KEY_B;
    else m_actionKeyPressed = V_KEY_NONE;
    if (!m_keyLeftPressed && !m_keyRightPressed && !m_keyUpPressed && !m_keyDownPressed) m_moveKeyPressed = V_KEY_NONE;
#endif // defined
}

void GameKeyData::draw(is::Render &surface)
{
    #if defined(__ANDROID__)
    if (m_moveObj < 320.f)
    {
        /*
         * This displays the virtual key mask on the screen
         *
        for (int i(0); i < 2; i++) surface.draw(m_recJoystickMask[i]);
        surface.draw(m_recKeyLeftMask);
        surface.draw(m_recKeyRightMask);
        surface.draw(m_recKeyUpMask);
        surface.draw(m_recKeyDownMask);
        surface.draw(m_recKeyAMask);
        surface.draw(m_recKeyBMask);
         */
        for (int i(0); i < 2; i++)
        {
            if (m_scene->getIsPlaying()) surface.draw(m_sprJoystick[i]);
        }
    }
    #endif // defined
}

bool GameKeyData::keyLeftPressed()
{
    if (m_disableAllKey) return false;

    //////////////////////////////////////////////////////////
    // Android version code
    #if defined(__ANDROID__)
    if (virtualKeyPressed(V_KEY_LEFT)) return true;
    #else
    if (m_scene->getGameSystem().keyIsPressed(m_keyboardLeft)) return true;
    #endif // defined
    //////////////////////////////////////////////////////////
    else return false;
}

bool GameKeyData::keyRightPressed()
{
    if (m_disableAllKey) return false;

    //////////////////////////////////////////////////////////
    // Android version code
    #if defined(__ANDROID__)
    if (virtualKeyPressed(V_KEY_RIGHT)) return true;
    #else
    if (m_scene->getGameSystem().keyIsPressed(m_keyboardRight)) return true;
    #endif // defined
    //////////////////////////////////////////////////////////
    else return false;
}

bool GameKeyData::keyUpPressed()
{
    if (m_disableAllKey) return false;

    //////////////////////////////////////////////////////////
    // Android version code
    #if defined(__ANDROID__)
    if (virtualKeyPressed(V_KEY_UP)) return true;
    #else
    if (m_scene->getGameSystem().keyIsPressed(m_keyboardUp)) return true;
    #endif // defined
    //////////////////////////////////////////////////////////
    else return false;
}

bool GameKeyData::keyDownPressed()
{
    if (m_disableAllKey) return false;

    //////////////////////////////////////////////////////////
    // Android version code
    #if defined(__ANDROID__)
    if (virtualKeyPressed(V_KEY_DOWN)) return true;
    #else
    if (m_scene->getGameSystem().keyIsPressed(m_keyboardDown)) return true;
    #endif // defined
    //////////////////////////////////////////////////////////
    else return false;
}

bool GameKeyData::keyAPressed()
{
    if (m_disableAllKey) return false;

    //////////////////////////////////////////////////////////
    // Android version code
    #if defined(__ANDROID__)
    if (virtualKeyPressed(V_KEY_A)) return true;
    #else
    if (m_scene->getGameSystem().keyIsPressed(m_keyboardA)) return true;
    #endif // defined
    //////////////////////////////////////////////////////////
    else return false;
}

bool GameKeyData::keyBPressed()
{
    if (m_disableAllKey) return false;

    //////////////////////////////////////////////////////////
    // Android version code
    #if defined(__ANDROID__)
    if (virtualKeyPressed(V_KEY_B)) return true;
    #else
    if (m_scene->getGameSystem().keyIsPressed(m_keyboardB)) return true;
    #endif // defined
    //////////////////////////////////////////////////////////
    else return false;
}

bool GameKeyData::virtualKeyPressed(VirtualKeyIndex virtualKeyIndex)
{
    // joystick controller
    bool mouseOnLJoystick(false);
    bool mouseOnRJoystick(false);

    if (virtualKeyIndex == V_KEY_LEFT || virtualKeyIndex == V_KEY_RIGHT || virtualKeyIndex == V_KEY_UP || virtualKeyIndex == V_KEY_DOWN)
    {
        // check collision with left joystick
        if (m_scene->mouseCollision(m_recJoystickMask[0])
            #if defined(__ANDROID__)
            || m_scene->mouseCollision(m_recJoystickMask[0], 1)
            #endif // defined
            ) mouseOnLJoystick = true;

        if (mouseOnLJoystick)
        {
            if (m_moveKeyPressed != V_KEY_NONE && m_moveKeyPressed != virtualKeyIndex)
            {
                if (m_scene->mouseCollision(m_recKeyLeftMask)
                    #if defined(__ANDROID__)
                    || m_scene->mouseCollision(m_recKeyLeftMask, 1)
                    #endif // defined
                    ) m_moveKeyPressed = V_KEY_LEFT;
                else if (m_scene->mouseCollision(m_recKeyRightMask)
                    #if defined(__ANDROID__)
                    || m_scene->mouseCollision(m_recKeyRightMask, 1)
                    #endif // defined
                         ) m_moveKeyPressed = V_KEY_RIGHT;
                else if (m_scene->mouseCollision(m_recKeyUpMask)
                    #if defined(__ANDROID__)
                    || m_scene->mouseCollision(m_recKeyUpMask, 1)
                    #endif // defined
                         ) m_moveKeyPressed = V_KEY_UP;
                else if (m_scene->mouseCollision(m_recKeyDownMask)
                    #if defined(__ANDROID__)
                    || m_scene->mouseCollision(m_recKeyDownMask, 1)
                    #endif // defined
                         ) m_moveKeyPressed = V_KEY_DOWN;
            }

            switch (m_moveKeyPressed)
            {
                case V_KEY_LEFT:
                    return (m_moveKeyPressed == virtualKeyIndex);
                break;
                case V_KEY_RIGHT:
                    return (m_moveKeyPressed == virtualKeyIndex);
                break;
                case V_KEY_UP:
                    return (m_moveKeyPressed == virtualKeyIndex);
                break;
                case V_KEY_DOWN:
                    return (m_moveKeyPressed == virtualKeyIndex);
                break;

                default: break;
            }
        }

        // if left joystick pressed
        if ((m_scene->getGameSystem().isPressed()
            #if defined(__ANDROID__)
            || m_scene->getGameSystem().isPressed(1)
            #endif // defined
             ) && mouseOnLJoystick)
        {
            switch (virtualKeyIndex)
            {
                case V_KEY_LEFT:
                    if (m_scene->mouseCollision(m_recKeyLeftMask)
                        #if defined(__ANDROID__)
                        || m_scene->mouseCollision(m_recKeyLeftMask, 1)
                        #endif // defined
                        )
                    {
                        m_moveKeyPressed = V_KEY_LEFT;
                        // is::showLog("L Pressed !");
                        return true;
                    }
                break;
                case V_KEY_RIGHT:
                    if (m_scene->mouseCollision(m_recKeyRightMask)
                        #if defined(__ANDROID__)
                        || m_scene->mouseCollision(m_recKeyRightMask, 1)
                        #endif // defined
                        )
                    {
                        m_moveKeyPressed = V_KEY_RIGHT;
                        // is::showLog("R Pressed !");
                        return true;
                    }
                break;
                case V_KEY_UP:
                    if (m_scene->mouseCollision(m_recKeyUpMask)
                        #if defined(__ANDROID__)
                        || m_scene->mouseCollision(m_recKeyUpMask, 1)
                        #endif // defined
                        )
                    {
                        m_moveKeyPressed = V_KEY_UP;
                        // is::showLog("U Pressed !");
                        return true;
                    }
                break;
                case V_KEY_DOWN:
                    if (m_scene->mouseCollision(m_recKeyDownMask)
                        #if defined(__ANDROID__)
                        || m_scene->mouseCollision(m_recKeyDownMask, 1)
                        #endif // defined
                        )
                    {
                        m_moveKeyPressed = V_KEY_DOWN;
                        // is::showLog("D Pressed !");
                        return true;
                    }
                break;

                default: break;
            }

        }
        m_moveKeyPressed = V_KEY_NONE;
    }

    if (virtualKeyIndex == V_KEY_A || virtualKeyIndex == V_KEY_B)
    {
        // check collision with right joystick
        if (m_scene->mouseCollision(m_recJoystickMask[1])
            #if defined(__ANDROID__)
            || m_scene->mouseCollision(m_recJoystickMask[1], 1)
            #endif // defined
            ) mouseOnRJoystick = true;

        // if left joystick pressed
        if ((m_scene->getGameSystem().isPressed()
            #if defined(__ANDROID__)
            || m_scene->getGameSystem().isPressed(1)
            #endif // defined
             ) && mouseOnRJoystick)
        {
            switch (virtualKeyIndex)
            {
                case V_KEY_A:
                    if (m_scene->mouseCollision(m_recKeyAMask)
                        #if defined(__ANDROID__)
                        || m_scene->mouseCollision(m_recKeyAMask, 1)
                        #endif // defined
                        )
                    {
                        m_actionKeyPressed = V_KEY_A;
                        // is::showLog("A Pressed !");
                        return true;
                    }
                break;

                case V_KEY_B:
                    if (m_scene->mouseCollision(m_recKeyBMask)
                        #if defined(__ANDROID__)
                        || m_scene->mouseCollision(m_recKeyBMask, 1)
                        #endif // defined
                        )
                    {
                        m_actionKeyPressed = V_KEY_B;
                        // is::showLog("B Pressed !");
                        return true;
                    }
                break;

                default: break;
            }
        }
        m_actionKeyPressed = V_KEY_NONE;
    }
    return false;
}
};
