#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "../../../isEngine/system/entity/MainObject.h"
#include "../../../isEngine/system/entity/parents/ScorePoint.h"
#include "Player.h"
#include "ElectroShock.h"

class Enemy : public is::MainObject, public is::ScorePoint
{
public:
    enum EnemyType
    {
        ENEMY_SPIKE_BALL,
        ENEMY_BALL
    };

    Enemy(sf::Texture &tex, EnemyType type, float x, float y, is::GameDisplay *scene, int scorePoint = 0);
    ~Enemy();

    void step(float const &DELTA_TIME);
    void draw(sf::RenderTexture &surface);

    EnemyType getType() const;

private:
    is::GameDisplay *m_scene;
    EnemyType m_type;
    float m_animationTime;
    bool m_destructible; ///< Lets know if we can destroy this enemy
};

#endif // ENEMY_H_INCLUDED
