/*
  is::Engine (Infinity Solution Engine)
  Copyright (C) 2018-2021 Is Daouda <isdaouda.n@gmail.com>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include "GameEngine.h"

#if defined(IS_ENGINE_HTML_5)
std::function<void(void)> mainLoop;
void MainLoop()
{
    return mainLoop();
}
#endif

namespace is
{
GameEngine::GameEngine():
    m_gameSysExt(m_window)
{
    srand((unsigned int)time(0));
}

GameEngine::~GameEngine()
{
#if defined(IS_ENGINE_SDL_2)
    is::SDL2freeLib();
#endif
};

void GameEngine::initEngine()
{
    m_gameSysExt.initSystemData();
    m_window.create(sf::VideoMode(is::GameConfig::WINDOW_WIDTH, is::GameConfig::WINDOW_HEIGHT),
                    is::GameConfig::GAME_NAME,
                    is::getWindowStyle());

    #if !defined(__ANDROID__)
    #if defined(IS_ENGINE_SFML)
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
    #endif // defined

    setFPS(m_window, is::GameConfig::FPS);
}

#if defined(IS_ENGINE_HTML_5)
void GameEngine::execMainLoop(std::function<bool(void)> loop)
{
    mainLoop = [myLoop = loop] {(void)myLoop();};
    emscripten_set_main_loop(&MainLoop, -1, 1);
}

void GameEngine::execMainLoop(std::function<void(void)> loop)
{
    mainLoop = loop;
    emscripten_set_main_loop(&MainLoop, -1, 1);
}
#endif

bool GameEngine::play()
{
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      GAME INTILISATION
//////////////////////////////////////////////////////////////////////////////////////////////////////
    initEngine();

    #if defined(__ANDROID__)
    #if defined(IS_ENGINE_USE_ADMOB)
    JNIEnv* env = (JNIEnv*)SDL_AndroidGetJNIEnv();
    jobject activity = (jobject)SDL_AndroidGetActivity();
    JavaVM* vm;
    env->GetJavaVM(&vm);
    vm->AttachCurrentThread(&env, NULL);

    m_gameSysExt.m_admobManager = std::make_shared<AdmobManager>(m_window, activity, env);
    m_gameSysExt.m_admobManager->checkAdObjInit();
    #endif // definded
    #endif // defined

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         GAME STARTUP
//////////////////////////////////////////////////////////////////////////////////////////////////////
    std::unique_ptr<ActivityController> app = nullptr;
#if !defined(IS_ENGINE_HTML_5)
    while (m_window.isOpen())
#else
    EM_ASM(console.log("Start successfully!");, 0);
    execMainLoop([&]
    {
    if (emscripten_run_script_int("Module.syncdone") == 1)
#endif
    {
        if (app == nullptr) app = std::make_unique<ActivityController>(m_gameSysExt);
        else
        {
            app->update();
            app->draw();
        }
    }
#if defined(IS_ENGINE_HTML_5)
    });
#endif
    return true;
}
}
