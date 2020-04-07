#include "HUD.h"

HUD::HUD(is::GameDisplay &scene) :
    m_score(0),
    m_scene(scene)
{
    m_imageAlpha = 0;
}

void HUD::loadResources(sf::Font const &fnt)
{
    int const TXT_SIZE(20);
    is::createText(fnt, m_txtScore,     " ", 0.f, 0.f, sf::Color(255, 255, 255, 255), sf::Color(0, 0, 0, 255), TXT_SIZE);
    is::createText(fnt, m_txtLevelTime, " ", 0.f, 0.f, sf::Color(255, 255, 255, 255), sf::Color(0, 0, 0, 255), TXT_SIZE);
    is::createText(fnt, m_txtHealth,    " ", 0.f, 0.f, sf::Color(255, 0, 0, 255), sf::Color(0, 0, 0, 255), TXT_SIZE);
    is::createText(fnt, m_txtBonus,     " ", 0.f, 0.f, sf::Color(255, 255, 255, 255), sf::Color(0, 0, 0, 255), TXT_SIZE);
    is::createText(fnt, m_txtLives,     " ", 0.f, 0.f, sf::Color(255, 255, 255, 255), sf::Color(0, 0, 0, 255), TXT_SIZE);
}

void HUD::step(float const &DELTA_TIME, is::GameTime &gameTime, Player &player, bool &levelComplete)
{

    if (m_score < m_scene.getGameSystem().m_currentScore)
    {
        m_timeScoreCount += ((is::VALUE_CONVERSION * 0.6f) * DELTA_TIME);
        if (m_timeScoreCount > 1.f)
        {
            m_score += 2;
            m_timeScoreCount = 0.f;
        }
    }
    float const TXT_X_POS(-300.f), TXT_Y_POS(16.f);

    m_txtScore.setString("Score : " + is::writeZero(m_score, 4));
    is::setSFMLObjX_Y(m_txtScore, m_scene.getViewX() + TXT_X_POS, (m_scene.getViewY() - m_scene.getViewH() / 2.f) + TXT_Y_POS);

    m_txtLevelTime.setString("Time : " + gameTime.getTimeString());
    is::setSFMLObjX_Y(m_txtLevelTime, m_scene.getViewX() + TXT_X_POS, (m_scene.getViewY() - m_scene.getViewH() / 2.f) + (TXT_Y_POS + 30.f));

    m_txtHealth.setString("Health : " + is::writeZero(player.getHealth()));
    is::setSFMLObjX_Y(m_txtHealth, m_scene.getViewX() + TXT_X_POS, (m_scene.getViewY() - m_scene.getViewH() / 2.f) + (TXT_Y_POS + 60.f));

    m_txtBonus.setString("Bonus : " + is::writeZero(m_scene.getGameSystem().m_currentBonus));
    is::setSFMLObjX_Y(m_txtBonus, m_scene.getViewX() + TXT_X_POS, (m_scene.getViewY() - m_scene.getViewH() / 2.f) + (TXT_Y_POS + 90.f));

    m_txtLives.setString("Lives : " + is::writeZero(m_scene.getGameSystem().m_currentLives));
    is::setSFMLObjX_Y(m_txtLives, m_scene.getViewX() + TXT_X_POS, (m_scene.getViewY() - m_scene.getViewH() / 2.f) + (TXT_Y_POS + 120.f));
}

void HUD::draw(sf::RenderTexture &surface)
{
    surface.draw(m_sprParent);
    surface.draw(m_txtScore);
    surface.draw(m_txtLevelTime);
    surface.draw(m_txtHealth);
    surface.draw(m_txtBonus);
    surface.draw(m_txtLives);
}

void HUD::setScore(int val)
{
    m_score = val;
}
