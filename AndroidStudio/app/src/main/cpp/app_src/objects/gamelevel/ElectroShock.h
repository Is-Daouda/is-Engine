#ifndef ELECTROSHOCK_H_INCLUDED
#define ELECTROSHOCK_H_INCLUDED

#include "../../../isEngine/system/entity/MainObject.h"

////////////////////////////////////////////////////////////
/// Represents the player's weapon in the game
////////////////////////////////////////////////////////////
class ElectroShock : public is::MainObject
{
public:
    ElectroShock(float x, float y);

    void step(float const &DELTA_TIME);
    void draw(sf::RenderTexture &surface);

private:
    sf::CircleShape m_circleElectro;
};

#endif // ELECTROSHOCK_H_INCLUDED
