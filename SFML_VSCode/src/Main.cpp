#include "Main.hpp"
#include "app_modules/core/GameEngine.h"

int main()
{
#if defined(_DEBUG)
	std::cout << "Debug Mode Start!" << std::endl;
#endif
    GameEngine game(is::GameDisplay::DisplayOption::INTRO);
    game.play();
#ifdef SFML_SYSTEM_WINDOWS
	__windowsHelper.setIcon(game.getRenderWindow().getSystemHandle());
#endif

#if defined (__ANDROID__)
    std::terminate(); // close application
#endif // defined

	return 0;
}
