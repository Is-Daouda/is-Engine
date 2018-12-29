#ifndef GAMEOVER_H_INCLUDED
#define GAMEOVER_H_INCLUDED

#include "../system/display/GameDisplay.h"

class GameOver : public is::GameDisplay
{
public:
    GameOver(sf::RenderWindow &window, DisplayOption &m_launchOption, GameSystemExtended& GameSystemExtended);
    ~GameOver();

    void step();
    void draw();

    bool loadResources();

private:
    sf::Texture m_texButton, m_texBg;
    sf::Sprite m_sprButton[2], m_sprBg;
    sf::Text m_txtRestartGame, m_txtQuitGame, m_txtTitle;

    bool m_isStarted;
    bool m_isClosed;
};

#endif // GAMEOVER_H_INCLUDED
