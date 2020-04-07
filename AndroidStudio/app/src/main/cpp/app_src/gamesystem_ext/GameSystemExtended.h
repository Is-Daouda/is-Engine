#ifndef GAMESYSTEMEXTENDED_H_INCLUDED
#define GAMESYSTEMEXTENDED_H_INCLUDED

#include "../../isEngine/system/function/GameFunction.h"
#include "../config/GameConfig.h"
#include "../levels/Level.h"

////////////////////////////////////////////////////////////
/// \brief Class derived from GameSystem to manage the
/// different engine components
///
/// Allows to manage the saving / loading of game and
/// configuration data, manipulate the data of the virtual
/// Game Pad and act on the different scenes of the game
////////////////////////////////////////////////////////////
class GameSystemExtended : public is::GameSystem
{
public:
    GameSystemExtended();

    ////////////////////////////////////////////////////////////
    /// \brief Allows to manipulate the different scenes
    ///
    ////////////////////////////////////////////////////////////
    enum DisplayOption
    {
        INTRO,               ///< Access the introduction scene
        RESTART_LEVEL,       ///< When player loses a life
        GAME_OPTION_RESTART, ///< When player restart the level with restart option
        NEXT_LEVEL,          ///< Access the next level scene
        MAIN_MENU,           ///< Access the main menu scene
        GAME_LEVEL,          ///< Access the game level scene
        GAME_OVER,           ///< Access the game over scene
        GAME_END_SCREEN      ///< Access the game end scene
    };

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
    DisplayOption m_launchOption = DisplayOption::INTRO; // Represents the first scene to be launched

    int   m_gameProgression;
    int   m_levelNumber;
    int   m_currentLevel;
    int   m_currentLives;
    int   m_currentBonus;
    int   m_currentScore;
    int   m_levelTime;
};

#endif // GAMESYSTEMEXTENDED_H_INCLUDED
