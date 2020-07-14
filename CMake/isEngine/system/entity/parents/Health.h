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
    Health(int healt):
        m_health(healt),
        m_maxHealth(healt)
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
