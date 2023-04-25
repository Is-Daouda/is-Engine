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

//#if !defined(__ANDROID__)
    /// Game Music container
    std::vector<std::shared_ptr<GameMusic>> m_GSMmusic;
//#endif
    //////////////////////////////////////////////////////
    /// \brief Allows to add SFML Sound in container
    ///
    /// \param name of sound which will be used to identify
    /// it in the container in order to be able to access it
    /// \param filePath path of the sound file to add
    //////////////////////////////////////////////////////
    virtual void GSMaddSound(const std::string& name, const std::string& filePath)
    {
        if (!soundFileExists(filePath))
        {
            auto obj = std::make_shared<GameSound>(name, filePath);
            m_GSMsound.push_back(obj);
        }
        else is::showLog("WARNING: <" + name + "> sound has already been added!");
    }

    //////////////////////////////////////////////////////
    /// \brief Allows to add existing sound in container
    ///
    /// \param sound object
    //////////////////////////////////////////////////////
    void GSMaddSoundObject(std::shared_ptr<GameSound> sound, bool showError = true)
    {
        if (!soundFileExists(sound->getFilePath())) m_GSMsound.push_back(sound);
        else
        {
            if (showError) is::showLog("WARNING: <" + sound->getName() + "> sound has already been added!");
        }
    }

    //////////////////////////////////////////////////////
    /// \brief Allows to add SFML Music in container
    ///
    /// \param name of music which will be used to identify
    /// it in the container in order to be able to access it
    /// \param filePath path of the music file to add
    //////////////////////////////////////////////////////
    virtual void GSMaddMusic(const std::string& name, const std::string& filePath)
    {
//#if defined(__ANDROID__)
//        GSMaddSound(name, filePath);
//#else
        if (!musicFileExists(filePath))
        {
            auto obj = std::make_shared<GameMusic>(name, filePath);
            m_GSMmusic.push_back(obj);
        }
        else is::showLog("WARNING: <" + name + "> music has already been added!");
//#endif
    }

    //////////////////////////////////////////////////////
    /// \brief Allows to add existing music in container
    ///
    /// \param music object
    //////////////////////////////////////////////////////
    void GSMaddMusicObject(std::shared_ptr<
//#if defined(__ANDROID__)
//                           GameSound
//#else
                           GameMusic
//#endif
                           >music, bool showError = true)
    {
//#if defined(__ANDROID__)
//        GSMaddSoundObject(music);
//#else
        if (!musicFileExists(music->getFilePath())) m_GSMmusic.push_back(music);
        else
        {
            if (showError) is::showLog("WARNING: <" + music->getName() + "> music has already been added!");
        }
//#endif
    }

    /// Allows to set sound loop
    virtual void GSMsetSoundLoop(const std::string& name, bool loop)
    {
        WITH(m_GSMsound.size())
        {
            if (m_GSMsound[_I].get() != nullptr)
            {
                if (m_GSMsound[_I]->getName() == name && m_GSMsound[_I]->getFileIsLoaded())
                {
                    m_GSMsound[_I]->getSound().setLoop(loop);
                    return;
                }
            }
        }
        is::showLog("ERROR: Can't loop <" + name + "> sound because sound does not exist!");
    }

    /// Allows to set music loop
    virtual void GSMsetMusicLoop(const std::string& name, bool loop)
    {
//#if defined(__ANDROID__)
//        GSMsetSoundLoop(name, loop);
//#else
        WITH(m_GSMmusic.size())
        {
            if (m_GSMmusic[_I].get() != nullptr)
            {
                if (m_GSMmusic[_I]->getName() == name && m_GSMmusic[_I]->getFileIsLoaded())
                {
                    m_GSMmusic[_I]->getMusic().setLoop(loop);
                    return;
                }
            }
        }
        is::showLog("ERROR: Can't loop <" + name + "> music because music does not exist!");
//#endif
    }

    /// Allows to get sound in container by his name
    virtual sf::Sound* GSMgetSound(const std::string& name, bool showError = true)
    {
        WITH(m_GSMsound.size())
        {
            if (m_GSMsound[_I].get() != nullptr)
            {
                if (m_GSMsound[_I]->getName() == name && m_GSMsound[_I]->getFileIsLoaded())
                {
                    return &m_GSMsound[_I]->getSound();
                }
            }
        }
        if (showError) is::showLog("ERROR: <" + name + "> sound does not exist!");
        return nullptr;
    }

    /// Allows to get music in container by his name
    virtual
//#if defined(__ANDROID__)
//    sf::Sound*
//#else
    sf::Music*
