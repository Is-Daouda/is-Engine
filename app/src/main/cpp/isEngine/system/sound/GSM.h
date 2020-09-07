#ifndef GSM_H_INCLUDED
#define GSM_H_INCLUDED

#include "../sound/GameSound.h"
#include "../sound/GameMusic.h"

namespace is
{
////////////////////////////////////////////////////////////
/// Class for manage SFML Sound and Music without using an
/// SFML object
////////////////////////////////////////////////////////////
class GSM
{
public:
    /// Game Sound container
    std::vector<std::shared_ptr<GameSound>> m_GSMsound;

    /// Game Music container
    std::vector<std::shared_ptr<GameMusic>> m_GSMmusic;

    //////////////////////////////////////////////////////
    /// \brief Allows to add SFML Sound in GSM container
    ///
    /// \param name of sound which will be used to identify it in the container in order to be able to access it
    /// \param filePath path of the sound file to add
    //////////////////////////////////////////////////////
    virtual void GSMaddSound(std::string name, std::string filePath)
    {
        auto obj = std::make_shared<GameSound>(name, filePath);
        m_GSMsound.push_back(obj);
    }

    //////////////////////////////////////////////////////
    /// \brief Allows to add SFML Music in GSM container
    ///
    /// \param name of msuic which will be used to identify it in the container in order to be able to access it
    /// \param filePath path of the music file to add
    //////////////////////////////////////////////////////
    virtual void GSMaddMusic(std::string name, std::string filePath)
    {
        auto obj = std::make_shared<GameMusic>(name, filePath);
        m_GSMmusic.push_back(obj);
    }

    /// Allows to get sound in container by his name
    virtual sf::Sound* GSMgetSound(std::string name)
    {
        WITH (m_GSMsound.size())
        {
            if (m_GSMsound[_I]->getName() == name)
            {
                return &m_GSMsound[_I]->getSound();
            }
        }
        is::showLog("ERROR: <" + name + "> sound does not exist!");
        return nullptr;
    }

    /// Allows to get music in container by his name
    virtual sf::Music* GSMgetMusic(std::string name)
    {
        WITH (m_GSMmusic.size())
        {
            if (m_GSMmusic[_I]->getName() == name)
            {
                return &m_GSMmusic[_I]->getMusic();
            }
        }
        is::showLog("ERROR: <" + name + "> music does not exist!");
        return nullptr;
    }
};
}
#endif // GSM_H_INCLUDED
