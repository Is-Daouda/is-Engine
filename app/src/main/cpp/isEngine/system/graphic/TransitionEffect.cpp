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

#include "TransitionEffect.h"

namespace is
{
TransitionEffect::TransitionEffect(is::GameDisplay *scene):
    MainObject(),
    Type(FADE_OUT),
    m_scene(scene),
    m_transitionEnd(false)
{
    m_strName = "TransitionEffect";
    m_imageAlpha = 255;
    #if defined(IS_ENGINE_USE_SDM)
    m_depth = -999999999;
    #endif // defined

    // transition rectangle
    is::createRectangle(m_recTransition, sf::Vector2f(scene->getViewW() + 10.f, scene->getViewH() + 10.f),
                        sf::Color(0, 0, 0, m_imageAlpha), scene->getViewW() / 2.f, scene->getViewH() / 2.f);
}

void TransitionEffect::step(float const &DELTA_TIME)
{
    m_x = m_scene->getViewX();
    m_y = m_scene->getViewY();

    // transition fade out
    if (m_type == FADE_OUT)
    {
        if (m_imageAlpha > 5)
        {
            m_imageAlpha -= static_cast<int>((5.f * is::VALUE_CONVERSION) * DELTA_TIME);
            m_transitionEnd = false;
        }
        else
        {
            m_imageAlpha = 0;
            m_transitionEnd = true;
        }
    }

    // transition fade in
    if (m_type == FADE_IN)
    {
        if (m_imageAlpha < 250)
        {
            m_imageAlpha += static_cast<int>((5.f * is::VALUE_CONVERSION) * DELTA_TIME);
            m_transitionEnd = false;
        }
        else
        {
            m_imageAlpha = 255;
            m_transitionEnd = true;
        }
    }
    is::setSFMLObjFillColor(m_recTransition, sf::Color(0, 0, 0, m_imageAlpha));
    is::setSFMLObjX_Y(m_recTransition, m_x, m_y);
}

void TransitionEffect::draw(is::Render &render)
{
    is::draw(render, m_recTransition);
}
}
