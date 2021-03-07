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

#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "../display/GameDisplay.h"

namespace is
{
////////////////////////////////////////////////////////////
/// Class which allows to use a Button in a scene. It
/// supports hover and click events.
////////////////////////////////////////////////////////////
class Button : public MainObject
{
public:
    Button(sf::Texture &tex, float x, float y, std::string const &title, std::string const &name, bool center, GameDisplay *scene):
        MainObject(x ,y),
        m_scene(scene),
        m_isInCollision(false)
    {
        m_strName = std::string((name == "" || name == " ") ? "Button_" + is::numToStr(MainObject::instanceNumber) : name); // object name
        m_w = tex.getSize().x / 2;
        m_h = tex.getSize().y;
        if (!center)
        {
            m_xOffset = m_w / 2.f;
            m_yOffset = m_h / 2.f;
        }
        is::createSprite(tex, m_sprParent, sf::IntRect(0, 0, m_w, m_h),
                         sf::Vector2f(m_x, m_y), sf::Vector2f(m_w / 2.f, m_h / 2.f));
        is::createText(scene->getFontSystem(), m_txtTitle, title, m_x, m_y, is::GameConfig::DEFAULT_BUTTON_TEXT_COLOR, true, m_h / 2);
        m_SDMcallEvent = true;
    }

    Button(sf::Texture &tex, sf::Font &font, float x, float y, std::string const &title, std::string const &name, bool center, int textSize, GameDisplay *scene):
        MainObject(x ,y),
        m_scene(scene),
        m_isInCollision(false)
    {
        m_strName = std::string((name == "" || name == " ") ? "Button_" + is::numToStr(MainObject::instanceNumber) : name); // object name
        m_w = tex.getSize().x / 2;
        m_h = tex.getSize().y;
        if (!center)
        {
            m_xOffset = m_w / 2.f;
            m_yOffset = m_h / 2.f;
        }
        is::createSprite(tex, m_sprParent, sf::IntRect(0, 0, m_w, m_h),
                         sf::Vector2f(m_x, m_y), sf::Vector2f(m_w / 2.f, m_h / 2.f));
        is::createText(font, m_txtTitle, title, m_x, m_y, is::GameConfig::DEFAULT_BUTTON_TEXT_COLOR, true, textSize);
        m_SDMcallEvent = true;
    }

    /// Set the button text title
    virtual void setTitle(std::string const &title)
    {
        m_txtTitle.setString(title);
        is::centerSFMLObj(m_txtTitle);
    }

    /// Triggers when the button is clicked
    /// This method must be overloaded
    virtual void onClick() = 0;

    /// Triggers when the user hovers over the button
    /// This method must be overloaded
    virtual void onMouseOver()
    {
        // is::showLog("WARNING: Button::onMouseOver() method must be overloaded!");
    }

    virtual void mouseAction(
                             #if !defined(IS_ENGINE_HTML_5)
                             sf::Event &event
                             #endif // defined
                             )
    {
        if (m_isInCollision)
        {
            auto functionClick = [this]()
            {
                onClick();
                m_imageScale =
                               #if !defined(__ANDROID__)
                               1.2f;
                               #else
                               1.f;
                               #endif
            };
            if (
                #if !defined(IS_ENGINE_HTML_5)
                event.type == sf::Event::MouseButtonPressed
                #else
                m_scene->getRenderWindow().input().IsCursorReleased()
                #endif
                )
            {
                #if !defined(IS_ENGINE_HTML_5)
                if (event.key.code == is::GameConfig::KEY_VALIDATION_MOUSE)
                {
                #endif
                    functionClick();
                #if !defined(IS_ENGINE_HTML_5)
                }
                #endif
            }
            #if defined(__ANDROID__)
            if (event.type == sf::Event::TouchEnded)
            {
                if (event.touch.finger == 0)
                {
                    functionClick();
                }
            }
            #endif
        }
    }

#if !defined(IS_ENGINE_HTML_5)
    virtual void event(sf::Event &event)
    {
        mouseAction(event);
    }
#endif

    virtual void step(float const &DELTA_TIME)
    {
        bool tempCollision(m_scene->mouseCollision(m_sprParent));
        if (tempCollision && !m_isInCollision)
        {
            onMouseOver();
            m_imageScale =
                            #if !defined(__ANDROID__)
                            1.1f;
                            #else
                            0.92f;
                            #endif // defined
            m_isInCollision = true;
        }
        #if defined(IS_ENGINE_HTML_5)
        mouseAction();
        #endif // defined
        is::setSFMLObjTexRec(m_sprParent, ((m_isInCollision) ? 1 : 0) * m_w, 0, m_w, m_h);
        if (!tempCollision)
        {
            m_isInCollision = false;
        #if defined(__ANDROID__)
            m_imageScale = 1.f;
        }
        #else
        }
        is::scaleAnimation(DELTA_TIME, m_imageScale, m_sprParent);
        #endif // defined
        updateSprite(m_x, m_y, m_imageAngle, m_imageAlpha, m_imageScale, m_imageScale, m_xOffset, m_yOffset);
        is::setSFMLObjProperties(m_txtTitle, is::getSFMLObjX(m_sprParent), is::getSFMLObjY(m_sprParent) - is::getSFMLObjHeight(m_txtTitle) / 4.f,
                                 m_imageAngle, m_imageAlpha, m_imageScale, m_imageScale);
    }

    virtual void draw(is::Render &surface)
    {
        surface.draw(m_sprParent);
        surface.draw(m_txtTitle);
    }

    /// Return the SFML text object
    virtual sf::Text &getText()
    {
        return m_txtTitle;
    }

    /// Check if mouse or finger (on Android) is in collision with the Button
    virtual bool getIsInCollision() const
    {
        return m_isInCollision;
    }

protected:
    GameDisplay *m_scene;
    sf::Text m_txtTitle;
    bool m_isInCollision;
};
}

#endif // BUTTON_H_INCLUDED
