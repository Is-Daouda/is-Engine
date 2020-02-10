#ifndef GAMEINTRO_H_INCLUDED
#define GAMEINTRO_H_INCLUDED

#include "../system/display/GameDisplay.h"

class GameIntro : public is::GameDisplay
{
public:
    GameIntro(sf::RenderWindow &window, DisplayOption &m_launchOption, GameSystemExtended &gameSysExt);

    void step();
    void draw();

    bool loadResources();

private:
    sf::Text m_txtTitle;
    int m_timeEv, m_introStep, m_imgAlpha;
    bool m_blind;
};

#endif // GAMEINTRO_H_INCLUDED
