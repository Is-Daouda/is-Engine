#include "GameSlider.h"

namespace is
{
GameSlider::GameSlider(is::GameDisplay *scene):
    MainObject(),
    Type(SLIDE_NONE),
    m_scene(scene),
    m_slideDistance(64.f)
{}

void GameSlider::step(float const &DELTA_TIME)
{
    if (m_scene->getGameSystem().isPressed(is::GameSystem::MOUSE))
    {
        sf::Vector2f cursor(m_scene->getCursor());
        if (static_cast<int>(m_time) == 0)
        {
            m_xStart = cursor.x;
            m_yStart = cursor.y;
        }
        m_time = 5.f;
        m_x = cursor.x;
        m_y = cursor.y;
        if (m_type == SLIDE_NONE)
        {
            if (m_x > m_xStart + m_slideDistance) m_type = SLIDE_RIGHT;
            else if (m_x < m_xStart - m_slideDistance) m_type = SLIDE_LEFT;
            else if (m_y < m_yStart - m_slideDistance) m_type = SLIDE_UP;
            else if (m_y > m_yStart + m_slideDistance) m_type = SLIDE_DOWN;
        }
    }
    if (m_time > 0.f) m_time -= is::getMSecond(DELTA_TIME);
    else
    {
        m_type = SLIDE_NONE;
        m_time = 0.f;
    }
}

GameSlider::SlideDirection GameSlider::getSlideDirection() const
{
    switch (m_type)
    {
        default: break;
        case 1: return SLIDE_UP; break;
        case 2: return SLIDE_DOWN; break;
        case 3: return SLIDE_RIGHT; break;
        case 4: return SLIDE_LEFT; break;
    }
    return SLIDE_NONE;
}
}
