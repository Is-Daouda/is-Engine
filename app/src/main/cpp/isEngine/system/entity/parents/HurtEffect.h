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

#ifndef HURTEFFECT_H_INCLUDED
#define HURTEFFECT_H_INCLUDED

#include "../MainObject.h"

namespace is
{
////////////////////////////////////////////////////////////
/// Provides methods to make a blind effect on a character
////////////////////////////////////////////////////////////
class HurtEffect
{
public:
    HurtEffect(sf::Sprite &sprParent) :
        m_spr(sprParent),
        m_isHurtTime(0.f)
    {}

    virtual void hurtStep(const float &DELTA_TIME)
    {
        if (m_isHurtTime > 0.f)
        {
            m_isHurtTime -= is::getMSecond(DELTA_TIME);
            is::setSFMLObjAlpha(m_spr, is::choose(5, 25, 200, 100, 25, 150));
        }
        else
        {
            m_isHurtTime = 0.f;
            is::setSFMLObjAlpha(m_spr, 255);
        }
    }

    virtual void setIsHurt(float duration = 100.f)
    {
        m_isHurtTime = duration;
    }

    virtual bool getIsHurt() const
    {
        return (m_isHurtTime > 0.f);
    }

protected:
    sf::Sprite &m_spr;
    float m_isHurtTime;
};
}
#endif // HURTEFFECT_H_INCLUDED
