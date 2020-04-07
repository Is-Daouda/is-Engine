#ifndef BONUS_H_INCLUDED
#define BONUS_H_INCLUDED

#include "../../../isEngine/system/entity/Destructible.h"
#include "../../../isEngine/system/entity/MainObject.h"
#include "../../gamesystem_ext/GameSystemExtended.h"
#include "../parents/ScorePoint.h"
#include "../parents/Step.h"

class Bonus : public is::MainObject, public is::Destructible, public ScorePoint, public Step
{
public:

    /// types of bonus
    enum BonusType
    {
        BONUS_NORMAL,
        BONUS_HEALTH,
        BONUS_1_UP
    };

    Bonus(sf::Texture &tex, BonusType type, float x, float y);
    ~Bonus();

    void step(float const &DELTA_TIME);
    void setTouchPlayer(bool val);
    void draw(sf::RenderTexture &surface);

    bool getTouchPlayer() const;
    BonusType getType() const;

private:
    BonusType m_type;
    float m_oscillation;
    int m_regenerationTime;
    bool m_touchPlayer;
};

#endif // BONUS_H_INCLUDED
