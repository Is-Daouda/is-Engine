#include "Bonus.h"


Bonus::Bonus(sf::Texture &m_tex, float x, float y):
    MainObject(x, y),
    Destructible(),
    m_oscillation(0.f),
    m_scale(1.f),
    m_alpha(255),
    m_touchPlayer(false)
{
    is::createSprite(m_tex, m_sprParent, sf::IntRect(0, 0, 32, 32), sf::Vector2f(m_x, m_y), sf::Vector2f(16.f, 16.f));
}

Bonus::~Bonus()
{
}

void Bonus::step(float const &DELTA_TIME)
{
    m_oscillation += is::radToDeg((0.05f * is::VALUE_CONVERSION) * DELTA_TIME);
    m_sprParent.rotate((10.f * is::VALUE_CONVERSION) * DELTA_TIME);
    if (m_touchPlayer)
    {
        if (m_alpha > 12)
        {
            m_alpha -= static_cast<int>((10.f * is::VALUE_CONVERSION) * DELTA_TIME);
            m_scale += (0.08f * is::VALUE_CONVERSION) * DELTA_TIME;
        }
        else m_destroy = true;
    }

    is::setSFMLObjX_Y(m_sprParent, m_x + 16.f, m_y + 8.f + is::lengthDirY(3.5f, m_oscillation));
    is::setSFMLObjScaleX_Y(m_sprParent, m_scale, m_scale);
    is::setSFMLObjAlpha(m_sprParent, m_alpha);
}

void Bonus::setTouchPlayer(bool val)
{
    m_touchPlayer = val;
}

bool Bonus::getTouchPlayer() const
{
    return m_touchPlayer;
}

void Bonus::draw(sf::RenderWindow &app)
{
    app.draw(m_sprParent);
}
