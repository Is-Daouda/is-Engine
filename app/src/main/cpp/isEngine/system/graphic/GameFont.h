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

#ifndef GAMEFONT_H_INCLUDED
#define GAMEFONT_H_INCLUDED

#include "../islibconnect/isLibConnect.h"
#include "../entity/parents/Name.h"
#include "../entity/parents/FilePath.h"

namespace is
{
////////////////////////////////////////////////////////////
/// Class for manage SFML Font
////////////////////////////////////////////////////////////
class GameFont : public is::Name, public is::FilePath
{
public:
    GameFont(const std::string& fontName, const std::string& filePath, float fontSize
            #if defined(IS_ENGINE_HTML_5)
            = is::GameConfig::DEFAULT_SFML_TEXT_SIZE
            #endif
             ):
        Name(fontName),
        FilePath(filePath),
        m_fontSize(fontSize)
#if defined(IS_ENGINE_HTML_5)
        , m_font(filePath, m_fontSize) {}
#else
    {
        if (m_font.loadFromFile(m_strFilePath)) m_fileIsLoaded = true;
        else showLog("ERROR: Can't load font : " + filePath);
    }
#endif
    virtual ~GameFont() {}

    void loadResources(const std::string& filePath)
    {
        #if !defined(IS_ENGINE_HTML_5)
        if (m_font.loadFromFile(filePath))
        {
            m_strFilePath = filePath;
            m_fileIsLoaded = true;
        }
        else
        {
            m_fileIsLoaded = false;
            showLog("ERROR: Can't load font : " + filePath);
        }
        #endif
    }

    /// Return font
    sf::Font& getFont() {return m_font;}

private:
    float m_fontSize;
    sf::Font m_font;
};
}

#endif // GAMEFONT_H_INCLUDED
