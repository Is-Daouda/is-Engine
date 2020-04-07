#include "Bonus.h"

Bonus::Bonus(sf::Texture &tex, BonusType type, float x, float y):
    MainObject(x, y),
    Destructible(),
    ScorePoint(10),
    Step(0),
    m_type(type),
    m_oscillation(0.f),
    m_regenerationTime(0),
    m_touchPlayer(false)
{
    is::createSprite(tex, m_sprParent, sf::IntRect(32 * m_type, 0, 32, 32), sf::Vector2f(m_x, m_y), sf::Vector2f(16.f, 16.f));
    switch(m_type)
    {
        case BONUS_NORMAL: m_y += 8.f;
        break;
        default: break;
    }
}

Bonus::~Bonus()
{
}

void Bonus::step(float const &DELTA_TIME)
{
    m_oscillation += is::radToDeg((0.05f * is::VALUE_CONVERSION) * DELTA_TIME);

    switch(m_type)
    {
        case BONUS_HEALTH:
        case BONUS_1_UP:
            if (m_touchPlayer) m_sprParent.rotate((-10.f * is::VALUE_CONVERSION) * DELTA_TIME);
        break;

        default :
        break;
    }

    if (m_touchPlayer)
    {
        if (m_imageAlpha > 12)
        {
            m_imageAlpha -= static_cast<int>((10.f * is::VALUE_CONVERSION) * DELTA_TIME);
            m_imageScale += (0.08f * is::VALUE_CONVERSION) * DELTA_TIME;
        }
        else m_destroy = true;
    }

    is::setSFMLObjX_Y(m_sprParent, m_x + 16.f, m_y + 8.f + is::lengthDirY(3.5f, m_oscillation));
    is::setSFMLObjScaleX_Y(m_sprParent, m_imageScale, m_imageScale);
    is::setSFMLObjAlpha(m_sprParent, m_imageAlpha);
}

void Bonus::setTouchPlayer(bool val)
{
    m_touchPlayer = val;
}

bool Bonus::getTouchPlayer() const
{
    return m_touchPlayer;
}

Bonus::BonusType Bonus::getType() const
{
    return m_type;
}

void Bonus::draw(sf::RenderTexture &surface)
{
    surface.draw(m_sprParent);
}
