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
    Button(sf::Texture &tex, float x, float y, std::string const &title, GameDisplay *scene):
        MainObject(x ,y),
        m_scene(scene),
        m_isInCollision(false)
    {
        m_strName = "Button " + MainObject::instanceNumber; // object name
        m_w = tex.getSize().x / 2;
        m_h = tex.getSize().y;
        is::createSprite(tex, m_sprParent, sf::IntRect(0, 0, m_w, m_h),
                         sf::Vector2f(m_x, m_y), sf::Vector2f(m_w / 2.f, m_h / 2.f));
        is::createText(scene->getFontSystem(), m_txtTitle, title, m_x, m_y, sf::Color::Blue, true, m_h / 2);
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
        is::showLog("WARNING: onMouseOver() method must be overloaded!");
    }

    virtual void event(sf::Event &event)
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
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.key.code == sf::Mouse::Left)
                {
                    functionClick();
                }
            }
            if (event.type == sf::Event::TouchEnded)
            {
                if (event.touch.finger == 0)
                {
                    functionClick();
                }
            }
        }
    }

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
        updateSprite(m_x, m_y, m_imageAngle, m_imageAlpha, m_imageScale, m_imageScale, m_w / 2.f, m_h / 2.f);
        is::setSFMLObjProperties(m_txtTitle, is::getSFMLObjX(m_sprParent), is::getSFMLObjY(m_sprParent) - is::getSFMLObjHeight(m_txtTitle) / 2.f,
                                 m_imageAngle, m_imageAlpha, m_imageScale, m_imageScale);
    }

    virtual void draw(sf::RenderTexture &surface)
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
