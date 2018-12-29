#ifndef BLOC_H_INCLUDED
#define BLOC_H_INCLUDED

#include "../core/GameSystemExtended.h"
#include "../system/entity/MainObject.h"
#include "../system/entity/Destructible.h"

class Bloc : public is::MainObject, public is::Destructible
{
public:
    Bloc(float x, float y);
    ~Bloc();

    void draw(sf::RenderWindow &app);
};

#endif // BLOC_H_INCLUDED
