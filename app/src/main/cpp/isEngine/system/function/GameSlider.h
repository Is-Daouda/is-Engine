#ifndef GAMESLIDER_H_INCLUDED
#define GAMESLIDER_H_INCLUDED

#include "../display/GameDisplay.h"
#include "../entity/parents/Type.h"

namespace is
{
class GameSlider : public is::MainObject, public is::Type
{
public:
    enum SlideDirection
    {
        SLIDE_NONE,
        SLIDE_UP,
        SLIDE_DOWN,
        SLIDE_RIGHT,
        SLIDE_LEFT
    };
    GameSlider(is::GameDisplay *scene);

    void step(float const &DELTA_TIME);
    SlideDirection getSlideDirection() const;

private:
    is::GameDisplay *m_scene;
    float m_slideDistance;
};
}

#endif // GAMESLIDER_H_INCLUDED
