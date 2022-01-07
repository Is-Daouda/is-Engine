/*
  is::Engine (Infinity Solutions Engine)
  Copyright (C) 2018-2022 Is Daouda <isdaouda.n@gmail.com>

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
    explicit Name(const std::string& name = "Unknown"):
        m_strName(name)
    {}

    /// Set name
    virtual void setName(const std::string& name) {m_strName = name;}

    /// Return name
    virtual const std::string& getName() const noexcept {return m_strName;}

protected:
    std::string m_strName;
};
}

#endif // NAME_H_INCLUDED
