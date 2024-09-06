/*
  is::Engine (Infinity Solutions Engine)
  Copyright (C) 2018-2024 Is Daouda <isdaouda.n@gmail.com>

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
    virtual sf::Font& GRMaddFont(const std::string& name, const std::string& filePath)
    {
        auto obj = fontFileExists(filePath);
        if (obj == nullptr)
        {
            auto newObj = std::make_shared<GameFont>(name, filePath);
            m_GRMfont.push_back(newObj);
            return newObj->getFont();
        }
        else is::showLog("WARNING: <" + name + "> font has already been added!");
        return obj->getFont();
    }

    //////////////////////////////////////////////////////
    /// \brief Allows to add existing font in GRM container
    ///
    /// \param font object
    //////////////////////////////////////////////////////
    void GRMaddFontObject(std::shared_ptr<GameFont> font, bool showError = true)
    {
        if (!fontFileExists(font->getFilePath())) m_GRMfont.push_back(font);
        else
        {
            if (showError) is::showLog("WARNING: <" + font->getName() + "> font has already been added!");
        }
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
        auto obj = textureFileExists(filePath);
        if (obj == nullptr)
        {
            auto newObj = std::make_shared<GameTexture>(name, filePath);
            m_GRMtexture.push_back(newObj);
            return newObj->getTexture();
        }
        else is::showLog("WARNING: <" + name + "> texture has already been added!");
        return obj->getTexture();
    }

    //////////////////////////////////////////////////////
    /// \brief Allows to add existing texture in GRM container
    ///
    /// \param texture object
    //////////////////////////////////////////////////////
    void GRMaddTextureObject(std::shared_ptr<GameTexture> texture, bool showError = true)
    {
        if (textureFileExists(texture->getFilePath()) == nullptr) m_GRMtexture.push_back(texture);
        else
        {
            if (showError) is::showLog("WARNING: <" + texture->getName() + "> texture has already been added!");
        }
    }

    /// Allows to get font as a reference in container by his name
    virtual sf::Font& GRMgetFont(const std::string& name)       {return *GRMgetFontPtr(name);}

    /// Allows to get texture as a reference in container by his name
    virtual sf::Texture& GRMgetTexture(const std::string& name) {return *GRMgetTexturePtr(name);}

    /// Allows to get font as a pointer in container by his name
    virtual sf::Font* GRMgetFontPtr(const std::string& name)
    {
        WITH(m_GRMfont.size())
        {
            if (m_GRMfont[_I].get() != nullptr)
            {
                if (m_GRMfont[_I]->getName() == name && m_GRMfont[_I]->getFileIsLoaded())
                {
                    return &m_GRMfont[_I]->getFont();
                }
            }
        }
        is::showLog("ERROR: <" + name + "> font does not exist!");
        return nullptr;
    }

    /// Allows to get texture as a pointer in container by his name
    virtual sf::Texture* GRMgetTexturePtr(const std::string& name)
    {
        WITH(m_GRMtexture.size())
        {
            if (m_GRMtexture[_I].get() != nullptr)
            {
                if (m_GRMtexture[_I]->getName() == name && m_GRMtexture[_I]->getFileIsLoaded())
                {
                    return &m_GRMtexture[_I]->getTexture();
                }
            }
        }
        is::showLog("ERROR: <" + name + "> texture does not exist!");
        return nullptr;
    }

    /// Allows to delete font in container by his name
    void GRMdeleteFont(const std::string& name)
    {
        int fontId(-1);
        WITH(m_GRMfont.size())
        {
            if (m_GRMfont[_I].get() != nullptr)
            {
                if (m_GRMfont[_I]->getName() == name)
                {
                    fontId = _I;
                    break;
                }
            }
        }
        if (fontId == -1) is::showLog("ERROR: Can't delete <" + name + "> font because font does not exist!");
        else
        {
            m_GRMfont[fontId].reset();
            m_GRMfont[fontId] = nullptr;
        }
    }

    /// Allows to delete texture in container by his name
    void GRMdeleteTexture(const std::string& name)
    {
        int textureId(-1);
        WITH(m_GRMtexture.size())
        {
            if (m_GRMtexture[_I].get() != nullptr)
            {
                if (m_GRMtexture[_I]->getName() == name)
                {
                    textureId = _I;
                    break;
                }
            }
        }
        if (textureId == -1) is::showLog("ERROR: Can't delete <" + name + "> texture because texture does not exist!");
        else
        {
            m_GRMtexture[textureId].reset();
            m_GRMtexture[textureId] = nullptr;
        }
    }

private:
    GameTexture* textureFileExists(const std::string& filePath) const
    {
        WITH(m_GRMtexture.size())
        {
            if (m_GRMtexture[_I].get() != nullptr)
            {
                if (m_GRMtexture[_I]->getFilePath() == filePath) return m_GRMtexture[_I].get();
            }
        }
        return nullptr;
    }

    GameFont* fontFileExists(const std::string& filePath) const
    {
        WITH(m_GRMfont.size())
        {
            if (m_GRMfont[_I].get() != nullptr)
            {
                if (m_GRMfont[_I]->getFilePath() == filePath) return m_GRMfont[_I].get();
            }
        }
        return nullptr;
    }
};
}
#endif // GRM_H_INCLUDED
