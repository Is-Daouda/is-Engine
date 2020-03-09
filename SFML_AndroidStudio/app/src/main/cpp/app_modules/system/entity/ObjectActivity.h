#ifndef OBJECTACTIVITY_H_INCLUDED
#define OBJECTACTIVITY_H_INCLUDED

namespace is
{
////////////////////////////////////////////////////////////
/// \brief Class to manage the activity state of object
////////////////////////////////////////////////////////////
class ObjectActivity
{
public:
    ObjectActivity(bool val = true) :
        m_active(val)
    {

    }

    virtual void setActive(bool val)
    {
        m_active = val;
    }

    virtual bool isActive() const
    {
        return m_active;
    }

protected:
    bool m_active;
};
}

#endif // OBJECTACTIVITY_H_INCLUDED
