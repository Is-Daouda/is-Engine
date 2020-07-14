#include "Bonus.h"

Bonus::Bonus(sf::Texture &tex, BonusType type, float x, float y, is::GameDisplay *scene):
    MainObject(x, y),
    ScorePoint(10),
    Step(0),
    m_scene(scene),
    m_type(type),
    m_oscillation(0.f),
    m_touchPlayer(false)
{
    is::createSprite(tex, m_sprParent, sf::IntRect(32 * m_type, 0, 32, 32), sf::Vector2f(m_x, m_y), sf::Vector2f(16.f, 16.f));
    switch(m_type)
    {
        case BONUS_NORMAL: m_y += 8.f;
        break;
        default: break;
    }
}

Bonus::~Bonus()
{
}

void Bonus::step(float const &DELTA_TIME)
{
    // We call the player object which is in the SDM container
    if (auto player = static_cast<Player*>(m_scene->SDMgetObject("Player")); player->getIsActive())
    {
        // If the player is at a certain distance from the Bonus then he can get it
        if (is::pointDistance(player->getSpriteX(), player->getSpriteY(), m_x + 16.f, m_y + 16.f) < 34.f && !m_touchPlayer)
        {
            // The action changes according to the Bonus
            switch (m_type)
            {
                case Bonus::BonusType::BONUS_NORMAL:
                    m_scene->getGameSystem().m_currentBonus++;
                    m_scene->getGameSystem().m_currentScore += getScorePoint();

                    // add life if bonus > 99
                    if (m_scene->getGameSystem().m_currentBonus > 99)
                    {
                        m_scene->GSMplaySound("have_life"); // We play this sound
                        m_scene->getGameSystem().useVibrate(60);
                        m_scene->getGameSystem().m_currentLives++;
                        m_scene->getGameSystem().m_currentBonus = 0;
                    }
                    m_scene->GSMplaySound("have_bonus"); // We play this sound
                break;

                case Bonus::BonusType::BONUS_HEALTH:
                    if (player->getHealth() < 4) player->addHealth();
                    else m_scene->getGameSystem().m_currentScore += getScorePoint() * 5;
                    m_scene->GSMplaySound("have_health"); // We play this sound
                break;

                case Bonus::BonusType::BONUS_1_UP:
                    m_scene->getGameSystem().m_currentLives++;
                    m_scene->GSMplaySound("have_life"); // We play this sound
                break;
            }
            m_touchPlayer = true;
        }
    }

    // Allows for an oscillation effect
    m_oscillation += is::radToDeg((0.05f * is::VALUE_CONVERSION) * DELTA_TIME);

    switch(m_type)
    {
        case BONUS_HEALTH:
        case BONUS_1_UP:
            if (m_touchPlayer) m_sprParent.rotate((-10.f * is::VALUE_CONVERSION) * DELTA_TIME);
        break;

        default :
        break;
    }

    // We make a disappearance effect thanks to alpha transparency. If its value reaches 0 we destroy the Bonus
    if (m_touchPlayer)
    {
        if (m_imageAlpha > 12)
        {
            m_imageAlpha -= static_cast<int>((10.f * is::VALUE_CONVERSION) * DELTA_TIME);
            m_imageScale += (0.08f * is::VALUE_CONVERSION) * DELTA_TIME;
        }
        else m_destroy = true; // We destroy the object
    }
    is::setSFMLObjX_Y(m_sprParent, m_x + 16.f, m_y + 8.f + is::lengthDirY(3.5f, m_oscillation));
    is::setSFMLObjScaleX_Y(m_sprParent, m_imageScale, m_imageScale);
    is::setSFMLObjAlpha(m_sprParent, m_imageAlpha);
}

Bonus::BonusType Bonus::getType() const
{
    return m_type;
}

void Bonus::draw(sf::RenderTexture &surface)
{
    // We draw the object only if it is in the field of vision of the scene view
    if (m_scene->inViewRec(this))
    {
        surface.draw(m_sprParent);
    }
}
