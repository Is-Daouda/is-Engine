/*
  is::Engine (Infinity Solutions Engine)
  Copyright (C) 2018-2023 Is Daouda <isdaouda.n@gmail.com>

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

#ifndef FILEPATH_H_INCLUDED
#define FILEPATH_H_INCLUDED

namespace is
{
////////////////////////////////////////////////////////////
/// class to manage the path of a file
////////////////////////////////////////////////////////////
class FilePath
{
public:
    FilePath(const std::string& filePath):
        m_strFilePath(filePath),
        m_fileIsLoaded(false)
    {}

    /// Set file path
    virtual void setFilePath(const std::string& filePath) {m_strFilePath = filePath;}

    /// Return file path
    virtual const std::string& getFilePath() const noexcept {return m_strFilePath;}

    /// Allows to know if file is loaded
    virtual bool getFileIsLoaded() const {return m_fileIsLoaded;}

protected:
    std::string m_strFilePath;
    bool m_fileIsLoaded;
};
}

#endif // FILEPATH_H_INCLUDED
