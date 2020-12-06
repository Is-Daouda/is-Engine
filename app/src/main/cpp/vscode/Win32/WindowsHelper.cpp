#ifdef _WIN32
#include "WindowsHelper.hpp"

#include "Icon.h"

/******************************************************************************
 *
 *****************************************************************************/
WindowsHelper::WindowsHelper()
{
	// Get the icon directory
	PBYTE iconDirectory = getIconDirectory(WIN32_ICON_MAIN);

	// Store each icon
	m_hIcon32 = getIconFromIconDirectory(iconDirectory, 32);
	m_hIcon16 = getIconFromIconDirectory(iconDirectory, 16);
}

/******************************************************************************
 * The window handle uses 32x32 (ICON_BIG) & 16x16 (ICON_SMALL) sized icons.
 * This should be called any time the SFML window is create/recreated
 *****************************************************************************/
void WindowsHelper::setIcon(const HWND& inHandle)
{
	if (m_hIcon32)
		SendMessage(inHandle, WM_SETICON, ICON_BIG, (LPARAM)m_hIcon32);
	if (m_hIcon16)
		SendMessage(inHandle, WM_SETICON, ICON_SMALL, (LPARAM)m_hIcon16);
}

/******************************************************************************
 * Loads a .ico file from The application's resources, and can contain multiple
 * sizes (for instance 16x16, 32x32 & 64x64). This is referred to as an
 * "Icon Directory". Additionally, it can have a single icon
 *****************************************************************************/
PBYTE WindowsHelper::getIconDirectory(const int& inResourceId)
{
	HMODULE hModule = GetModuleHandle(nullptr);
	HRSRC hResource = FindResource(hModule, MAKEINTRESOURCE(inResourceId), RT_GROUP_ICON);

	HGLOBAL hData = LoadResource(hModule, hResource);
	PBYTE data = (PBYTE)LockResource(hData);

	return data;
}

/******************************************************************************
 * This will attempt to load a single icon from an icon directory
 * If the requested size isn't found, the first one is returned
 *****************************************************************************/
HICON WindowsHelper::getIconFromIconDirectory(const PBYTE& inIconDirectory, const uint& inSize)
{
	HMODULE hModule = GetModuleHandle(nullptr);
	int resourceId = LookupIconIdFromDirectoryEx(inIconDirectory, TRUE, inSize, inSize, LR_DEFAULTCOLOR);
	HRSRC hResource = FindResource(hModule, MAKEINTRESOURCE(resourceId), RT_ICON);

	HGLOBAL hData = LoadResource(hModule, hResource);
	PBYTE data = (PBYTE)LockResource(hData);
	DWORD sizeofData = SizeofResource(hModule, hResource);

	HICON icon = CreateIconFromResourceEx(data, sizeofData, TRUE, 0x00030000, inSize, inSize, LR_DEFAULTCOLOR);
	return icon;
}

#endif
