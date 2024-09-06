/*
  is::Engine (Infinity Solutions Engine)
  Copyright (C) 2018-2024 Is Daouda <isdaouda.n@gmail.com>

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

#include "GameSlider.h"

namespace is
{
GameSlider::GameSlider(is::GameDisplay *scene):
    MainObject(),
    Type(SLIDE_NONE),
    m_scene(scene),
    m_slideDistance(64.f)
{
    m_strName = "GameSlider";
    #if defined(IS_ENGINE_USE_SDM)
    m_depth = 999999999; // will update this object before all others
    #endif
}

void GameSlider::step(const float &DELTA_TIME)
{
    if (m_scene->getGameSystem().isPressed(is::GameSystem::MOUSE))
    {
        sf::Vector2f cursor(m_scene->getCursor());
        if (static_cast<int>(m_time) == 0)
        {
            m_xStart = cursor.x;
            m_yStart = cursor.y;
        }
        m_time = 5.f;
        m_x = cursor.x;
        m_y = cursor.y;
        if (m_type == SLIDE_NONE)
        {
            if (m_x > m_xStart + m_slideDistance) m_type = SLIDE_RIGHT;
            else if (m_x < m_xStart - m_slideDistance) m_type = SLIDE_LEFT;
            else if (m_y < m_yStart - m_slideDistance) m_type = SLIDE_UP;
            else if (m_y > m_yStart + m_slideDistance) m_type = SLIDE_DOWN;
        }
    }
    if (m_time > 0.f) m_time -= is::getMSecond(DELTA_TIME);
    else
    {
        m_type = SLIDE_NONE;
        m_time = 0.f;
    }
}

GameSlider::SlideDirection GameSlider::getSlideDirection() const
{
    switch (m_type)
    {
        default: break;
        case 1: return SLIDE_UP; break;
        case 2: return SLIDE_DOWN; break;
        case 3: return SLIDE_RIGHT; break;
        case 4: return SLIDE_LEFT; break;
    }
    return SLIDE_NONE;
}
}
