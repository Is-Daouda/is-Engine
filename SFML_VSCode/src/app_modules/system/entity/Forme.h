#ifndef FORME_H_INCLUDED
#define FORME_H_INCLUDED

namespace is
{
////////////////////////////////////////////////////////////
/// \brief Class to manage collision mask shape
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

class Point
{
public:
    Point():
        m_x(0),
        m_y(0)
    {}

    Point(float x, float y):
        m_x(x),
        m_y(y)
    {}

    float m_x, m_y;
};

class Line
{
public:
    Line():
        m_x1(0),
        m_y1(0),
        m_x2(0),
        m_y2(0)
    {}

    Line(float x1, float y1, float x2, float y2):
        m_x1(x1),
        m_y1(y1),
        m_x2(x2),
        m_y2(y2)
    {}

    float m_x1, m_y1, m_x2, m_y2;
};
}

#endif // FORME_H_INCLUDED
