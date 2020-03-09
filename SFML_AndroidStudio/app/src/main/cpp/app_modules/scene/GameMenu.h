#ifndef GAMEMENU_H_INCLUDED
#define GAMEMENU_H_INCLUDED

#include "../system/function/GameFunction.h"
#include "../system/display/GameDisplay.h"
#include "../config/GameVersion.h"

class GameMenu : public is::GameDisplay
{
public:
    GameMenu(sf::RenderWindow &window, DisplayOption &m_launchOption, GameSystemExtended &gameSysExt);
    ~GameMenu();

    void step();
    void draw();

    bool loadResources();

private:
    sf::Texture m_texButton, m_texBg;
    sf::Sprite m_sprButton[2], m_sprBg;

    sf::Text m_txtStartGame, m_txtContinue, m_txtTitle, m_txtVersion;
    sf::Text m_txtOptionValue[3];

    sf::Keyboard::Key keyBack;

    int levelIndex, m_gameOptionIndex;
    int TXT_OPTION_NUMBER;
    float m_txtOptionScale[3];
    bool m_isStarted, m_saveFileOpen;
    bool m_isClosed, m_closeApplication;
};

#endif // GAMEMENU_H_INCLUDED
