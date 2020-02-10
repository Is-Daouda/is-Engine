#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED

#include "../scene/GameIntro.h"
#include "../scene/GameMenu.h"
#include "../scene/GameOver.h"
#include "../scene/GameLevel.h"
#include "../scene/GameEndScreen.h"

////////////////////////////////////////////////////////////
// PC version code
#if !defined(__ANDROID__)
#if !defined(LINUX_VERSION)
#include <direct.h>
#else
#include <sys/stat.h>
#endif // defined
#else
#if defined(ENABLE_ADMOB)
#include "../system/android/AdmobManager.h"
#endif
#endif // defined
////////////////////////////////////////////////////////////

class GameEngine
{
public:
    GameEngine(is::GameDisplay::DisplayOption index);
    ~GameEngine();

    bool initEngine();
    bool play();

private:
    bool m_launchAd;

    sf::RenderWindow m_app;
    sf::View m_view;
    GameSystemExtended m_gameSysExt;

    GameIntro *m_gameIntroScreen;
    GameMenu *m_gameMenuScreen;
    GameLevel *m_gameLevelScreen;
    GameOver *m_gameOverScreen;
    GameEndScreen *m_gameEndScreen;

    is::GameDisplay::DisplayOption m_launchOption;
};

#endif // GAMEENGINE_H_INCLUDED
