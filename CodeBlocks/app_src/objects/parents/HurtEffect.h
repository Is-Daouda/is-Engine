#ifndef HURTEFFECT_H_INCLUDED
#define HURTEFFECT_H_INCLUDED

#include "../../system/entity/MainObject.h"

////////////////////////////////////////////////////////////
/// Provides methods to make a blind effect on a character
////////////////////////////////////////////////////////////
class HurtEffect
{
public:
    HurtEffect(sf::Sprite &sprParent) :
        m_sprParent(sprParent),
        m_isHurtTime(0.f)
    {}

    void hurtStep(float const &DELTA_TIME)
    {
        if (m_isHurtTime > 0.f)
        {
            m_isHurtTime -= DELTA_TIME;
            is::setSFMLObjAlpha(m_sprParent, is::choose(5, 25, 200, 100, 25, 150));
        }
        else
        {
            m_isHurtTime = 0.f;
            is::setSFMLObjAlpha(m_sprParent, 255);
        }
    }

    void setIsHurt()
    {
        m_isHurtTime = 100.f;
    }

    bool getIsHurt() const
    {
        return (m_isHurtTime > 0.f);
    }

protected:
    sf::Sprite &m_sprParent;
    float m_isHurtTime;
};

#endif // HURTEFFECT_H_INCLUDED
