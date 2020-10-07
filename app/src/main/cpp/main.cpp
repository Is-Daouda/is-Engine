#if defined(IS_ENGINE_VS_CODE)
#include "Main.hpp"
#endif
#include "isEngine/core/GameEngine.h"

////////////////////////////////////////////////////////////
/// \brief application entry point
////////////////////////////////////////////////////////////
int main()
{
#if defined(IS_ENGINE_VS_CODE)
#if defined(_DEBUG)
	// Display a text in the console to inform that we are in Debug mode on Visual Studio Code
	is::showLog("Debug Mode Start!");
#endif
#endif
    is::GameEngine game;
#if defined(IS_ENGINE_VS_CODE)
#ifdef SFML_SYSTEM_WINDOWS
	// Allows to create the icon for the application when developing with Visual Studio Code
	windowsHelper.setIcon(game.getRenderWindow().getSystemHandle());
#endif
#endif
    game.play();

    // uncomment "game.basicSFMLmain()" to display a basic SFML window
    // if this line is uncommented you must comment this one "game.play()"
    // to avoid using the main engine rendering loop
    /*
    game.basicSFMLmain();
    */
    #if defined (__ANDROID__)
    std::terminate(); // close application
    #else
    return 0;
    #endif // defined
}