//#endif
    GSMgetMusic(const std::string& name, bool showError = true)
    {
        WITH(
//#if defined(__ANDROID__)
//                m_GSMsound.size()
//#else
                m_GSMmusic.size()
//#endif
                )
        {
            if (
//#if defined(__ANDROID__)
//                m_GSMsound[_I].get() != nullptr
//#else
                m_GSMmusic[_I].get() != nullptr
//#endif
                )
            {
                if (
//#if defined(__ANDROID__)
//                    m_GSMsound[_I]->getName() == name && m_GSMsound[_I]->getFileIsLoaded()
//#else
                    m_GSMmusic[_I]->getName() == name && m_GSMmusic[_I]->getFileIsLoaded()
//#endif
                    )
                {
                    return
//#if defined(__ANDROID__)
//                        &m_GSMsound[_I]->getSound();
//#else
                        &m_GSMmusic[_I]->getMusic();
//#endif
                }
            }
        }
        if (showError) is::showLog("ERROR: <" + name + "> music does not exist!");
        return nullptr;
    }

    /// Allows to pause sound in container by his name
    virtual void GSMpauseSound(const std::string& name)
    {
        bool soundExist(false);
        WITH(m_GSMsound.size())
        {
            if (m_GSMsound[_I].get() != nullptr)
            {
                if (m_GSMsound[_I]->getName() == name)
                {
                    soundExist = true;
                    if (m_GSMsound[_I]->getFileIsLoaded())
                    {
                        if (is::checkSFMLSndState(m_GSMsound[_I]->getSound(), is::SFMLSndStatus::Playing)) m_GSMsound[_I]->getSound().pause();
                    }
                    else is::showLog("ERROR: Can't pause <" + name + "> sound!");
                    break;
                }
            }
        }
        if (!soundExist) is::showLog("ERROR: Can't pause <" + name + "> sound because sound does not exist!");
    }

    /// Allows to stop sound in container by his name
    virtual void GSMstopSound(const std::string& name)
    {
        bool soundExist(false);
        WITH(m_GSMsound.size())
        {
            if (m_GSMsound[_I].get() != nullptr)
            {
                if (m_GSMsound[_I]->getName() == name)
                {
                    soundExist = true;
                    if (m_GSMsound[_I]->getFileIsLoaded())
                    {
                        if (is::checkSFMLSndState(m_GSMsound[_I]->getSound(), is::SFMLSndStatus::Playing)) m_GSMsound[_I]->getSound().stop();
                    }
                    else is::showLog("ERROR: Can't stop <" + name + "> sound!");
                    break;
                }
            }
        }
        if (!soundExist) is::showLog("ERROR: Can't stop <" + name + "> sound because sound does not exist!");
    }

    /// Allows to pause music in container by his name
    virtual void GSMpauseMusic(const std::string& name)
    {
//    #if defined(__ANDROID__)
//        GSMpauseSound(name);
//    #else
        bool musicExist(false);
        WITH(m_GSMmusic.size())
        {
            if (m_GSMmusic[_I].get() != nullptr)
            {
                if (m_GSMmusic[_I]->getName() == name)
                {
                    musicExist = true;
                    if (m_GSMmusic[_I]->getFileIsLoaded())
                    {
                        if (is::checkSFMLSndState(m_GSMmusic[_I]->getMusic(), is::SFMLSndStatus::Playing)) m_GSMmusic[_I]->getMusic().pause();
                    }
                    else is::showLog("ERROR: Can't pause <" + name + "> music!");
                    break;
                }
            }
        }
        if (!musicExist) is::showLog("ERROR: Can't pause <" + name + "> music because music does not exist!");
//    #endif
    }

    /// Allows to stop music in container by his name
    virtual void GSMstopMusic(const std::string& name)
    {
//    #if defined(__ANDROID__)
//        GSMstopSound(name);
//    #else
        bool musicExist(false);
        WITH(m_GSMmusic.size())
        {
            if (m_GSMmusic[_I].get() != nullptr)
            {
                if (m_GSMmusic[_I]->getName() == name)
                {
                    musicExist = true;
                    if (m_GSMmusic[_I]->getFileIsLoaded())
                    {
                        if (is::checkSFMLSndState(m_GSMmusic[_I]->getMusic(), is::SFMLSndStatus::Playing)) m_GSMmusic[_I]->getMusic().stop();
                    }
                    else is::showLog("ERROR: Can't stop <" + name + "> music!");
                    break;
                }
            }
        }
        if (!musicExist) is::showLog("ERROR: Can't stop <" + name + "> music because music does not exist!");
//    #endif
    }

    /// Allows to delete sound in container by his name
    virtual void GSMdeleteSound(const std::string& name)
    {
        int soundId(-1);
        WITH(m_GSMsound.size())
        {
            if (m_GSMsound[_I].get() != nullptr)
            {
                if (m_GSMsound[_I]->getName() == name)
                {
                    soundId = _I;
                    break;
                }
            }
        }
        if (soundId == -1) is::showLog("ERROR: Can't delete <" + name + "> sound because sound does not exist!");
        else
        {
            m_GSMsound[soundId].reset();
            m_GSMsound[soundId] = nullptr;
        }
    }

    /// Allows to delete music in container by his name
    virtual void GSMdeleteMusic(const std::string& name)
    {
//    #if defined(__ANDROID__)
//        GSMdeleteSound(name);
//    #else
        int musicId(-1);
        WITH(m_GSMmusic.size())
        {
            if (m_GSMmusic[_I].get() != nullptr)
            {
                if (m_GSMmusic[_I]->getName() == name)
                {
                    musicId = _I;
                    break;
                }
            }
        }
        if (musicId == -1) is::showLog("ERROR: Can't delete <" + name + "> music because music does not exist!");
        else
        {
            m_GSMmusic[musicId].reset();
            m_GSMmusic[musicId] = nullptr;
        }
//    #endif
    }

