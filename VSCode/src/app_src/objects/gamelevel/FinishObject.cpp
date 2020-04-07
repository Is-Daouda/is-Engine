#include "FinishObject.h"

FinishObject::FinishObject(GameSystemExtended &gameSysExt):
    MainObject(),
    Step(0),
    m_gameSysExt(gameSysExt)
{
    m_w = 32;
    m_h = 32;
}

void FinishObject::loadResources(sf::Texture &tex)
{
    is::createSprite(tex, m_sprParent, sf::IntRect(0, 0, 32, 32), sf::Vector2f(m_x, m_y), sf::Vector2f(0.f, 0.f));
    updateCollisionMask();
}

void FinishObject::draw(sf::RenderTexture &surface)
{
    surface.draw(m_sprParent);
}
