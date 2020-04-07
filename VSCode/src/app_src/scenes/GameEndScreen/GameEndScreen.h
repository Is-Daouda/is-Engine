#ifndef GAMEENDSCREEN_H_INCLUDED
#define GAMEENDSCREEN_H_INCLUDED

#include "../../../isEngine/system/display/GameDisplay.h"

class GameEndScreen : public is::GameDisplay
{
public:
    GameEndScreen(sf::RenderWindow &window, sf::View &view, sf::RenderTexture &surface, GameSystemExtended& GameSystemExtended);
    ~GameEndScreen();

    void step();
    void draw();

    bool loadResources();

private:
    float m_oscillation, m_bgX, m_bgY;
    bool m_isStart, m_isOnPad;
    sf::Font m_fontTitle;

    sf::Texture m_texScreenBG, m_texPad;
    sf::Sprite m_sprScreenBG;
    sf::Text m_txtQuitScreen, m_txtEndTitle, m_txtEndMsg;
};

#endif // GAMEENDSCREEN_H_INCLUDED
