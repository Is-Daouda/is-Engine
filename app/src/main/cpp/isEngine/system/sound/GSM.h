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

#ifndef GSM_H_INCLUDED
#define GSM_H_INCLUDED

#include <memory>
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

#if !defined(__ANDROID__)
    /// Game Music container
    std::vector<std::shared_ptr<GameMusic>> m_GSMmusic;
#endif
    //////////////////////////////////////////////////////
    /// \brief Allows to add SFML Sound in GSM container
    ///
    /// \param name of sound which will be used to identify
    /// it in the container in order to be able to access it
    /// \param filePath path of the sound file to add
    //////////////////////////////////////////////////////
    virtual void GSMaddSound(const std::string& name, const std::string& filePath)
    {
        auto obj = std::make_shared<GameSound>(name, filePath);
        m_GSMsound.push_back(obj);
    }

    //////////////////////////////////////////////////////
    /// \brief Allows to add SFML Music in GSM container
    ///
    /// \param name of music which will be used to identify
    /// it in the container in order to be able to access it
    /// \param filePath path of the music file to add
    //////////////////////////////////////////////////////
    virtual void GSMaddMusic(const std::string& name, const std::string& filePath)
    {
#if defined(__ANDROID__)
        GSMaddSound(name, filePath);
#else
        auto obj = std::make_shared<GameMusic>(name, filePath);
        m_GSMmusic.push_back(obj);
#endif
    }

    /// Allows to set sound loop
    virtual void GSMsetSoundLoop(const std::string& name, bool loop)
    {
        WITH (m_GSMsound.size())
        {
            if (m_GSMsound[_I]->getName() == name)
            {
                m_GSMsound[_I]->getSound().setLoop(loop);
                return;
            }
        }
        is::showLog("ERROR: <" + name + "> sound does not exist!");
    }

    /// Allows to set music loop
    virtual void GSMsetMusicLoop(const std::string& name, bool loop)
    {
#if defined(__ANDROID__)
        GSMsetSoundLoop(name, loop);
#else
        WITH (m_GSMmusic.size())
        {
            if (m_GSMmusic[_I]->getName() == name)
            {
                m_GSMmusic[_I]->getMusic().setLoop(loop);
                return;
            }
        }
        is::showLog("ERROR: <" + name + "> music does not exist!");
#endif
    }

    /// Allows to get sound in container by his name
    virtual sf::Sound* GSMgetSound(const std::string& name, bool showError = true)
    {
        WITH (m_GSMsound.size())
        {
            if (m_GSMsound[_I]->getName() == name)
            {
                return &m_GSMsound[_I]->getSound();
            }
        }
        if (showError) is::showLog("ERROR: <" + name + "> sound does not exist!");
        return nullptr;
    }

    /// Allows to get music in container by his name
    virtual
#if defined(__ANDROID__)
    sf::Sound*
#else
    sf::Music*
#endif
    GSMgetMusic(const std::string& name, bool showError = true)
    {
        WITH (
#if defined(__ANDROID__)
                m_GSMsound.size()
#else
                m_GSMmusic.size()
#endif
                )
        {
            if (
#if defined(__ANDROID__)
                    m_GSMsound[_I]->
#else
                    m_GSMmusic[_I]->
#endif
            getName() == name)
            {
                return
#if defined(__ANDROID__)
                        &m_GSMsound[_I]->getSound();
#else
                        &m_GSMmusic[_I]->getMusic();
#endif
            }
        }
        if (showError) is::showLog("ERROR: <" + name + "> music does not exist!");
        return nullptr;
    }
};
}
#endif // GSM_H_INCLUDED
