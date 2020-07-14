#include "GameLevel.h"

GameLevel::GameLevel(sf::RenderWindow &window, sf::View &view, sf::RenderTexture &surface, GameSystemExtended &gameSysExt):
    GameDisplay(window, view, surface, gameSysExt, sf::Color::White),
    CURRENT_LEVEL(gameSysExt.m_currentLevel),
    m_restartTime(0),
    m_timeUp(false),
    m_countLevelTime(true)
{
    // redefine view parameter
    m_viewX = (m_viewW / 2.f);
    m_viewY = (m_viewH / 2.f);

    srand(time(NULL));
}


GameLevel::~GameLevel() {}
