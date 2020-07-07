#ifndef GAMECONFIG_H_INCLUDED
#define GAMECONFIG_H_INCLUDED

#include <string>

// uncomment to enable showLog function
#define IS_ENGINE_USE_SHOWLOG ///< Allows to show text in console

// uncomment to enable SDM function
#define IS_ENGINE_USE_SDM ///< Allows to use Step and Draw Manager

// uncomment to enable SGM function
#define IS_ENGINE_USE_GSM ///< Allows to use Game Sound Manager

#if defined(__ANDROID__)
// uncomment this line to use Admob
// #define IS_ENGINE_USE_ADMOB

// if you enable Admob you need to uncomment line in
// CMakeLists and Gradle files to link the Firebase library on project
#endif // defined
////////////////////////////////////////////////////////////

namespace is
{
////////////////////////////////////////////////////////////
/// \brief Allows to manipulate the different scenes and options
///
////////////////////////////////////////////////////////////
enum DisplayOption
{
    RESUME_GAME = 0,         ///< When player close pause menu
    GAME_OPTION_RESTART = 1, ///< When player restart the level with restart option
    QUIT_GAME = 2,           ///< When player use quit option
    INTRO,                   ///< Access the introduction scene
    RESTART_LEVEL,           ///< When player loses a life
    NEXT_LEVEL,              ///< Access the next level scene
    MAIN_MENU,               ///< Access the main menu scene
    GAME_LEVEL,              ///< Access the game level scene
    GAME_OVER,               ///< Access the game over scene
    GAME_END_SCREEN          ///< Access the game end scene
};

////////////////////////////////////////////////////////////
/// \brief Allows to manipulate the window style
///
////////////////////////////////////////////////////////////
enum WindowStyle
{
    NONE,       ///< No decoration at all
    TITLEBAR,   ///< The window has a titlebar
    RESIZE,     ///< The window can be resized and has a maximize button
    CLOSE,      ///< The window has a close button
    FULLSCREEN, ///< The window is shown in fullscreen mode
    DEFAULT     ///< The default style, which is a shortcut for Titlebar | Resize | Close
};

////////////////////////////////////////////////////////////
/// Allows to define the general parameters of the game and
/// that the ad manager (Admob)
////////////////////////////////////////////////////////////
namespace GameConfig
{
    static const unsigned int WINDOW_WIDTH   = 640; ///< Window width work only for PC Platform
    static const unsigned int WINDOW_HEIGHT  = 480; ///< Window height work only for PC Platform
    static const float        VIEW_WIDTH     = 640.f;
    static const float        VIEW_HEIGHT    = 480.f;
    static const float        FPS            = 60.f; ///< Game FPS
    static const is::WindowStyle WINDOW_SETTINGS = WindowStyle::DEFAULT; ///< Window style

	static const DisplayOption LAUNCH_OPTION = DisplayOption::INTRO; ///< Represents the first scene to be launched

    static const sf::Mouse::Button KEY_VALIDATION_MOUSE    = sf::Mouse::Left;      ///< Represent the key which validates the options with the Mouse
    static const sf::Keyboard::Key KEY_VALIDATION_KEYBOARD = sf::Keyboard::Return; ///< Represent the key which validates the options with the Keyboard
    static const sf::Keyboard::Key KEY_CANCEL              = sf::Keyboard::Escape; ///< Represent the key which cancel the options with the Keyboard

    static const sf::Keyboard::Key KEY_A = sf::Keyboard::W;         ///< Represents the button A key
    static const sf::Keyboard::Key KEY_B = sf::Keyboard::X;         ///< Represents the button B key
    static const sf::Keyboard::Key KEY_LEFT = sf::Keyboard::Left;   ///< Represents the Left directional key
    static const sf::Keyboard::Key KEY_RIGHT = sf::Keyboard::Right; ///< Represents the Right directional key
    static const sf::Keyboard::Key KEY_UP = sf::Keyboard::Up;       ///< Represents the Up directional key
    static const sf::Keyboard::Key KEY_DOWN = sf::Keyboard::Down;   ///< Represents the Down directional key

    static const std::wstring MAJOR = L"2"; ///< Game major version
    static const std::wstring MINOR = L"1"; ///< Game minor version
    inline std::wstring getGameVersion() {return MAJOR + L"." + MINOR;} ///< return version of the game

    static std::wstring const GAME_NAME     = L"is::Engine DEMO"; ///< Windows title name
    static std::wstring const GAME_AUTHOR   = L"Is Daouda";

    #if defined(IS_ENGINE_USE_ADMOB)
    ////////////////////////////////////////////////////////////
    /// Allows to define the parameters of the ad manager (Admob)
    ////////////////////////////////////////////////////////////
    namespace AdmobConfig
    {
        // The AdMob components IDs.
        static const char* kAdMobAppID          = "ca-app-pub-3940256099942544~3347511713";
        static const char* kBannerAdUnit        = "ca-app-pub-3940256099942544/6300978111";
        static const char* kRewardedVideoAdUnit = "ca-app-pub-3940256099942544/2888167318";

        // Standard mobile banner size is 320x50.
        static const int kBannerWidth = 640;
        static const int kBannerHeight = 48;

        // Sample birthday value to use in making the request.
        static const int kBirthdayDay = 1;
        static const int kBirthdayMonth = 1;
        static const int kBirthdayYear = 1990;

        // Sample keywords to use in making the request.
        static const char* kKeywords[] = {"Football", "Game", "Music", "Applications"};
    }
    #endif // defined

    static std::string const GUI_DIR        = "data/image/gui/";     ///< Path to resource files that serve as GUI
    static std::string const FONT_DIR       = "data/font/";          ///< Path to resource files that serve as Font
    static std::string const SPRITES_DIR    = "data/image/sprites/"; ///< Path to resource files that serve as Sprite
    static std::string const TILES_DIR      = "data/image/tiles/";   ///< Path to resource files that serve as tile and background
    static std::string const SFX_DIR        = "data/sound/sfx/";     ///< Path to resource files that serve as SFX
    static std::string const MUSIC_DIR      = "data/sound/music/";   ///< Path to resource files that serve as Music

    #if defined(__ANDROID__)
    ////////////////////////////////////////////////////////////
    /// \brief game package name
    /// Represents the place where your data will be saved on Android
    /// Replace this with your real package name (e.g. com.StudioName.GameName)
    /// You must apply this name for the applicationId in the build.gradle file
    ////////////////////////////////////////////////////////////
    static std::string const PACKAGE_NAME   = "com.isdaouda.isenginedemo";

    // file path
    static std::string const GAME_DATA_FILE = "/data/data/" + PACKAGE_NAME + "/game_data.bin";       ///< Path to save game progress file based on package name
    static std::string const CONFIG_FILE    = "/data/data/" + PACKAGE_NAME + "/game_config.dat";     ///< Path to save game menu configuration file based on package name
    static std::string const GAME_PAD_FILE  = "/data/data/" + PACKAGE_NAME + "/game_pad_config.dat"; ///< Path to save game pad configuration file based on package name
    #else
    static std::string GAME_DATA_FILE       = "save/game_data.bin";       ///< Path to save game progress file
    static std::string const CONFIG_FILE    = "save/game_config.dat";     ///< Path to save game menu configuration
    static std::string const GAME_PAD_FILE  = "save/game_pad_config.dat"; ///< Path to save game pad configuration
    #endif // defined

}
}

#endif // GAMECONFIG_H_INCLUDED
