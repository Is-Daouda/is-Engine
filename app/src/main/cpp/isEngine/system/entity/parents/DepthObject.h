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

#ifndef DepthOBJECT_H_INCLUDED
#define DepthOBJECT_H_INCLUDED

namespace is
{
////////////////////////////////////////////////////////////
/// Class for manage the depth of drawing object
////////////////////////////////////////////////////////////
class DepthObject
{
public:
    enum Depth
    {
        VERY_BIG_DEPTH = 99999,
        BIG_DEPTH = 999,
        NORMAL_DEPTH = 0,
        SMALL_DEPTH = -999,
        VERY_SMALL_DEPTH = -99999,
    };

    DepthObject(int depth) :
        m_depth(depth)
    {}

    virtual void setDepth(int val)
    {
        m_depth = val;
    }

    virtual int getDepth() const
    {
        return m_depth;
    }

protected:
    int m_depth;
};
}
#endif // DepthOBJECT_H_INCLUDED
