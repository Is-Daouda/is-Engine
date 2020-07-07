#ifndef BLOCKPHYSIC_H_INCLUDED
#define BLOCKPHYSIC_H_INCLUDED

#include "../../../isEngine/system/display/GameDisplay.h"
#include "Player.h"
#include "Limiter.h"

////////////////////////////////////////////////////////////
/// This class is used to manage the collision of blocks with
/// the other objects of the level.
/// Basically it is used to manage the collision loop of the
/// blocks
////////////////////////////////////////////////////////////
class BlockPhysic : public is::MainObject
{
public:
    BlockPhysic(is::GameDisplay *scene);
    void step(float const &DELTA_TIME);

private:
    is::GameDisplay *m_scene;
    float m_timeCancelCollision;
};

#endif // BLOCKPHYSIC_H_INCLUDED
