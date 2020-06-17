#ifndef VISIBILTY_H_INCLUDED
#define VISIBILTY_H_INCLUDED

namespace is
{
////////////////////////////////////////////////////////////
/// Class for manage the visibility of object
////////////////////////////////////////////////////////////
class Visibility
{
public:
    explicit Visibility(bool defaultVisibility = true) :
        m_visible(defaultVisibility)
    {}

    virtual void setVisible(bool value)
    {
        m_visible = value;
    }

    virtual bool getVisible() const
    {
        return m_visible;
    }

protected:
    bool m_visible;
};
}

#endif // VISIBILTY_H_INCLUDED
