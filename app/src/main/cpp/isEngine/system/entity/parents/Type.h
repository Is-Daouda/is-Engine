#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED

namespace is
{
////////////////////////////////////////////////////////////
/// Class which allows to manage object types based on an
/// enum list
////////////////////////////////////////////////////////////
class Type
{
public:
    Type(int type):
        m_type(type)
    {}

    virtual void setType(int type)
    {
        m_type = type;
    }

    virtual int getType() const
    {
        return m_type;
    }

protected:
    int m_type;
};
}


#endif // TYPE_H_INCLUDED
