#ifndef GAMECONFIG_H_INCLUDED
#define GAMECONFIG_H_INCLUDED

#include "ExtraConfig.h"

namespace is
{
////////////////////////////////////////////////////////////
/// \brief Allows to manipulate the different scenes and options
///
////////////////////////////////////////////////////////////
enum DisplayOption
{
    HELLO_SCENE,   ///< Access the hello scene

    // example
    // YOUR_SCENE, ///< Access to your scene
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

	static const DisplayOption LAUNCH_OPTION = DisplayOption::HELLO_SCENE; ///< Represents the first scene to be launched

	/// Represent the key which validates the options with the Mouse
    static sf::Mouse::Button KEY_VALIDATION_MOUSE    = sf::Mouse::Left;

    /// Represent the key which validates the options with the Keyboard
    static sf::Keyboard::Key KEY_VALIDATION_KEYBOARD = sf::Keyboard::Return;

    /// Represent the key which cancel the options with the Keyboard
    static sf::Keyboard::Key KEY_CANCEL = sf::Keyboard::Escape;;

    /// Represents the button A key
    static sf::Keyboard::Key KEY_A      = sf::Keyboard::W;

    /// Represents the button B key
    static sf::Keyboard::Key KEY_B      = sf::Keyboard::X;

    /// Represents the Left directional key
    static sf::Keyboard::Key KEY_LEFT   = sf::Keyboard::Left;

    /// Represents the Right directional key
    static sf::Keyboard::Key KEY_RIGHT  = sf::Keyboard::Right;

    /// Represents the Up directional key
    static sf::Keyboard::Key KEY_UP     = sf::Keyboard::Up;

    /// Represents the Down directional key
    static sf::Keyboard::Key KEY_DOWN   = sf::Keyboard::Down;

    ////////////////////////////////////////////////////////////
    /// Default values that SFML texts will take when they are created
    ////////////////////////////////////////////////////////////
    static const int        DEFAULT_SFML_TEXT_SIZE                 = 20;
    static const sf::Color &DEFAULT_SFML_TEXT_COLOR                = sf::Color::Blue;
    static const sf::Color &DEFAULT_SFML_SELECTED_TEXT_COLOR       = sf::Color::White;
    static const int        DEFAULT_MSG_BOX_TEXT_SIZE              = 20;
    static const int        DEFAULT_MSG_BOX_BUTTON_TEXT_SIZE       = 18;
    static const sf::Color &DEFAULT_MSG_BOX_TEXT_COLOR             = sf::Color::White;
    static const sf::Color &DEFAULT_MSG_BOX_SELECTED_TEXT_COLOR    = sf::Color::Red;
    static const int        DEFAULT_RPG_DIALOG_TEXT_SIZE           = 16;
    static const int        DEFAULT_RPG_DIALOG_BUTTON_TEXT_SIZE    = 13;
    static const sf::Color &DEFAULT_RPG_DIALOG_TEXT_COLOR          = sf::Color::White;
    static const sf::Color &DEFAULT_RPG_DIALOG_SELECTED_TEXT_COLOR = sf::Color::Blue;
    static const sf::Color &DEFAULT_BUTTON_TEXT_COLOR              = sf::Color::White;

    static const std::string MAJOR = "1"; ///< Game major version
    static const std::string MINOR = "0"; ///< Game minor version
    inline std::string getGameVersion() {return MAJOR + "." + MINOR;} ///< return version of the game

    static std::string const GAME_NAME     = "Hello"; ///< Windows title name
    static std::string const GAME_AUTHOR   = "Author";

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

    // parent directory
	static std::string const ASSETS_DIR =
	#if !defined(__ANDROID__)
        #if defined(IS_ENGINE_QT)
                                           (fileExist("assets/assets.dat") ? "" : "../../") +
        #endif
                                           std::string("assets/");
    #elif defined(IS_ENGINE_HTML_5)
                                           "/assets/"
	#else
                                           "";
	#endif // defined
    static std::string const GUI_DIR        = ASSETS_DIR + "image/gui/";     ///< Path to resource files that serve as GUI
    static std::string const FONT_DIR       = ASSETS_DIR + "font/";          ///< Path to resource files that serve as Font
    static std::string const SPRITES_DIR    = ASSETS_DIR + "image/sprites/"; ///< Path to resource files that serve as Sprite
    static std::string const TILES_DIR      = ASSETS_DIR + "image/tiles/";   ///< Path to resource files that serve as tile and background
    static std::string const SFX_DIR        = ASSETS_DIR + "sound/sfx/";     ///< Path to resource files that serve as SFX
    static std::string const MUSIC_DIR      = ASSETS_DIR + "sound/music/";   ///< Path to resource files that serve as Music
    static std::string const TMX_RSC_DIR    = ASSETS_DIR + "maps/";          ///< Path to TMX resource files

    #if defined(__ANDROID__)
    ////////////////////////////////////////////////////////////
    /// \brief game package name
    /// Represents the place where your data will be saved on Android
    /// Replace this with your real package name (e.g. com.StudioName.GameName)
    /// You must apply this name for the applicationId in the build.gradle file
    ////////////////////////////////////////////////////////////
    static std::string const PACKAGE_NAME   = "com.author.isengine";
    #endif // defined

    // parent directory
    static std::string DATA_PARENT_DIR =
                                        #if defined(__ANDROID__)
                                        "/data/data/" + PACKAGE_NAME + "/"
                                        #elif defined(IS_ENGINE_HTML_5)
                                        "/save/"
                                        #else
                                        "save/"
                                        #endif
                                        ;
    ///< Path to save game progress file
    static std::string const GAME_DATA_FILE = DATA_PARENT_DIR + "game_data.bin";

    ///< Path to save game menu configuration file
    static std::string const CONFIG_FILE    = DATA_PARENT_DIR + "game_config.dat";

    ///< Path to save game pad configuration file
    static std::string const GAME_PAD_FILE  = DATA_PARENT_DIR + "game_pad_config.dat";
}
}

#endif // GAMECONFIG_H_INCLUDED
