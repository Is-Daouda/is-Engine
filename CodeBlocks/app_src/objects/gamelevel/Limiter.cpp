#include "Limiter.h"

Limiter::Limiter(float x, float y, bool secondFunction) :
    MainObject(x, y),
    m_secondFunction(secondFunction)
{
    m_w = 32;
    m_h = 32;
    updateCollisionMask();
}

void Limiter::draw(sf::RenderTexture &surface)
{
    surface.draw(m_sprParent);
}
