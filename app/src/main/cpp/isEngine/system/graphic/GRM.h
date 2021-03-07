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

#ifndef GRM_H_INCLUDED
#define GRM_H_INCLUDED

#include "GameFont.h"
#include "GameTexture.h"

namespace is
{
////////////////////////////////////////////////////////////
/// Class for manage SFML Font and Texture without using an
/// SFML object
////////////////////////////////////////////////////////////
class GRM
{
public:
    /// Game Font container
    std::vector<std::shared_ptr<GameFont>> m_GRMfont;

    /// Game Texture container
    std::vector<std::shared_ptr<GameTexture>> m_GRMtexture;

    //////////////////////////////////////////////////////
    /// \brief Allows to add SFML Font in GRM container
    ///
    /// \param name of font which will be used to identify
    /// it in the container in order to be able to access it
    /// \param filePath path of the font file to add
    //////////////////////////////////////////////////////
    virtual sf::Font& GRMaddFont(const std::string& name, const std::string& filePath, float fontSize
                                   #if !defined(IS_ENGINE_HTML_5)
                                   = is::GameConfig::DEFAULT_SFML_TEXT_SIZE
                                   #endif
                                   )
    {
        auto obj = std::make_shared<GameFont>(name, filePath, fontSize);
        m_GRMfont.push_back(obj);
        return obj->getFont();
    }

    //////////////////////////////////////////////////////
    /// \brief Allows to add SFML Texture in GRM container
    ///
    /// \param name of texture which will be used to identify
    /// it in the container in order to be able to access it
    /// \param filePath path of the texture file to add
    //////////////////////////////////////////////////////
    virtual sf::Texture& GRMaddTexture(const std::string& name, const std::string& filePath)
    {
        auto obj = std::make_shared<GameTexture>(name, filePath);
        m_GRMtexture.push_back(obj);
        return obj->getTexture();
    }

    /// Allows to get font as a reference in container by his name
    virtual sf::Font& GRMgetFont(const std::string& name)       {return *GRMgetFontPtr(name);}

    /// Allows to get texture as a reference in container by his name
    virtual sf::Texture& GRMgetTexture(const std::string& name) {return *GRMgetTexturePtr(name);}

    /// Allows to get font as a pointer in container by his name
    virtual sf::Font* GRMgetFontPtr(const std::string& name)
    {
        WITH (m_GRMfont.size())
        {
            if (m_GRMfont[_I]->getName() == name)
            {
                return &m_GRMfont[_I]->getFont();
            }
        }
        is::showLog("ERROR: <" + name + "> font does not exist!");
        return nullptr;
    }

    /// Allows to get texture as a pointer in container by his name
    virtual sf::Texture* GRMgetTexturePtr(const std::string& name)
    {
        WITH (m_GRMtexture.size())
        {
            if (m_GRMtexture[_I]->getName() == name)
            {
                return &m_GRMtexture[_I]->getTexture();
            }
        }
        is::showLog("ERROR: <" + name + "> texture does not exist!");
        return nullptr;
    }
};
}
#endif // GRM_H_INCLUDED
