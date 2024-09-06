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

#ifndef GAMEMUSIC_H_INCLUDED
#define GAMEMUSIC_H_INCLUDED

#include "../islibconnect/isLibConnect.h"
#include "../entity/parents/Name.h"
#include "../entity/parents/FilePath.h"

namespace is
{
////////////////////////////////////////////////////////////
/// Class for manage SFML Music
////////////////////////////////////////////////////////////
class GameMusic : public is::Name, public is::FilePath
{
public:
    GameMusic(const std::string& musicName, const std::string& filePath):
        Name(musicName),
        FilePath(filePath)
    {
        if (m_music.openFromFile(m_strFilePath)) m_fileIsLoaded = true;
        //else showLog("ERROR: Can't load music : " + filePath);
    }

    virtual ~GameMusic() {}

    void loadResources(const std::string&filePath)
    {
        if (m_music.openFromFile(filePath))
        {
            m_strFilePath = filePath;
            m_fileIsLoaded = true;
        }
        else
        {
            m_fileIsLoaded = false;
            //showLog("ERROR: Can't load music : " + filePath);
        }
    }

    /// Return music object
    sf::Music& getMusic()
    {
        return m_music;
    }

private:
    sf::Music m_music;
};
}

#endif // GAMEMUSIC_H_INCLUDED
