#ifndef GAMEMUSIC_H_INCLUDED
#define GAMEMUSIC_H_INCLUDED

#include <SFML/Audio.hpp>
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
    GameMusic(std::string musicName, std::string filePath):
        Name(musicName),
        FilePath(filePath)
    {
        if (m_music.openFromFile(m_strFilePath)) m_fileIsLoaded = true;
        else showLog("ERROR: Can't load file : " + filePath);
    }

    void loadResources(std::string filePath)
    {
        if (m_music.openFromFile(filePath))
        {
            m_strFilePath = filePath;
            m_fileIsLoaded = true;
        }
        else
        {
            m_fileIsLoaded = false;
            showLog("ERROR: Can't load file : " + filePath);
        }
    }

    /// Return music object
    sf::Music& getMusic() {return m_music;}

private:
    sf::Music m_music;
};
}

#endif // GAMEMUSIC_H_INCLUDED
