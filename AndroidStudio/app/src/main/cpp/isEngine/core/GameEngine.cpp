#include "GameEngine.h"

GameEngine::~GameEngine()
{
    #if defined(__ANDROID__)
    /// uncomment to active lock screen on Android
    // is::setScreenLock(false);
    #endif // defined
}

bool GameEngine::initEngine()
{
    m_gameSysExt.initSystemData();
    m_window.create(sf::VideoMode(is::GameConfig::WINDOW_WIDTH, is::GameConfig::WINDOW_HEIGHT),
                    is::GameConfig::GAME_NAME,
                    is::getWindowStyle());

    #if !defined(__ANDROID__)
    // load application icon
    sf::Image iconTex;
    if (!iconTex.loadFromFile(is::GameConfig::GUI_DIR + "icon.png")) return false;
    m_window.setIcon(iconTex.getSize().x, iconTex.getSize().y, iconTex.getPixelsPtr());

    // create saving directory
    if (!m_gameSysExt.fileExist(is::GameConfig::CONFIG_FILE))
    {
        #if !defined(SFML_SYSTEM_LINUX)
        mkdir("save");
        #else
        mkdir("save", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        #endif
        m_gameSysExt.saveConfig(is::GameConfig::CONFIG_FILE);
    }
    #else
        /// uncomment to disable lock screen on Android
        // is::setScreenLock(true);
    #endif // defined

    m_window.setFramerateLimit(is::GameConfig::FPS);
    return true;
}

bool GameEngine::play()
{
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      GAME INTILISATION
//////////////////////////////////////////////////////////////////////////////////////////////////////
    if (!initEngine()) return false;

    #if defined(__ANDROID__)
    #if defined(IS_ENGINE_USE_ADMOB)
    ANativeActivity* activity = sf::getNativeActivity();
    JNIEnv* env = activity->env;
    JavaVM* vm = activity->vm;
    vm->AttachCurrentThread(&env, NULL);

    AdmobManager *admobManager = 0;
    admobManager = new AdmobManager(m_window, activity, env, vm);
    admobManager->checkAdObjInit();
    #endif // definded
    #endif // defined

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         GAME STARTUP
//////////////////////////////////////////////////////////////////////////////////////////////////////

    ActivityController app(m_window);
    app.push<GameActivity>(m_gameSysExt);

#if 1 || __ANDROID__
    app.optimizeForPerformance(true);
#endif

    // run the program as long as the window is open
    float elapsed(0.0f);
    sf::Clock clock;
    srand((unsigned int)time(0));
    while (m_window.isOpen())
    {
        clock.restart();
        m_window.clear();
        app.update(elapsed);
        app.draw();
        m_window.display();
        elapsed = static_cast<float>(clock.getElapsedTime().asSeconds());
    }

    #if defined(__ANDROID__)
    #if defined(IS_ENGINE_USE_ADMOB)
     if (is::instanceExist(admobManager))
     {
         delete admobManager;
         admobManager = 0;
     }
    #endif
    #endif // defined
    return true;
}
