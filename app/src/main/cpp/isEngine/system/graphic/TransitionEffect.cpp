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
