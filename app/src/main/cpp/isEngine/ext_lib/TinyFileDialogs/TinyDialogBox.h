/*
  is::Engine (Infinity Solutions Engine)
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

#ifndef TINYDIALOGBOX_H_INCLUDED
#define TINYDIALOGBOX_H_INCLUDED

#if !defined(__ANDROID__)
#include "../../ext_lib/TinyFileDialogs/tinyfiledialogs.h"
#include "../../system/function/GameFunction.h"

////////////////////////////////////////////////////////////
/// tinyString is a custom type it changes depending on the target platform (windows / linux)
/// on windows it becomes @a wchar_t @a const* and on linux @a char @a const*
////////////////////////////////////////////////////////////
#if !defined(SFML_SYSTEM_LINUX) && !defined(IS_ENGINE_LINUX)
typedef wchar_t const* tinyString;
#else
typedef char const* tinyString;
#endif

namespace is
{
    /// return file path
    static tinyString TINY_FILE_DIALOGBOX_PATH;

    /// \brief allow use tinyfiledialog lib to show windows diaglog box
    class TinyDialogBox
    {
    public:
        enum FileDialogType
        {
            SAVE_FILE,
            LOAD_FILE
        };
        enum DialogType
        {
            OK,
            OKCANCEL,
            YESNO
        };
        enum IconType
        {
            INFO,
            WARNING,
            ERROR_ICO,
            QUESTION
        };

        static tinyString const enumDialogTypeToStr(DialogType val)
        {
            switch (val)
            {
                case DialogType::OKCANCEL :
                    return (
                            #if !defined(SFML_SYSTEM_LINUX) && !defined(IS_ENGINE_LINUX)
                            L"okcancel"
                            #else
                            "okcancel"
                            #endif
                            );
                break;
                case DialogType::YESNO :
                    return (
                            #if !defined(SFML_SYSTEM_LINUX) && !defined(IS_ENGINE_LINUX)
                            L"yesno"
                            #else
                            "yesno"
                            #endif
                            );
                break;
                default :
                    return (
                            #if !defined(SFML_SYSTEM_LINUX) && !defined(IS_ENGINE_LINUX)
                            L"ok"
                            #else
                            "ok"
                            #endif
                            );
                break;
            }
        }
        static tinyString const enumIconTypeToStr(IconType val)
        {
            switch (val)
            {
                case IconType::QUESTION :
                    return (
                            #if !defined(SFML_SYSTEM_LINUX) && !defined(IS_ENGINE_LINUX)
                            L"question"
                            #else
                            "question"
                            #endif
                            );
                break;
                case IconType::ERROR_ICO :
                    return (
                            #if !defined(SFML_SYSTEM_LINUX) && !defined(IS_ENGINE_LINUX)
                            L"error"
                            #else
                            "error"
                            #endif
                            );
                break;
                case IconType::WARNING :
                    return (
                            #if !defined(SFML_SYSTEM_LINUX) && !defined(IS_ENGINE_LINUX)
                            L"warning"
                            #else
                            "warning"
                            #endif
                            );
                break;
                default :
                    return (
                            #if !defined(SFML_SYSTEM_LINUX) && !defined(IS_ENGINE_LINUX)
                            L"info"
                            #else
                            "info"
                            #endif
                            );
                break;
            }
        }

        ////////////////////////////////////////////////////////////
        /// \brief show windows dialog
        ///
        /// \param saveFile true to display a file save dialog box, false to display a load file dialog box
        ///
        /// \return @a 1 when user click on @a OK button and @a 0 when @a CANCEL or @a NO button is clicked
        ///
        ////////////////////////////////////////////////////////////
        static int showDialogBox(const std::string& title,
                                 const std::string& msg,
                                 DialogType dialogType,
                                 IconType iconType
                                 )
        {
            tinyString const _dialogType = enumDialogTypeToStr(dialogType);
            tinyString const _iconType = enumIconTypeToStr(iconType);
            return (
                    #if !defined(SFML_SYSTEM_LINUX) && !defined(IS_ENGINE_LINUX)
                    tinyfd_messageBoxW(is::strToWStr(title).c_str(), is::strToWStr(msg).c_str(), _dialogType, _iconType, 1)
                    #else
                    tinyfd_messageBox(title.c_str(), msg.c_str(), _dialogType, _iconType, 1)
                    #endif
                    );
        }

        ////////////////////////////////////////////////////////////
        /// \brief show windows file dialog
        ///
        /// \param saveFile @a true to display a file save dialog box, @a false to display a load file dialog box
        ///
        /// \return file path if the function succeeded and @a "" (empty string) is faliled
        ///
        ////////////////////////////////////////////////////////////
        static std::string showFileDialogBox(FileDialogType type,
                                             const std::string& title,
                                             tinyString filterPatterns[],
                                             const std::string& fileName = "file",
                                             const std::string& msgError = "Unable to access file!",
                                             const std::string& errTitle = "Error"
                                             )
        {
            if (type == FileDialogType::SAVE_FILE)
            {
                TINY_FILE_DIALOGBOX_PATH =
                                            #if !defined(SFML_SYSTEM_LINUX) && !defined(IS_ENGINE_LINUX)
                                            tinyfd_saveFileDialogW(is::strToWStr(title).c_str(), is::strToWStr(fileName).c_str(), 2, filterPatterns, NULL);
                                            #else
                                            tinyfd_saveFileDialog(title.c_str(), fileName.c_str(), 2, filterPatterns, NULL);
                                            #endif
            }
            else
            {
                TINY_FILE_DIALOGBOX_PATH =
                                            #if !defined(SFML_SYSTEM_LINUX) && !defined(IS_ENGINE_LINUX)
                                            tinyfd_openFileDialogW(is::strToWStr(title).c_str(), L"", 2, filterPatterns, NULL, 0);
                                            #else
                                            tinyfd_openFileDialog(title.c_str(), "", 2, filterPatterns, NULL, 0);
                                            #endif
            }
            if (!TINY_FILE_DIALOGBOX_PATH)
            {
                showDialogBox(errTitle, msgError, DialogType::OK, IconType::ERROR_ICO);
            }
            else
            {
                return (
                        #if !defined(SFML_SYSTEM_LINUX) && !defined(IS_ENGINE_LINUX)
                        is::w_chart_tToStr(TINY_FILE_DIALOGBOX_PATH)
                        #else
                        TINY_FILE_DIALOGBOX_PATH
                        #endif
                        );
            }
            return "";
        }

        ////////////////////////////////////////////////////////////
        /// \brief show windows select folder dialog
        ///
        /// \return directory path if the function succeeded and @a "" (empty string) is faliled
        ///
        ////////////////////////////////////////////////////////////
        static std::string showFolderDialogBox(const std::string& title,
                                               const std::string& defaultPath
                                               #if !defined(SFML_SYSTEM_LINUX) && !defined(IS_ENGINE_LINUX)
                                                = "C:\\",
                                               #else
                                                = "/usr/local",
                                               #endif
                                               const std::string& msgError = "Unable to access folder!",
                                               const std::string& errTitle = "Error"
                                               )
        {
            TINY_FILE_DIALOGBOX_PATH =
                                        #if !defined(SFML_SYSTEM_LINUX) && !defined(IS_ENGINE_LINUX)
                                        tinyfd_selectFolderDialogW(is::strToWStr(title).c_str(), is::strToWStr(defaultPath).c_str());
                                        #else
                                        tinyfd_selectFolderDialog(title.c_str(), defaultPath.c_str());
                                        #endif
            if (!TINY_FILE_DIALOGBOX_PATH)
            {
                showDialogBox(errTitle, msgError, DialogType::OK, IconType::ERROR_ICO);
            }
            else
            {
                return (
                        #if !defined(SFML_SYSTEM_LINUX) && !defined(IS_ENGINE_LINUX)
                        is::w_chart_tToStr(TINY_FILE_DIALOGBOX_PATH)
                        #else
                        TINY_FILE_DIALOGBOX_PATH
                        #endif
                        );
            }
            return "";
        }

    };
}
#endif // defined

#endif // TINYDIALOGBOX_H_INCLUDED
