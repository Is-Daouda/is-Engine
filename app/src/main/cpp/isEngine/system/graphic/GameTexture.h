#ifndef GAMETEXTURE_H_INCLUDED
#define GAMETEXTURE_H_INCLUDED

#include "../isEngineWrapper.h"
#include "../entity/parents/Name.h"
#include "../entity/parents/FilePath.h"

namespace is
{
////////////////////////////////////////////////////////////
/// Class for manage SFML Texture
////////////////////////////////////////////////////////////
class GameTexture : public is::Name, public is::FilePath
{
public:
    GameTexture(std::string textureName, std::string filePath):
        Name(textureName),
        FilePath(filePath)
#if defined(IS_ENGINE_HTML_5)
        , m_tex(filePath) {}
#else
    {
        if (m_tex.loadFromFile(m_strFilePath)) m_fileIsLoaded = true;
        else showLog("ERROR: Can't load texture : " + filePath);
    }
#endif
    virtual ~GameTexture() {}

    void loadResources(std::string filePath)
    {
        #if !defined(IS_ENGINE_HTML_5)
        if (m_tex.loadFromFile(filePath))
        {
            m_strFilePath = filePath;
            m_fileIsLoaded = true;
        }
        else
        {
            m_fileIsLoaded = false;
            showLog("ERROR: Can't load texture : " + filePath);
        }
        #endif
    }

    /// Return texture
    sf::Texture& getTexture() {return m_tex;}

private:
    sf::Texture m_tex;
};
}

#endif // GAMETEXTURE_H_INCLUDED
