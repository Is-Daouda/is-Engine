#ifndef GAMEOVER_H_INCLUDED
#define GAMEOVER_H_INCLUDED

#include "../../../isEngine/system/display/GameDisplay.h"

class GameOver : public is::GameDisplay
{
public:
    GameOver(sf::RenderWindow &window, sf::View &view, sf::RenderTexture &surface, GameSystemExtended& GameSystemExtended);
    ~GameOver();

    void step();
    void draw();

    void loadResources();

private:
    sf::Texture m_texPad, m_texScreenBG;
    sf::Sprite m_sprPad1, m_sprPad2, m_sprScreenBG;
    sf::Font m_fontTitle;
    sf::Text m_txtRestartGame, m_txtResumeGame, m_txtQuitGame, m_txtGameOver;

    float m_oscillation, m_bgX, m_bgY, m_TitleX, m_TitleY;
};

#endif // GAMEOVER_H_INCLUDED
