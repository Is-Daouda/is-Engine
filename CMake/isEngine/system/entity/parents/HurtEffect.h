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

    virtual void hurtStep(float const &DELTA_TIME)
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
