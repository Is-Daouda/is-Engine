/*
  is::Engine (Infinity Solutions Engine)
  Copyright (C) 2018-2022 Is Daouda <isdaouda.n@gmail.com>

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

#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED

#include "ActivityController.h"
#include <functional>

////////////////////////////////////////////////////////////
// PC version code
#if !defined(__ANDROID__)
    #if !defined(SFML_SYSTEM_LINUX) && !defined(IS_ENGINE_HTML_5) && !defined(IS_ENGINE_LINUX)
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
private:
    sf::RenderWindow m_window;
    is::GameSystemExtended m_gameSysExt;

public:
    GameEngine();

    ~GameEngine();

    /// Initialize game engine
    void initEngine();

#if defined(IS_ENGINE_HTML_5)
    /// Allow to launch main loop
    void execMainLoop(std::function<bool(void)> loop);
    void execMainLoop(std::function<void(void)> loop);
#endif

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
};
}

#endif // GAMEENGINE_H_INCLUDED
