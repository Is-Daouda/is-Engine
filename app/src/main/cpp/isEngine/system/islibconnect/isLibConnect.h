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

#ifndef ISLIBCONNECT_H_INCLUDED
#define ISLIBCONNECT_H_INCLUDED

#if defined(__ANDROID__)
#define IS_ENGINE_SDL_2
#endif

#if defined(IS_ENGINE_HTML_5)
    #include "isEngineSMKWrapper.h"
#elif defined(IS_ENGINE_SDL_2)
    #include "isEngineSDLWrapper.h"
#else
    #include <SFML/Audio.hpp>
    #include <SFML/Network.hpp>
    #include <SFML/Graphics.hpp>
    #include <SFML/Window.hpp>
    #include <SFML/System.hpp>
    #include "isEngineWrapper.h"
#endif

#if !defined(IS_ENGINE_HTML_5) && !defined(IS_ENGINE_SDL_2)
#define IS_ENGINE_SFML
#endif

namespace is
{
typedef sf::RenderWindow Render;
}

#endif // ISLIBCONNECT_H_INCLUDED
