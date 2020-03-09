#include "GameEngine.h"

GameEngine::GameEngine(is::GameDisplay::DisplayOption index):
    m_launchAd(false),
    m_launchOption(index)
{
    m_gameIntroScreen = 0;
    m_gameMenuScreen = 0;
    m_gameLevelScreen = 0;
    m_gameOverScreen = 0;
    m_gameEndScreen = 0;
}

GameEngine::~GameEngine()
{
    is::instanceDestroy(m_gameIntroScreen);
    is::instanceDestroy(m_gameMenuScreen);
    is::instanceDestroy(m_gameLevelScreen);
    is::instanceDestroy(m_gameOverScreen);
    is::instanceDestroy(m_gameEndScreen);
    #if defined(__ANDROID__)
    /// uncomment to active lock screen on Android
    // is::setScreenLock(false);
    #endif // defined
}

bool GameEngine::initEngine()
{
    m_gameSysExt.initSystemData();
    m_gameSysExt.initProgress();

    ////////////////////////////////////////////////////////////
    // code for PC / Android version
    #if defined(__ANDROID__)
    m_app.create(sf::VideoMode::getDesktopMode(), "");
    /// uncomment to disable lock screen on Android
    // is::setScreenLock(true);
    #else
    m_app.create(sf::VideoMode(640, 480), "is::engine Demo", sf::Style::Close);

    // load application icon
    sf::Image iconTex;
    if (!iconTex.loadFromFile(is::GUI_DIR + "icon.png")) return false;
    m_app.setIcon(32, 32, iconTex.getPixelsPtr());

    // create saving directory
    if (!m_gameSysExt.fileExist(is::CONFIG_FILE))
    {
        #if !defined(LINUX_VERSION)
        mkdir("save");
        #else
        mkdir("save", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        #endif
        m_gameSysExt.saveConfig(is::CONFIG_FILE);
    }
    #endif // defined
    ////////////////////////////////////////////////////////////

    m_app.setFramerateLimit(60);
    return true;
}

bool GameEngine::play()
{
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      GAME INTILISATION
//////////////////////////////////////////////////////////////////////////////////////////////////////
    if (!initEngine()) return false;

    #if defined(__ANDROID__)
    #if defined(ENABLE_ADMOB)
    ANativeActivity* activity = sf::getNativeActivity();
    JNIEnv* env = activity->env;
    JavaVM* vm = activity->vm;
    vm->AttachCurrentThread(&env, NULL);

    AdmobManager *admobManager = 0;
    admobManager = new AdmobManager(m_app, activity, env, vm);
    admobManager->checkAdObjInit();
    #endif // defined
    #endif // defined

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         GAME STAR-TUP
//////////////////////////////////////////////////////////////////////////////////////////////////////
    while (m_app.isOpen())
    {
        switch (m_launchOption)
        {
            case is::GameDisplay::INTRO : // intro
                m_gameIntroScreen = new GameIntro(m_app, m_launchOption, m_gameSysExt);
                if (!m_gameIntroScreen->loadResources()) return false;
                while (m_gameIntroScreen->isRunning())
                {
                    m_gameIntroScreen->step();
                    m_gameIntroScreen->drawScreen();
                }
                #if defined(__ANDROID__)
                #if defined(ENABLE_ADMOB)
                admobManager->loadBannerAd();
                admobManager->loadInterstitialAd();
                #endif // defined
                #endif // defined
                delete m_gameIntroScreen;
                m_gameIntroScreen = 0;
            break;

            case is::GameDisplay::MAIN_MENU : // main menu
                m_gameSysExt.initData(); // initialize game variables
                m_gameMenuScreen = new GameMenu(m_app, m_launchOption, m_gameSysExt);
                if (!m_gameMenuScreen->loadResources()) return false;
                while (m_gameMenuScreen->isRunning())
                {
                    #if defined(__ANDROID__)
                    #if defined(ENABLE_ADMOB)
                    admobManager->showBannerAd();
                    #endif // defined
                    #endif // defined
                    m_gameMenuScreen->step();
                    m_gameMenuScreen->drawScreen();
                }
                #if defined(__ANDROID__)
                #if defined(ENABLE_ADMOB)
                admobManager->hideBannerAd();
                #endif // defined
                #endif // defined
                delete m_gameMenuScreen;
                m_gameMenuScreen = 0;
            break;

            case is::GameDisplay::DisplayOption::GAME_LEVEL : // game levels
                m_gameLevelScreen = new GameLevel(m_app, m_launchOption, m_gameSysExt, m_launchAd);
                if (!m_gameLevelScreen->loadResources()) return false;
                while (m_gameLevelScreen->isRunning())
                {
                    m_gameLevelScreen->step();
                    m_gameLevelScreen->drawScreen();
                }
                if (m_launchAd)
                {
                    #if defined(__ANDROID__)
                    #if defined(ENABLE_ADMOB)
                    admobManager->showInterstitialAd();
                    #endif // defined
                    #else
                    #if defined(ENABLE_ADMOB)
                    is::showLog("Interstitial Ad Showed !");
                    #endif // defined
                    #endif
                    m_launchAd = false;
                }
                delete m_gameLevelScreen;
                m_gameLevelScreen = 0;
            break;

            case is::GameDisplay::RESTART_LEVEL : // restart level (when player lose)
                // can restart level if have more than 1 live
                if (m_gameSysExt.m_currentLives > 1)
                {
                    m_gameSysExt.m_currentLives --;
                    m_gameSysExt.m_currentBonus = 0;
                    m_launchOption = is::GameDisplay::DisplayOption::GAME_LEVEL;
                    m_gameSysExt.saveData(is::DATA_FILE); // save progress
                }
                else // no more lives GAME OVER
                {
                    // clear all current data excepted game progress
                    m_gameSysExt.initData(false);
                    m_gameSysExt.m_currentBonus = 0;
                    m_gameSysExt.m_currentLives = 3;
                    m_launchOption = is::GameDisplay::GAME_OVER; // go to GAME OVER scene
                }
            break;

            case is::GameDisplay::NEXT_LEVEL : // next level (when player win)
               // clear level data
                m_gameSysExt.m_currentBonus = 0;
                #if defined(__ANDROID__)
                #if defined(ENABLE_ADMOB)
                admobManager->showInterstitialAd();
                #endif // defined
                #endif // defined
                m_launchOption = is::GameDisplay::DisplayOption::GAME_LEVEL; // go to next level

                // if current level value is superior than level number so player finish the game
                if (m_gameSysExt.m_currentLevel > m_gameSysExt.m_levelNumber)
                {
                    m_launchOption = is::GameDisplay::GAME_END_SCREEN; // go to game end scene
                }
            break;

            case is::GameDisplay::DisplayOption::GAME_RESTART: // restart level (when player use restart option)
                m_launchOption = is::GameDisplay::DisplayOption::GAME_LEVEL; // restart level

                // clear level data
                m_gameSysExt.initData(false);
            break;

            case is::GameDisplay::DisplayOption::GAME_OVER : // GAME OVER
                m_gameOverScreen = new GameOver(m_app, m_launchOption, m_gameSysExt);
                if (!m_gameOverScreen->loadResources()) return false;
                while (m_gameOverScreen->isRunning())
                {
                    m_gameOverScreen->step();
                    m_gameOverScreen->drawScreen();
                }
                delete m_gameOverScreen;
                m_gameOverScreen = 0;
            break;

            case is::GameDisplay::DisplayOption::GAME_END_SCREEN : // GAME END scene
                m_gameEndScreen = new GameEndScreen(m_app, m_launchOption, m_gameSysExt);
                if (!m_gameEndScreen->loadResources()) return false;
                while (m_gameEndScreen->isRunning())
                {
                    m_gameEndScreen->step();
                    m_gameEndScreen->drawScreen();
                }
                delete m_gameEndScreen;
                m_gameEndScreen = 0;
            break;
        }
    }

    #if defined(__ANDROID__)
    #if defined(ENABLE_ADMOB)
    if (is::instanceExist(admobManager))
    {
        delete admobManager;
        admobManager = 0;
    }
    #endif // defined
    #endif // defined
    return true;
}
