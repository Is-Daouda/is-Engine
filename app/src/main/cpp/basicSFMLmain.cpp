#include "isEngine/core/GameEngine.h"

namespace is
{
bool GameEngine::basicSFMLmain()
{
#if defined(__ANDROID__)
    m_window.create(sf::VideoMode::getDesktopMode(), "");
#else
    #if !defined(IS_ENGINE_HTML_5)
    m_window.create(sf::VideoMode(is::GameConfig::WINDOW_WIDTH,
                                  is::GameConfig::WINDOW_HEIGHT),
                                  is::GameConfig::GAME_NAME,
                                  is::getWindowStyle());

    // load application icon
    sf::Image iconTex;
    if (!iconTex.loadFromFile(is::GameConfig::GUI_DIR + "icon.png")) return false;
    m_window.setIcon(32, 32, iconTex.getPixelsPtr());
    #else // using the SFML library (Web development)
    m_window = sf::RenderWindow(is::GameConfig::WINDOW_WIDTH, is::GameConfig::WINDOW_HEIGHT, is::GameConfig::GAME_NAME);
    #endif // defined
#endif // defined

    sf::View m_view(m_window.getDefaultView());

    // is::GameConfig::MUSIC_DIR, is::GameConfig::GUI_DIR, is::GameConfig::FONT_DIR
    // Are variables that return the path of resources located in the "assets" folder

    // Load music
    sf::Music music; // Music is played in the render loop. See line 129
    is::loadSFMLMusic(music, is::GameConfig::MUSIC_DIR + "game_music.ogg");

    // Load texture
    sf::Texture texture;
    is::loadSFMLTexture(texture, is::GameConfig::GUI_DIR + "icon.png");

    // Create Sprite and set Texture
    sf::Sprite image(texture);
    is::centerSFMLObj(image); // Allows to center the sprite
    image.setPosition(is::GameConfig::VIEW_WIDTH / 2.f, is::GameConfig::VIEW_HEIGHT / 2.f);

    // Load font
    sf::Font font;
    is::loadSFMLFont(font, is::GameConfig::FONT_DIR + "sansation.ttf", 16); // When you develop for the Web you must define
                                                                            // the size that the texts will have with this font
    // Create text and set font
    sf::Text text;
    text.setFont(font);
    text.setString("Hello World !");
    is::centerSFMLObj(text); // Allows to center the text
    text.setPosition(is::GameConfig::VIEW_WIDTH / 2.f, 64.f);

    bool focus = true; // Doesn't work when you're on the web version

    ////////////////////////////////////////////////////////////
    // This starts the render loop.
    // Don't touch unless you know what you're doing.
    #if !defined(IS_ENGINE_HTML_5)
    while (m_window.isOpen())
    #else
    m_window.ExecuteMainLoop([&]
    #endif // defined
    ////////////////////////////////////////////////////////////
    {
        sf::Vector2i mousePosition(-1, -1); // Allows to get mouse or touch position
                                            // A negative value means that no position has been recorded

        #if !defined(IS_ENGINE_HTML_5) // using the SFML library
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    m_window.close();
                break;

                case sf::Event::Resized:
                    m_view.setSize(event.size.width, event.size.height);
                    m_view.setCenter(event.size.width / 2, event.size.height / 2);
                    m_window.setView(m_view);
                break;

                #if defined(__ANDROID__)
                case sf::Event::TouchBegan:
                    if (event.touch.finger == 0)
                    {
                        mousePosition.x = event.touch.x;
                        mousePosition.y = event.touch.y;
                        is::vibrate(100);
                    }
                break;
                #else
                case sf::Event::MouseButtonPressed:
                    mousePosition.x = sf::Mouse::getPosition(m_window).x;
                    mousePosition.y = sf::Mouse::getPosition(m_window).y;
                break;
                #endif // defined

                case sf::Event::LostFocus:
                focus = false;                    //don't draw, if the window is not shown
                is::showLog("LOST FOCUS!");
                break;

                case sf::Event::GainedFocus:
                focus = true;                    //draw if the window is shown
                is::showLog("GAINED FOCUS!");
                break;

                default: break;
            }
        }
        #else                  // using the SMK library (Web development)
        m_window.PoolEvents(); // Allows to update events

        // Get position on cursor released.
        if (m_window.input().IsCursorReleased())
        {
            mousePosition = sf::Mouse::getPosition(m_window);

            // Vibrate on cursor released
            // Works if and only if the platform supports the vibrator (Smart phone)
            is::vibrate(100);
        }
        #endif // defined

        // With the SMK library, musics can only be played if they are in the render loop
        if (is::checkSFMLSndState(music, is::SFMLSndStatus::Stopped)) music.play();

        // This function allows the use Keyboard and Mouse inputs
        // Here it is used to stop the music
        if (m_gameSysExt.keyIsPressed(is::GameConfig::KEY_VALIDATION_KEYBOARD) ||
            m_gameSysExt.keyIsPressed(is::GameConfig::KEY_VALIDATION_MOUSE))
        {
            if (is::checkSFMLSndState(music, is::SFMLSndStatus::Playing)) music.stop();
        }

        if (mousePosition.x != -1 && mousePosition.y != -1) image.setPosition(mousePosition.x, mousePosition.y);
        if (focus)
        {
            m_window.clear(sf::Color::Blue);
            m_window.draw(text);
            m_window.draw(image);
            m_window.display();
        }
    }
    #if defined(IS_ENGINE_HTML_5)
    );
    #endif // defined

    return true;
}
}
