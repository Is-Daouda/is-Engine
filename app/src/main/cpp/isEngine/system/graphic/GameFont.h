#ifndef GAMEFONT_H_INCLUDED
#define GAMEFONT_H_INCLUDED

#include "../isEngineWrapper.h"
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
    GameFont(std::string fontName, std::string filePath, float fontSize
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

    void loadResources(std::string filePath)
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
