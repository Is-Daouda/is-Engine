#ifndef GAMESOUND_H_INCLUDED
#define GAMESOUND_H_INCLUDED

#include "../isEngineWrapper.h"
#include "../entity/parents/Name.h"
#include "../entity/parents/FilePath.h"

namespace is
{
////////////////////////////////////////////////////////////
/// Class for manage SFML Sound
////////////////////////////////////////////////////////////
class GameSound : public is::Name, public is::FilePath
{
public:
    GameSound(std::string soundName, std::string filePath):
        Name(soundName),
        FilePath(filePath)
#if defined(IS_ENGINE_HTML_5)
        , m_sb(filePath),
        m_snd(m_sb)
        {
            m_fileIsLoaded = true;
            // is::showLog("sound loaded name: " << soundName << "\n";
        }
#else
    {
        if (m_sb.loadFromFile(m_strFilePath))
        {
            m_snd.setBuffer(m_sb);
            m_fileIsLoaded = true;
        }
        else showLog("ERROR: Can't load sound : " + filePath);
    }
#endif
    virtual ~GameSound() {}

    void loadResources(std::string filePath)
    {
        #if !defined(IS_ENGINE_HTML_5)
        if (m_sb.loadFromFile(filePath))
        {
            m_strFilePath = filePath;
            m_snd.setBuffer(m_sb);
            m_fileIsLoaded = true;
        }
        else
        {
            m_fileIsLoaded = false;
            showLog("ERROR: Can't load sound : " + filePath);
        }
        #endif
    }

    /// Return sound buffer
    sf::SoundBuffer& getSoundBuffer() {return m_sb;}

    /// Return sound object
    sf::Sound& getSound() {return m_snd;}

private:
    sf::SoundBuffer m_sb;
    sf::Sound m_snd;
};
}

#endif // GAMESOUND_H_INCLUDED
