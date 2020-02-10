#include "core/GameEngine.h"

////////////////////////////////////////////////////////////
/// \brief application entry point
////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    GameEngine game(is::GameDisplay::DisplayOption::INTRO);

    if (!game.play())
    {
        #if defined (__ANDROID__)
        std::terminate(); // close application
        #else
        return EXIT_FAILURE;
        #endif // defined
    }
}