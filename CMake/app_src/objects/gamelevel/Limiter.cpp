#include "Limiter.h"

Limiter::Limiter(float x, float y) :
    MainObject(x, y)
{
    m_w = 32;
    m_h = 32;
    updateCollisionMask();
}
