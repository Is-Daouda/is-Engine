/*
  is::Engine (Infinity Solutions Engine)
  Copyright (C) 2018-2023 Is Daouda <isdaouda.n@gmail.com>

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

#ifndef HEALTH_H_INCLUDED
#define HEALTH_H_INCLUDED

namespace is
{
////////////////////////////////////////////////////////////
/// Provides methods and attributes to manage the health of
/// a character
////////////////////////////////////////////////////////////
class Health
{
public:
    Health(int health):
        m_health(health),
        m_maxHealth(health)
    {}

    Health(int health, int maxHealth):
        m_health(health),
        m_maxHealth(maxHealth)
    {}

    virtual void setHealth(int val)
    {
        m_health = val;
        if (m_health < 0) m_health = 0;
        if (m_health > m_maxHealth) m_health = m_maxHealth;
    }

    virtual void setMaxHealth(int val)
    {
        m_maxHealth = val;
        if (m_maxHealth < 1) m_maxHealth = 1;
    }

    virtual void addHealth(int val = 1)
    {
        m_health += val;
        if (m_health < 0) m_health = 0;
        if (m_health > m_maxHealth) m_health = m_maxHealth;
    }

    virtual int getHealth() const
    {
        return m_health;
    }

    virtual int getMaxHealth() const
    {
        return m_maxHealth;
    }

protected:
    int m_health, m_maxHealth;
};
}
#endif // HEALTH_H_INCLUDED
