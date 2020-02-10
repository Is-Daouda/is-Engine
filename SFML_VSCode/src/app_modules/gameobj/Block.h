#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include "../core/GameSystemExtended.h"
#include "../system/entity/MainObject.h"
#include "../system/entity/Destructible.h"

class Block : public is::MainObject, public is::Destructible
{
public:
    Block(float x, float y);
    ~Block();

    void draw(sf::RenderWindow &app);
};

#endif // BLOCK_H_INCLUDED
