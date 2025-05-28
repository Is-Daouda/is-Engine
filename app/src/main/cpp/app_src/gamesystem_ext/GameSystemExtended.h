#ifndef GAMESYSTEMEXTENDED_H_INCLUDED
#define GAMESYSTEMEXTENDED_H_INCLUDED

#include "../../isEngine/system/function/GameSystem.h"
#include "../levels/Level.h"

////////////////////////////////////////////////////////////
/// \brief Class derived from GameSystem to manage the
/// different engine components
///
/// Allows to manage the saving / loading of game and
/// configuration data, manipulate the data of the virtual
/// Game Pad and act on the different scenes of the game
////////////////////////////////////////////////////////////
namespace is
{
class GameSystemExtended : public GameSystem
{
public:
    GameSystemExtended(sf::RenderWindow &window);

    /// Initialize the data link to the game engine
    void initSystemData();

    /// Initialize game progress data
    void initProgress();

    /// Initialize game play data (bonus, score, ...)
    void initData(bool clearCurrentLevel = true);

    /// Save game play data
    void saveData(std::string const &fileName);

    /// Load game play data
    void loadData(std::string const &fileName);

    /// Allows to choose the scene that will be launched
    is::DisplayOption m_launchOption = is::GameConfig::LAUNCH_OPTION; // Represents the first scene to be launched

    int   m_gameProgression;
    int   m_levelNumber;
    int   m_currentLevel;
    int   m_currentLives;
    int   m_currentBonus;
    int   m_currentScore;
    int   m_currentHiScore;
    int   m_levelTime;
};
}

#endif // GAMESYSTEMEXTENDED_H_INCLUDED
