#include "GameSystemExtended.h"

namespace is
{
GameSystemExtended::GameSystemExtended(sf::RenderWindow &window) :
    GameSystem(window)
{
    initProgress();

    // Default position of the Virtual Pad Game on the screen
    m_defaultPadDirXPos = -250.f;
    m_defaultPadDirYPos = 170.f;
    m_defaultPadActionXPos = 245.f;
    m_defaultPadActionYPos = 200.f;

    // Configurable position of the Virtual Pad Game on the screen
    m_padDirXPos = m_defaultPadDirXPos;
    m_padDirYPos = m_defaultPadDirYPos;
    m_padActionXPos = m_defaultPadActionXPos;
    m_padActionYPos = m_defaultPadActionYPos;
    m_permutePadAB = false;
    m_padAlpha = 255;
}

void GameSystemExtended::initProgress()
{
    m_gameProgression = 0; // LEVEL 1
    m_currentLives = 3;
    m_currentBonus = 0;
    m_currentLevel = 0;
    m_currentScore = 0;
    m_currentHiScore = 0;
}

void GameSystemExtended::initSystemData()
{
    // global variable
    m_gameLanguage = 0;
    m_firstLaunch = true;

    // Determine the number of levels
    // LEVEL_MAX - 1 because we count the number of levels from zero (0) as for the array)
    m_levelNumber = is::level::LevelId::LEVEL_MAX - 1;

    initProgress();
}

void GameSystemExtended::initData(bool clearCurrentLevel)
{
    if (clearCurrentLevel) m_currentLevel = 0; // LEVEL 1
    m_currentLives = 3;
    m_currentBonus = 0;
    m_currentScore = 0;
}

void GameSystemExtended::saveData(std::string const &fileName)
{
    FILE *file = NULL;
    file = fopen(fileName.c_str(), "wb");

    if (file != NULL)
    {
        fwrite(&m_gameProgression, sizeof(int), 1, file);
        fwrite(&m_currentLives, sizeof(int), 1, file);
        fwrite(&m_currentBonus, sizeof(int), 1, file);
        fwrite(&m_currentHiScore, sizeof(int), 1, file);
        fclose(file);
#if defined(IS_ENGINE_HTML_5)
        EM_ASM(FS.syncfs(false, function(err){console.log(err)});, 0);
#endif
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
        fread(&m_currentBonus, sizeof(int), 1, file);
        fread(&m_currentHiScore, sizeof(int), 1, file);
        fclose(file);
    }
}
}
