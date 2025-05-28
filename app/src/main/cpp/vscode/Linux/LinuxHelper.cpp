#ifdef __linux__
#include "LinuxHelper.hpp"

#include <X11/Xlib.h>

/******************************************************************************
 *
 *****************************************************************************/
LinuxHelper::LinuxHelper()
{
	XInitThreads();
}

#endif
