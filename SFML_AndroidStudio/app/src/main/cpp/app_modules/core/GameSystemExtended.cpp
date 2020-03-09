#include "GameSystemExtended.h"

GameSystemExtended::GameSystemExtended() :
    GameSystem()
{

}

void GameSystemExtended::initProgress()
{
    m_gameProgression = 0; // LEVEL 1
    m_currentBonus = 0;
    m_currentLevel= 0;
    m_currentLives = 3;
}

void GameSystemExtended::initSystemData()
{
    m_levelNumber = LEVEL_3; // game level number
}

void GameSystemExtended::initData(bool clearCurrentLevel)
{
    if (clearCurrentLevel) m_currentLevel = 0; // LEVEL 1
    m_currentBonus = 0;
    m_currentLives = 3;
}

void GameSystemExtended::saveData(std::string const &fileName)
{
    FILE *file = NULL;
    file = fopen(fileName.c_str(), "wb");

    if (file != NULL)
    {
        fwrite(&m_gameProgression, sizeof(int), 1, file);
        fwrite(&m_currentLives, sizeof(int), 1, file);
        fclose(file);
    }
}

void GameSystemExtended::loadData(std::string const &fileName)
{
    FILE *file = NULL;
    file = fopen(fileName.c_str(), "rb");

    if (file != NULL)
    {
        fread(&m_gameProgression, sizeof(int), 1, file);
        fread(&m_currentLives, sizeof(int), 1, file);
        m_currentLevel = m_gameProgression;
        fclose(file);
    }
}

void GameSystemExtended::saveConfig(std::string const &fileName)
{
    FILE *file = NULL;
    file = fopen(fileName.c_str(), "wb");

    if (file != NULL)
    {
        fwrite(&m_enableSound, sizeof(bool), 1, file);
        fwrite(&m_enableMusic, sizeof(bool), 1, file);
        fwrite(&m_enableVibrate, sizeof(bool), 1, file);
        fclose(file);
    }
}

void GameSystemExtended::loadConfig(std::string const &fileName)
{
    FILE *file = NULL;
    file = fopen(fileName.c_str(), "rb");

    if (file != NULL)
    {
        fread(&m_enableSound, sizeof(bool), 1, file);
        fread(&m_enableMusic, sizeof(bool), 1, file);
        fread(&m_enableVibrate, sizeof(bool), 1, file);
        fclose(file);
    }
}
