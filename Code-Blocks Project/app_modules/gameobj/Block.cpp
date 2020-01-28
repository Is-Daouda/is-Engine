#include "../gameobj/Block.h"

Block::Block(float x, float y):
    MainObject(x, y)
{
    // define collision mask size
    m_w = 32;
    m_h = 32;

    // update collision mask
    updateCollisionMask();
}

Block::~Block()
{
}

void Block::draw(sf::RenderWindow &app)
{
    app.draw(m_sprParent);
}
