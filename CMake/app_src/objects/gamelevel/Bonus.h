#ifndef BONUS_H_INCLUDED
#define BONUS_H_INCLUDED

#include "../../../isEngine/system/entity/parents/ScorePoint.h"
#include "../../../isEngine/system/entity/parents/Step.h"
#include "../../../isEngine/system/display/GameDisplay.h"
#include "Player.h"

class Bonus : public is::MainObject, public is::ScorePoint, public is::Step
{
public:
    /// types of bonus
    enum BonusType
    {
        BONUS_NORMAL,
        BONUS_HEALTH,
        BONUS_1_UP
    };

    Bonus(sf::Texture &tex, BonusType type, float x, float y, is::GameDisplay *scene);
    ~Bonus();

    void step(float const &DELTA_TIME);
    void draw(sf::RenderTexture &surface);
    BonusType getType() const;

private:
    is::GameDisplay *m_scene;
    BonusType m_type;
    float m_oscillation;
    bool m_touchPlayer;
};

#endif // BONUS_H_INCLUDED
