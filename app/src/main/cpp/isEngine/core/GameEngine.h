#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED

#include "../../app_src/activity/GameActivity.h"

////////////////////////////////////////////////////////////
// PC version code
#if !defined(__ANDROID__)
#if !defined(SFML_SYSTEM_LINUX)
#include <direct.h>
#else
#include <sys/stat.h>
#endif // defined
#else
#if defined(IS_ENGINE_USE_ADMOB)
#include "../system/android/AdmobManager.h"
#endif
#endif // defined
////////////////////////////////////////////////////////////

namespace is
{
////////////////////////////////////////////////////////////
/// \brief Class to operate the entire game system
///
/// It allows the interconnection of different engine components
////////////////////////////////////////////////////////////
class GameEngine
{
public:
    GameEngine(){};
    ~GameEngine();

    /// Initialize game engine
    void initEngine();

    /// Starts the engine rendering loop
    bool play();

    ////////////////////////////////////////////////////////////
    /// \brief Starts the SFML classic rendering loop
    ///
    /// Useful for implementing a custom rendering loop to facilitate
    /// the integration of other projects with the engine
    ////////////////////////////////////////////////////////////
    bool basicSFMLmain();

    /// return Render Window
    sf::RenderWindow& getRenderWindow() {return m_window;}

private:
    sf::RenderWindow m_window;
    is::GameSystemExtended m_gameSysExt;
};
}

#endif // GAMEENGINE_H_INCLUDED
