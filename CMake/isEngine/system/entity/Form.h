#ifndef FORME_H_INCLUDED
#define FORME_H_INCLUDED

namespace is
{
////////////////////////////////////////////////////////////
/// \brief Class to manage rectangle collision
///
////////////////////////////////////////////////////////////
class Rectangle
{
public:
    Rectangle():
        m_left(0),
        m_top(0),
        m_right(0),
        m_bottom(0)
    {}
    int m_left, m_top, m_right, m_bottom;
};

////////////////////////////////////////////////////////////
/// \brief Class to manage circle collision
///
////////////////////////////////////////////////////////////
class Circle
{
public:
    Circle():
        m_x(0.f),
        m_y(0.f),
        m_raduis(0.f)
    {}
    float m_x, m_y, m_raduis;
};
}

#endif // FORME_H_INCLUDED
