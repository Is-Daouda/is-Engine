#ifndef LIMITER_H_INCLUDED
#define LIMITER_H_INCLUDED

#include "../../../isEngine/system/entity/MainObject.h"

class Limiter : public is::MainObject
{
public:
    Limiter(float x, float y, bool secondFunction = false);
    bool m_secondFunction;
    void draw(sf::RenderTexture &surface);
};

#endif // LIMITER_H_INCLUDED
