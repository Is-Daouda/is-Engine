#include "Enemy.h"

Enemy::Enemy(sf::Texture &tex, EnemyType type, float x, float y, int scorePoint):
    MainObject(x, y),
    Destructible(),
    ScorePoint(scorePoint),
    m_type(type),
    m_destructible(true),
    m_playSndTime(0)
{
    m_w = 32;
    m_h = 32;
    is::createSprite(tex, m_sprParent, sf::IntRect(0, 0, 32, 32), sf::Vector2f(m_x, m_y), sf::Vector2f(16.f, 16.f));
}

Enemy::~Enemy()
{
}

void Enemy::step(float const &DELTA_TIME)
{
    switch (m_type)
    {
        case Enemy::EnemyType::ENEMY_SPIKE_BALL:
            m_destructible = false;
            m_frame = 0.f;
        break;

        case Enemy::EnemyType::ENEMY_BALL:
            m_frameStart = 1.f;
            m_frameEnd = 2.f;
        break;

        default :
        break;
    }

    // animation
    if (m_animationTime < 32.5f) m_animationTime += (0.25f * is::VALUE_CONVERSION) * DELTA_TIME;
    else m_animationTime = 0.f;

    if (m_animationTime > 30.f)  m_frame = m_frameEnd;
    else m_frame = m_frameStart;

    // update sprite
    is::setFrame(m_sprParent, m_frame, 8);
    is::setSFMLObjScaleX_Y(m_sprParent, m_imageXscale, m_imageYscale);

    centerCollisionMask(3, 3);
}

bool Enemy::getIsDestructible() const
{
    return m_destructible;
}

Enemy::EnemyType Enemy::getType() const
{
    return m_type;
}

void Enemy::draw(sf::RenderTexture &surface)
{
    surface.draw(m_sprParent);
}
