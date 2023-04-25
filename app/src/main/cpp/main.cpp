/*
  is::Engine (Infinity Solution Engine)
  Copyright (C) 2018-2023 Is Daouda <isdaouda.n@gmail.com>

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

#if defined(IS_ENGINE_VS_CODE)
#include "Main.hpp"
#endif
#include "isEngine/core/GameEngine.h"

////////////////////////////////////////////////////////////
/// \brief application entry point
////////////////////////////////////////////////////////////
int main(int argc, char * argv[])
{
#if defined(IS_ENGINE_HTML_5)
    std::vector<std::string> vectorArray;
    char saveDir[is::GameConfig::DATA_PARENT_DIR.size() - 1];
    for (unsigned int i(0); i < is::GameConfig::DATA_PARENT_DIR.size() - 1; i++)
        saveDir[i] = is::GameConfig::DATA_PARENT_DIR[i];
    vectorArray.push_back(saveDir);
    EM_ASM(
        var vectorArray = new Module.VectorString($0);
        FS.mkdir(vectorArray.get(0));
        FS.mount(IDBFS, {}, vectorArray.get(0));
        Module.print("Start file sync...");
        Module.syncdone = 0;
        FS.syncfs(true, function(err){
                Module.print("End file sync..");
                Module.syncdone = 1;
                });
      , &vectorArray);
#endif

#if !defined(IS_ENGINE_HTML_5)
    is::GameEngine game;
#else
    is::GameEngine *game = new is::GameEngine();
#endif
#if defined(IS_ENGINE_VS_CODE)
#if defined(_DEBUG)
	// Display a text in the console to inform that we are in Debug mode on Visual Studio Code
	is::showLog("Debug Mode Start!");
#endif
#ifdef SFML_SYSTEM_WINDOWS
	// Allows to create the icon for the application when developing with Visual Studio Code
	windowsHelper.setIcon(game.getRenderWindow().getSystemHandle());
#endif
#endif
#if !defined(IS_ENGINE_HTML_5)
    game.
#else
    game->
#endif
#if defined(IS_ENGINE_USE_MAIN_LOOP)
        play
#else
        basicSFMLmain
#endif
        ();
#if defined(IS_ENGINE_HTML_5)
    delete game;
    game = nullptr;
#endif
#if defined(IS_ENGINE_SDL_2)
    is::SDL2freeLib();
#endif
#if defined (__ANDROID__)
    std::terminate(); // close application
#else
    return 0;
#endif
}
