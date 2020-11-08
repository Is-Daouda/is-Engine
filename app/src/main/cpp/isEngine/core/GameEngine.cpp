#include "GameEngine.h"

namespace is
{
GameEngine::GameEngine():
    m_gameSysExt(m_window)
{
    srand((unsigned int)time(0));
}

GameEngine::~GameEngine()
{
    #if defined(__ANDROID__)
    /// uncomment to active lock screen on Android
    // is::setScreenLock(false);
    #endif // defined
}

void GameEngine::initEngine()
{
    m_gameSysExt.initSystemData();
    #if !defined(IS_ENGINE_HTML_5)
    m_window.create(sf::VideoMode(is::GameConfig::WINDOW_WIDTH, is::GameConfig::WINDOW_HEIGHT),
                    is::GameConfig::GAME_NAME,
                    is::getWindowStyle());
    #else
    m_window = sf::RenderWindow(is::GameConfig::WINDOW_WIDTH, is::GameConfig::WINDOW_HEIGHT, is::GameConfig::GAME_NAME);
    #endif

    #if !defined(__ANDROID__)
    #if !defined(IS_ENGINE_HTML_5)
    // load application icon
    sf::Image iconTex;
    if (iconTex.loadFromFile(is::GameConfig::GUI_DIR + "icon.png"))
    	m_window.setIcon(iconTex.getSize().x, iconTex.getSize().y, iconTex.getPixelsPtr());
    #endif

    // create saving directory
#if !defined(IS_ENGINE_HTML_5)
    if (!m_gameSysExt.fileExist(is::GameConfig::CONFIG_FILE))
    {

        mkdir(is::GameConfig::DATA_PARENT_DIR.c_str()
                #if defined(SFML_SYSTEM_LINUX)
                , S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH
                #endif
              );

        m_gameSysExt.saveConfig(is::GameConfig::CONFIG_FILE);
    }
#endif
    #else
        /// uncomment to disable lock screen on Android
        // is::setScreenLock(true);
    #endif // defined

    setFPS(m_window, is::GameConfig::FPS);
}

bool GameEngine::play()
{
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      GAME INTILISATION
//////////////////////////////////////////////////////////////////////////////////////////////////////
    initEngine();

    #if defined(__ANDROID__)
    #if defined(IS_ENGINE_USE_ADMOB)
    ANativeActivity* activity = sf::getNativeActivity();
    JNIEnv* env = activity->env;
    JavaVM* vm = activity->vm;
    vm->AttachCurrentThread(&env, NULL);

    AdmobManager *admobManager = nullptr;
    admobManager = new AdmobManager(m_window, activity, env, vm);
    admobManager->checkAdObjInit();
    #endif // definded
    #endif // defined

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         GAME STARTUP
//////////////////////////////////////////////////////////////////////////////////////////////////////
#if !defined(IS_ENGINE_HTML_5)
    #if defined(IS_ENGINE_RENDER)
    ActivityController app(m_gameSysExt);
    #else
    float elapsed(0.0f);
    sf::Clock clock;
    ActivityController app(m_window);
    app.push<GameActivity>(m_gameSysExt);
        #if defined(IS_ENGINE_OPTIMIZE_PERF)
        app.optimizeForPerformance(true);
        #endif
    #endif
    while (m_window.isOpen())
#else
    ActivityController app(m_gameSysExt);
    m_window.ExecuteMainLoop([&]
#endif
    {
        #if (defined(IS_ENGINE_HTML_5) || defined(IS_ENGINE_RENDER))
            #if defined(IS_ENGINE_HTML_5)
            m_window.PoolEvents();
            #endif
        app.update();
        #else
        m_window.clear();
        app.update(elapsed);
        #endif
        app.draw();
        is::display(m_window);
        #if (!defined(IS_ENGINE_HTML_5) && !defined(IS_ENGINE_RENDER))
        elapsed = static_cast<float>(clock.getElapsedTime().asSeconds());
        #endif
    }
    #if defined(IS_ENGINE_HTML_5)
    );
    #endif // defined

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

}
