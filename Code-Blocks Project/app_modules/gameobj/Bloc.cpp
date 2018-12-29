#include "../gameobj/Bloc.h"

Bloc::Bloc(float x, float y):
    MainObject(x, y)
{
    // define collision mask size
    m_w = 32;
    m_h = 32;

    // update collision mask
    updateCollisionMask();
}

Bloc::~Bloc()
{
}

void Bloc::draw(sf::RenderWindow &app)
{
    app.draw(m_sprParent);
}
