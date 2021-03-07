/*
  is::Engine (Infinity Solution Engine)
  Copyright (C) 2018-2021 Is Daouda <isdaouda.n@gmail.com>

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
