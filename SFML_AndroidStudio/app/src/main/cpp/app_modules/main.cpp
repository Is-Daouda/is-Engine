#include "core/GameEngine.h"

////////////////////////////////////////////////////////////
/// \brief application entry point
////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    GameEngine game(is::GameDisplay::DisplayOption::INTRO);

    game.play();

    // uncomment "game.basicSFMLMain()" to display a basic sfml window
    // if this line is uncommented you must comment this one "game.play()"
    // to avoid using the main engine rendering loop
    /**
    game.basicSFMLMain();
    **/

    #if defined (__ANDROID__)
    std::terminate(); // close application
    #else
    return 0;
    #endif // defined
}
