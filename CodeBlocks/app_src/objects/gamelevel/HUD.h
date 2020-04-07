#ifndef HUD_H_INCLUDED
#define HUD_H_INCLUDED

#include "../../../isEngine/system/entity/MainObject.h"
#include "../../../isEngine/system/function/GameTime.h"
#include "../../gamesystem_ext/GameSystemExtended.h"
#include "Player.h"

class HUD : public is::MainObject
{
public:
    HUD(is::GameDisplay &scene);

    void loadResources(sf::Font const &fnt);
    void step(float const &DELTA_TIME, is::GameTime &gameTime, Player &player, bool &levelComplete);
    void draw(sf::RenderTexture &surface);
    void setScore(int val);

private:
    float m_timeScoreCount;
    int m_score;
    is::GameDisplay &m_scene;

    sf::Text m_txtHealth, m_txtBonus, m_txtLives, m_txtLevelTime, m_txtScore;
};

#endif // HUD_H_INCLUDED
