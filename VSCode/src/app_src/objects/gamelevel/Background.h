#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include "../../../isEngine/system/display/GameDisplay.h"

class Background : public is::MainObject
{
public:
    Background(is::GameDisplay *scene, sf::Texture &tex):
        is::MainObject(),
        m_scene(scene)
    {
        // Create the background so that it fills the whole level
        is::createSprite(tex, m_sprParent, sf::IntRect(0, 0, (scene->getSceneWidth() * 32), 640), sf::Vector2f(scene->getViewX() * 0.25f - 80.f, scene->getViewY() - 240.f),
             sf::Vector2f(0.f, 0.f), true);
    }

    void step(float const &DELTA_TIME)
    {
        // Apply a 3D effect on the background movement
        is::setSFMLObjX_Y(m_sprParent, m_scene->getViewX() * 0.98f - 390.f, m_scene->getViewY() - 240.f);
    }

private:
    is::GameDisplay *m_scene;
};

#endif // BACKGROUND_H_INCLUDED
