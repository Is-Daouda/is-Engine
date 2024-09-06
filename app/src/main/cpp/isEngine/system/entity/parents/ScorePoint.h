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

#ifndef SCOREPOINT_H_INCLUDED
#define SCOREPOINT_H_INCLUDED

namespace is
{
////////////////////////////////////////////////////////////
/// Provides methods to assign a score point to a character
////////////////////////////////////////////////////////////
class ScorePoint
{
public:
    explicit ScorePoint(int point = 0) :
        m_scorePoint(point)
    {}

    virtual void setScorePoint(int point)
    {
        m_scorePoint = point;
    }

    virtual int getScorePoint() const
    {
        return m_scorePoint;
    }

protected:
    int m_scorePoint;
};
}
#endif // SCOREPOINT_H_INCLUDED
