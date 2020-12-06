#ifndef NAME_H_INCLUDED
#define NAME_H_INCLUDED

#include <string>

namespace is
{
////////////////////////////////////////////////////////////
/// Class for manage the name of object
////////////////////////////////////////////////////////////
class Name
{
public:
    explicit Name(std::string name = "Unknown"):
        m_strName(name)
    {}

    /// Set name
    virtual void setName(std::string name) {m_strName = name;}

    /// Return name
    virtual const std::string& getName() const noexcept {return m_strName;}

protected:
    std::string m_strName;
};
}

#endif // NAME_H_INCLUDED