////////////////////////////////////////////////////////////
/// These methods below have the same role as those above.
/// The difference here is that their name starting with GSM
/// is replaced by GRM (Game Resource Manager).
////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////
    /// \brief Allows to add SFML Sound in container
    ///
    /// \param name of sound which will be used to identify
    /// it in the container in order to be able to access it
    /// \param filePath path of the sound file to add
    //////////////////////////////////////////////////////
    virtual void GRMaddSound(const std::string& name, const std::string& filePath)
    {
        GSMaddSound(name, filePath);
    }

    //////////////////////////////////////////////////////
    /// \brief Allows to add existing sound in container
    ///
    /// \param sound object
    //////////////////////////////////////////////////////
    void GRMaddSoundObject(std::shared_ptr<GameSound> sound, bool showError = true)
    {
        GSMaddSoundObject(sound, showError);
    }

    //////////////////////////////////////////////////////
    /// \brief Allows to add SFML Music in container
    ///
    /// \param name of music which will be used to identify
    /// it in the container in order to be able to access it
    /// \param filePath path of the music file to add
    //////////////////////////////////////////////////////
    virtual void GRMaddMusic(const std::string& name, const std::string& filePath)
    {
//#if defined(__ANDROID__)
//        GSMaddSound(name, filePath);
//#else
        GSMaddMusic(name, filePath);
//#endif
    }

    //////////////////////////////////////////////////////
    /// \brief Allows to add existing music in container
    ///
    /// \param music object
    //////////////////////////////////////////////////////
    void GRMaddMusicObject(std::shared_ptr<
//#if defined(__ANDROID__)
//                           GameSound
//#else
                           GameMusic
//#endif
                           >music, bool showError = true)
    {
//#if defined(__ANDROID__)
//        GSMaddSoundObject(music, showError);
//#else
        GSMaddMusicObject(music, showError);
//#endif
    }

    /// Allows to set sound loop
    virtual void GRMsetSoundLoop(const std::string& name, bool loop)
    {
        GSMsetSoundLoop(name, loop);
    }

    /// Allows to set music loop
    virtual void GRMsetMusicLoop(const std::string& name, bool loop)
    {
//#if defined(__ANDROID__)
//        GSMsetSoundLoop(name, loop);
//#else
        GSMsetMusicLoop(name, loop);
//#endif
    }

    /// Allows to get sound in container by his name
    virtual sf::Sound* GRMgetSound(const std::string& name, bool showError = true)
    {
        return GSMgetSound(name, showError);
    }

    /// Allows to get music in container by his name
    virtual
//#if defined(__ANDROID__)
//    sf::Sound*
//#else
    sf::Music*
//#endif
    GRMgetMusic(const std::string& name, bool showError = true)
    {
        return
//#if defined(__ANDROID__)
//            GSMgetSound(name, showError);
//#else
            GSMgetMusic(name, showError);
//#endif
    }

    /// Allows to pause sound in container by his name
    virtual void GRMpauseSound(const std::string& name)
    {
        GSMpauseSound(name);
    }

    /// Allows to stop sound in container by his name
    virtual void GRMstopSound(const std::string& name)
    {
        GSMstopSound(name);
    }

    /// Allows to pause music in container by his name
    virtual void GRMpauseMusic(const std::string& name)
    {
//    #if defined(__ANDROID__)
//        GSMpauseSound(name);
//    #else
        GSMpauseMusic(name);
//    #endif
    }

    /// Allows to stop music in container by his name
    virtual void GRMstopMusic(const std::string& name)
    {
//    #if defined(__ANDROID__)
//        GSMstopSound(name);
//    #else
        GSMstopMusic(name);
//    #endif
    }

    /// Allows to delete sound in container by his name
    virtual void GRMdeleteSound(const std::string& name)
    {
        GSMdeleteSound(name);
    }

    /// Allows to delete music in container by his name
    virtual void GRMdeleteMusic(const std::string& name)
    {
//    #if defined(__ANDROID__)
//        GSMdeleteSound(name);
//    #else
        GSMdeleteMusic(name);
//    #endif
    }

private:
    bool soundFileExists(const std::string& filePath) const
    {
        WITH(m_GSMsound.size())
        {
            if (m_GSMsound[_I].get() != nullptr)
            {
                if (m_GSMsound[_I]->getFilePath() == filePath) return true;
            }
        }
        return false;
    }

//#if !defined(__ANDROID__)
    bool musicFileExists(const std::string& filePath) const
    {
        WITH(m_GSMmusic.size())
        {
            if (m_GSMmusic[_I].get() != nullptr)
            {
                if (m_GSMmusic[_I]->getFilePath() == filePath) return true;
            }
        }
        return false;
    }
//#endif
};
}
#endif // GSM_H_INCLUDED
