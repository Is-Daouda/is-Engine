#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include "../display/GameDisplay.h"

namespace is
{
////////////////////////////////////////////////////////////
/// Class for drawing a background that fills a scene and
/// that we can scroll vertically and horizontally with a speed
////////////////////////////////////////////////////////////
class Background : public MainObject
{
public:
    Background(sf::Texture &tex, float x, float y, GameDisplay *scene, float hSpeed = 0.f, float vSpeed = 0.f,
               bool fillHorizontal = true, bool fillVertical = true):
        MainObject(x ,y),
        m_scene(scene)
    {
        m_strName = "Background"; // object name

        m_hsp = hSpeed;
        m_vsp = vSpeed;
        int bgW = (fillHorizontal) ? scene->getSceneWidth()  + tex.getSize().x : tex.getSize().x;
        int bgH = (fillVertical)   ? scene->getSceneHeight() + tex.getSize().y : tex.getSize().y;
        is::createSprite(tex, m_sprParent, sf::IntRect(0, 0, bgW, bgH), sf::Vector2f(m_x, m_y), sf::Vector2f(0.f, 0.f), true);
        if (m_hsp > 0.f)
        {
            m_x -= tex.getSize().x;
            m_xStart = m_x;
        }
        if (m_vsp > 0.f)
        {
            m_y -= tex.getSize().x;
            m_yStart = m_y;
        }
    }

    void step(float const &DELTA_TIME)
    {
        m_x += m_hsp;
        m_y += m_vsp;
        if (m_hsp > 0.f)
        {
            if (m_x > m_xStart + m_sprParent.getTexture()->getSize().x) m_x = m_xStart;
        }
        if (m_hsp < 0.f)
        {
            if (m_x < m_xStart - m_sprParent.getTexture()->getSize().x) m_x = m_xStart;
        }
        if (m_vsp > 0.f)
        {
            if (m_y > m_yStart + m_sprParent.getTexture()->getSize().y) m_y = m_yStart;
        }
        if (m_vsp < 0.f)
        {
            if (m_y < m_yStart - m_sprParent.getTexture()->getSize().y) m_y = m_yStart;
        }
        updateSprite();
    }

private:
    GameDisplay *m_scene;
};
}

#endif // BACKGROUND_H_INCLUDED
