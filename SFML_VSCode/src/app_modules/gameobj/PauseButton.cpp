#include "PauseButton.h"

PauseButton::PauseButton() :
    MainObject(),
    alpha(255)
{
}

void PauseButton::loadResources(sf::Texture &m_tex)
{
    is::createSprite(m_tex, m_sprParent, sf::Vector2f(m_x, m_y), sf::Vector2f(16.f, 16.f));
}

void PauseButton::step(float const &DELTA_TIME)
{
    is::setSFMLObjX_Y(m_sprParent, m_x, m_y);
    if (alpha > 95) alpha -= static_cast<int>((4.f * is::VALUE_CONVERSION) * DELTA_TIME);
    else alpha = 90;
    m_sprParent.setColor(sf::Color(255, 255, 255, alpha));
}

void PauseButton::setAlpha(int val)
{
    alpha = val;
}

bool PauseButton::isOn() const
{
    return (alpha > 250);
}

void PauseButton::draw(sf::RenderWindow &app)
{
    app.draw(m_sprParent);
}
