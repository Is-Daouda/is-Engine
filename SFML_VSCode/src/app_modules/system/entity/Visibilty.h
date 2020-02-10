#ifndef VISIBILTY_H_INCLUDED
#define VISIBILTY_H_INCLUDED

namespace is
{
////////////////////////////////////////////////////////////
/// \brief Class for manage the visibility of object
////////////////////////////////////////////////////////////
class Visibility
{
public:
    Visibility(bool defaultVisibility = true) :
        m_visible(defaultVisibility)
    {}

    void setVisible(bool value)
    {
        m_visible = value;
    }

    bool getVisible() const
    {
        return m_visible;
    }

protected:
    bool m_visible;
};
}

#endif // VISIBILTY_H_INCLUDED
