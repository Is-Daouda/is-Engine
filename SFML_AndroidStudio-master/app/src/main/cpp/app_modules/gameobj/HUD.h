#ifndef HUD_H_INCLUDED
#define HUD_H_INCLUDED

#include "../system/function/GameTime.h"
#include "../system/function/GameFunction.h"
#include "../system/entity/MainObject.h"
#include "../core/GameSystemExtended.h"

class HUD : public is::MainObject
{
public:
    HUD();
    void loadResources(sf::Font const &fnt);
    void step(GameTime const &gameTime, int maxBonus, GameSystemExtended const &gameSysExt);
    void draw(sf::RenderWindow &app);

private:
    sf::Text m_txtBonus, m_txtLives, m_txtLevelTime;
};

#endif // HUD_H_INCLUDED
