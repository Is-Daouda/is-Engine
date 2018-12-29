#include "GameLevel.h"

GameLevel::GameLevel(sf::RenderWindow &window, DisplayOption &m_launchOption, GameSystemExtended &gameSysExt, bool &launchAd):
    GameDisplay(window, m_launchOption, gameSysExt, sf::Color::Black),
    m_gameHud(),
    CURRENT_LEVEL(gameSysExt.m_currentLevel),
    m_levelWidth(0),
    m_levelHeight(0),
    m_restartTime(0),
    m_buttonY(-40.f),
    m_isPlaying(true),
    m_levelStart(false),
    m_levelEnd(false),
    m_levelCompleted(false),
    m_pauseKeyPressed(false),
    m_rotationKeyPressed(false),
    m_speedKeyPression(false),
    m_timeUp(false),
    m_playerExploseSnd(false),
    m_launchAd(launchAd)
{
    srand(time(NULL));
}

GameLevel::~GameLevel()
{
    // destroy blocs
    WITH(m_blocList.size())
    {
        is::instanceDestroy(m_blocList[_I]);
    }

    // destroy bonus
    WITH(m_bonusList.size())
    {
        is::instanceDestroy(m_bonusList[_I]);
    }

    // destroy tiles map
    WITH(m_levelTile.size())
    {
        is::instanceDestroy(m_levelTile[_I]);
    }
}
