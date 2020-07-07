#include "FinishObject.h"

FinishObject::FinishObject(is::GameDisplay *scene):
    MainObject(),
    Step(0),
    m_scene(scene)
{
    m_w = 32;
    m_h = 32;
}

void FinishObject::loadResources(sf::Texture &tex)
{
    is::createSprite(tex, m_sprParent, sf::IntRect(0, 0, 32, 32), sf::Vector2f(m_x, m_y), sf::Vector2f(0.f, 0.f));
    updateCollisionMask();
}

void FinishObject::step(float const &DELTA_TIME)
{
    if (m_step == 0)
    {
        // If the player touches the object then he has gained the level
        if (auto player = static_cast<Player*>(m_scene->SDMgetObject("Player")); placeMetting(0, 0, player))
        {
            m_scene->GSMplaySound("finish"); // We play this sound
            static_cast<is::GameKeyData*>(m_scene->SDMgetObject("GameKeyData"))->m_disableAllKey = true; // deactivate commands
            addStep(); // We go to the next step in order to go to the next level
        }
    }
}

void FinishObject::draw(sf::RenderTexture &surface)
{
    // We draw the object only if it is in the field of vision of the scene view
    if (m_scene->inViewRec(this)) surface.draw(m_sprParent);
}
