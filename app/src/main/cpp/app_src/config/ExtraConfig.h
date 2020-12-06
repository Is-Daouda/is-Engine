#ifndef EXTRACONFIG_H_INCLUDED
#define EXTRACONFIG_H_INCLUDED

// Uncomment to enable this function
#define IS_ENGINE_RENDER ///< Allows engine to run on old machine

/*
 * 1) Uncomment this line (definition of the Preporcessor which is below) to use the engine's main render loop.
 * 2) But if you want to use a basic SFML render loop comment out this line.
 *    It activates the "basicSFMLmain()" function which launches an SFML window.
 *    Very useful if you already have an existing project and want to integrate it into the engine.
 *    The "basicSFMLmain()" function is implemented in the "basicSFMLmain.cpp" file (found in the "cpp" directory).
 *    It is in this file that you can associate your code with that of the engine.
 */
#define IS_ENGINE_USE_MAIN_LOOP ///< Allows to use the engine's main render loop

// Uncomment to enable SDM function
#define IS_ENGINE_USE_SDM ///< Allows to use Step and Draw Manager

// Uncomment to enable this function
#define IS_ENGINE_OPTIMIZE_PERF ///< Allows to activate the optimization in certain parts of the engine

// Uncomment to enable SHOW LOG function
#define IS_ENGINE_USE_SHOWLOG ///< Allows to show log in console

#if defined(__ANDROID__)
// Uncomment this line (definition of the Preporcessor which is below) to use Admob
// If you enable Admob you need to uncomment line in CMakeLists
// and Gradle files to link the Firebase library on your project
// #define IS_ENGINE_USE_ADMOB ///< Allows to use Admob Manager
#endif // defined

#include <string>
#include <fstream>
#include <cstdio>
#include <iostream>

namespace is
{
inline bool fileExist(std::string const &fileName)
{
    std::ifstream file(fileName.c_str());
    return !file.fail();
}
}

#endif // EXTRACONFIG_H_INCLUDED
