#include "Main.hpp"
#include "app_modules/core/GameEngine.h"

int main()
{
#if defined(_DEBUG)
	std::cout << "Debug Mode Start!" << std::endl;
#endif
    GameEngine game(is::GameDisplay::DisplayOption::INTRO);
    game.play();

    // uncomment "game.basicSFMLMain()" to display a basic sfml window
    // if this line is uncommented you must comment this one "game.play()"
    // to avoid using the main engine rendering loop
    /**
    game.basicSFMLMain();
    **/
#ifdef SFML_SYSTEM_WINDOWS
	__windowsHelper.setIcon(game.getRenderWindow().getSystemHandle());
#endif

#if defined (__ANDROID__)
    std::terminate(); // close application
#else
	return 0;
#endif // defined
}
