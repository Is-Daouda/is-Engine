/*
  is::Engine (Infinity Solutions Engine)
  Copyright (C) 2018-2024 Is Daouda <isdaouda.n@gmail.com>

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
