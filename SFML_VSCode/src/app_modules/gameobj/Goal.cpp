#include "Goal.h"

Goal::Goal() :
    is::MainObject(),
    is::Visibility(false),
    m_scale(2.f),
    m_alpha(0)
{
}

void Goal::loadResources(sf::Texture &tex)
{
    is::createSprite(tex, m_sprParent, sf::IntRect(0, 0, 32, 32), sf::Vector2f(m_x, m_y), sf::Vector2f(16.f, 16.f));
}

void Goal::step(const float &DELTA_TIME)
{
    if (m_visible)
    {
        if (m_alpha < 249)
        {
            m_sprParent.rotate((15.f * is::VALUE_CONVERSION) * DELTA_TIME);
            m_alpha += static_cast<int>((5.f * is::VALUE_CONVERSION) * DELTA_TIME);
            if (m_scale > 1.f) m_scale -= (0.08f * is::VALUE_CONVERSION) * DELTA_TIME;
        }
        else is::setSFMLObjAngle(m_sprParent, 0.f);
    }
    is::setSFMLObjX_Y(m_sprParent, m_x + 16.f, m_y + 16.f);
    is::setSFMLObjScaleX_Y(m_sprParent, m_scale, m_scale);
    is::setSFMLObjAlpha(m_sprParent, m_alpha);
}

void Goal::draw(sf::RenderWindow &app)
{
    if (m_visible)
    {
        app.draw(m_sprParent);
    }
}
