#include "HUD.h"

HUD::HUD() :
    is::MainObject()
{

}

void HUD::loadResources(sf::Font const &fnt)
{
    is::createText(fnt, m_txtBonus, " ", m_x, m_y, sf::Color::Yellow, 20);
    is::createText(fnt, m_txtLevelTime, " ", m_x, m_y, sf::Color::Yellow, 20);
    is::createText(fnt, m_txtLives, " ", m_x, m_y, sf::Color::Yellow, 20);
}

void HUD::step(GameTime const &gameTime, int maxBonus, GameSystemExtended const &gameSysExt)
{
    // position bonus text
    m_txtBonus.setString("Bonus : " + is::writeZero(gameSysExt.m_currentBonus) + "/" + is::writeZero(maxBonus));
    is::setSFMLObjX_Y(m_txtBonus, m_x, m_y);

    // position level time
    m_txtLevelTime.setString("Level Time : " + gameTime.getTimeString());

    if (gameTime.getMinute() == 0 && gameTime.getSecond() <= 30)
    {
        if (gameTime.getSecond() % 2)
        {
            is::setSFMLTextColor(m_txtLevelTime, sf::Color(255, 0, 0, 255));
            is::setSFMLTextOutlineColor(m_txtLevelTime, sf::Color(150, 0, 0, 255));
        }
        else
        {
            is::setSFMLTextColor(m_txtLevelTime , sf::Color(255, 255, 0, 255));
            is::setSFMLTextOutlineColor(m_txtLevelTime, sf::Color(175, 175, 0, 255));
        }
    }
    else
    {
        is::setSFMLTextColor(m_txtLevelTime, sf::Color(255, 255, 0, 255));
        is::setSFMLTextOutlineColor(m_txtLevelTime, sf::Color(175, 175, 0, 255));
    }

    is::setSFMLObjX_Y(m_txtLevelTime, m_x, m_y + 32.f);

    // position lives
    m_txtLives.setString("Lives : " + is::writeZero(gameSysExt.m_currentLives));
    is::setSFMLObjX_Y(m_txtLives, m_x, m_y + 64.f);
}

void HUD::draw(sf::RenderWindow &app)
{
    app.draw(m_txtBonus);
    app.draw(m_txtLives);
    app.draw(m_txtLevelTime);
}
