/*
  is::Engine (Infinity Solutions Engine)
  Copyright (C) 2018-2024 Is Daouda <isdaouda.n@gmail.com>

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

#ifndef TRANSITIONEFFECT_H_INCLUDED
#define TRANSITIONEFFECT_H_INCLUDED

#include "../display/GameDisplay.h"
#include "../entity/parents/Type.h"

namespace is
{
class TransitionEffect : public is::MainObject, public is::Type
{
public:
    enum Transition
    {
        FADE_IN,
        FADE_OUT
    };
    TransitionEffect(is::GameDisplay *scene);
    void step(const float &DELTA_TIME);
    void draw(is::Render &render);
    void setType(int type)
    {
        if ((m_type == FADE_OUT && type == FADE_IN) || (m_type == FADE_IN && type == FADE_OUT))
            m_transitionEnd = false;
        m_type = type;
    }
    bool getTransitionEnd(int type) const {return (m_transitionEnd && m_type == type);}
    sf::RectangleShape& getRecTransition() {return m_recTransition;}

private:
    is::GameDisplay *m_scene;
    sf::RectangleShape m_recTransition;
    bool m_transitionEnd;
};
}

#endif // TRANSITIONEFFECT_H_INCLUDED
