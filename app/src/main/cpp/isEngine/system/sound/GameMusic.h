#ifndef GAMEMUSIC_H_INCLUDED
#define GAMEMUSIC_H_INCLUDED

#include "../isEngineWrapper.h"
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
#if defined(IS_ENGINE_HTML_5)
        , m_sb(filePath),
        m_music(m_sb) {m_fileIsLoaded = true;}
#else
    {
        if (m_music.openFromFile(m_strFilePath)) m_fileIsLoaded = true;
        else showLog("ERROR: Can't load music : " + filePath);
    }
#endif
    virtual ~GameMusic() {}

    void loadResources(std::string filePath)
    {
        #if !defined(IS_ENGINE_HTML_5)
        if (m_music.openFromFile(filePath))
        {
            m_strFilePath = filePath;
            m_fileIsLoaded = true;
        }
        else
        {
            m_fileIsLoaded = false;
            showLog("ERROR: Can't load music : " + filePath);
        }
        #endif
    }

    /// Return music object
    sf::Music& getMusic()
    {
        return m_music;
    }

private:
    #if defined(IS_ENGINE_HTML_5)
    sf::SoundBuffer m_sb;
    #endif
    sf::Music m_music;
};
}

#endif // GAMEMUSIC_H_INCLUDED
