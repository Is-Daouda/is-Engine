#ifndef GAMEENDSCREEN_H_INCLUDED
#define GAMEENDSCREEN_H_INCLUDED

#include "../system/display/GameDisplay.h"

class GameEndScreen : public is::GameDisplay
{
public:
    GameEndScreen(sf::RenderWindow &window, DisplayOption &m_launchOption, GameSystemExtended& GameSystemExtended);
    ~GameEndScreen();

    void step();
    void draw();

    bool loadResources();

private:
    float m_sprButtonSelectScale;
    bool m_isStarted, m_isClosed, m_isOnButton;

    sf::Texture m_texButton, m_texBg;
    sf::Sprite m_sprBg;
    sf::Text m_txtTitle, m_txtQuitScreen;
};

#endif // GAMEENDSCREEN_H_INCLUDED
