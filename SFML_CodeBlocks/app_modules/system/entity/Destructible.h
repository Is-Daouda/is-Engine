#ifndef DESTRUCTIBLE_H_INCLUDED
#define DESTRUCTIBLE_H_INCLUDED

namespace is
{
////////////////////////////////////////////////////////////
/// \brief Class to manage the destructible object
////////////////////////////////////////////////////////////
class Destructible
{
public:
    Destructible() :
        m_destroy(false)
    {

    }

    virtual void setDestroyed()
    {
        m_destroy = true;
    }

    virtual bool isDestroyed() const
    {
        return m_destroy;
    }

protected:
    bool m_destroy;
};
}

#endif // DESTRUCTIBLE_H_INCLUDED
