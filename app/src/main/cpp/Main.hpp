#ifndef MAIN_HPP
#define MAIN_HPP

#ifdef __APPLE__
	#include "vscode/MacOS/MacHelper.hpp"
	MacHelper macHelper;
#endif // __APPLE__

#ifdef __linux__
	#include "vscode/Linux/LinuxHelper.hpp"
	LinuxHelper linuxHelper;
#endif // __linux__

#ifdef _WIN32
	#include "vscode/Win32/WindowsHelper.hpp"
	WindowsHelper windowsHelper;
#endif // _WIN32

//

#endif // MAIN_HPP
