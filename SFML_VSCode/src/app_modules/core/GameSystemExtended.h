#ifndef GAMESYSTEMEXTENDED_H_INCLUDED
#define GAMESYSTEMEXTENDED_H_INCLUDED

#include "../system/function/GameFunction.h"
#include "../config/GameFilesPath.h"

enum LevelId
{
    LEVEL_1,
    LEVEL_2,
	LEVEL_3
    // LEVEL_...,
};

class GameSystemExtended : public is::GameSystem
{
public:
    GameSystemExtended();

    void initSystemData();
    void initRecord();
    void initProgress();
    void initData(bool clearCurrentLevel = true);

    void saveData(std::string const &fileName);
    void loadData(std::string const &fileName);
    void saveConfig(std::string const &fileName);
    void loadConfig(std::string const &fileName);

    int m_gameProgression;
    int m_currentLevel;
    int m_currentLives;
    int m_currentBonus;
    int m_levelNumber;
};

#endif // GAMESYSTEMEXTENDED_H_INCLUDED
