#include "ElectroShock.h"

ElectroShock::ElectroShock(float x, float y):
    MainObject(x, y),
    Destructible()
{
    m_imageScale = 0.f;
    m_circleElectro.setRadius(32.f);
    is::centerSFMLObj(m_circleElectro);
    is::setSFMLObjX_Y(m_circleElectro, m_x, m_y);
}

void ElectroShock::step(float const &DELTA_TIME)
{
    if (m_imageAlpha > 12)
    {
        m_circleElectro.rotate((-20.f * is::VALUE_CONVERSION) * DELTA_TIME);
        m_imageAlpha -= static_cast<int>((10.f * is::VALUE_CONVERSION) * DELTA_TIME);
        if (m_imageScale < 1.f) m_imageScale += (0.08f * is::VALUE_CONVERSION) * DELTA_TIME;
    }
    else m_destroy = true;
    m_x += (m_hsp * is::VALUE_CONVERSION) * DELTA_TIME;
    m_y += (m_vsp * is::VALUE_CONVERSION) * DELTA_TIME;
    is::setSFMLObjX_Y(m_circleElectro, m_x, m_y);
    is::setSFMLObjScaleX_Y(m_circleElectro, m_imageScale, m_imageScale / 3.3f);
    is::setSFMLObjFillColor(m_circleElectro, sf::Color(0, 0, 255, m_imageAlpha));
}

void ElectroShock::draw(sf::RenderTexture &surface)
{
    surface.draw(m_circleElectro);
}
