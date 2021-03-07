/*
  is::Engine (Infinity Solution Engine)
  Copyright (C) 2018-2021 Is Daouda <isdaouda.n@gmail.com>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

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
