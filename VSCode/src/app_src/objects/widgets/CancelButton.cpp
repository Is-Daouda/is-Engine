#include "CancelButton.h"

CancelButton::CancelButton() :
    MainObject(-999, -999)
{
    m_imageAlpha = 250;
}

void CancelButton::loadResources(sf::Texture &tex)
{
    is::createSprite(tex, m_sprParent, sf::IntRect(0, 0, 32, 32), sf::Vector2f(m_x, m_y), sf::Vector2f(16.f, 16.f));
}

void CancelButton::step(float const &DELTA_TIME)
{
    is::setSFMLObjX_Y(m_sprParent, m_x, m_y);
    if (m_imageAlpha > 80) m_imageAlpha -= static_cast<int>((4.f * is::VALUE_CONVERSION) * DELTA_TIME);
    else m_imageAlpha = 80;
    is::setSFMLObjAlpha(m_sprParent, m_imageAlpha);
}

void CancelButton::setAlpha(int val)
{
    m_imageAlpha = val;
}

bool CancelButton::isOn() const
{
    return (m_imageAlpha > 250);
}

void CancelButton::draw(sf::RenderTexture &surface)
{
    surface.draw(m_sprParent);
}
