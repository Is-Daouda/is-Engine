#ifndef BONUS_H_INCLUDED
#define BONUS_H_INCLUDED

#include "../core/GameSystemExtended.h"
#include "../system/entity/Destructible.h"
#include "../system/entity/MainObject.h"

class Bonus : public is::MainObject, public is::Destructible
{
public:
    Bonus(sf::Texture &m_tex, float x, float y);
    ~Bonus();

    void step(float const &DELTA_TIME);
    void setTouchPlayer(bool val);
    void draw(sf::RenderWindow &app);

    bool getTouchPlayer() const;

private:
    float m_oscillation, m_scale;
    int m_alpha;
    bool m_touchPlayer;
};

#endif // BONUS_H_INCLUDED
