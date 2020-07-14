#ifndef LIMITER_H_INCLUDED
#define LIMITER_H_INCLUDED

#include "../../../isEngine/system/entity/MainObject.h"

////////////////////////////////////////////////////////////
/// Allows to control the movement of movable blocks.
/// They change the direction of the blocks when they touch it
////////////////////////////////////////////////////////////
class Limiter : public is::MainObject
{
public:
    Limiter(float x, float y);
};

#endif // LIMITER_H_INCLUDED
