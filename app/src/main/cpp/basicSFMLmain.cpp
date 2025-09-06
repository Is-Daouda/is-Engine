#include "isEngine/core/GameEngine.h"

namespace is
{
bool GameEngine::basicSFMLmain()
{
////////////////////////////////////////////////////////////
//                    WINDOW CREATION
////////////////////////////////////////////////////////////
#if defined(__ANDROID__)
    m_window.create(sf::VideoMode::getDesktopMode(), "");
#else
    m_window.create(sf::VideoMode(is::GameConfig::WINDOW_WIDTH,
                                  is::GameConfig::WINDOW_HEIGHT),
                                  is::GameConfig::GAME_NAME,
                                  is::getWindowStyle());

    // load application icon
    sf::Image iconTex;
    if (!iconTex.loadFromFile(is::GameConfig::GUI_DIR + "icon.png")) return false;
#if !defined (IS_ENGINE_SDL_2) && !defined(IS_ENGINE_VS)
    m_window.setIcon(32, 32, iconTex.getPixelsPtr());
#endif
#endif // defined
    setFPS(m_window, is::GameConfig::FPS); // set frames per second (FPS)
    sf::View m_view(sf::Vector2f(is::GameConfig::VIEW_WIDTH / 2.f, is::GameConfig::VIEW_HEIGHT / 2.f), sf::Vector2f(is::GameConfig::VIEW_WIDTH, is::GameConfig::VIEW_HEIGHT));
    m_window.setView(m_view);

////////////////////////////////////////////////////////////
//                    INITIALIZATION
////////////////////////////////////////////////////////////

    // is::GameConfig::MUSIC_DIR, is::GameConfig::GUI_DIR, is::GameConfig::FONT_DIR
    // Are variables that return the path of resources located in the "assets" folder

    // Load music buffer
    sf::SoundBuffer musicBuffer; // Music is played in the render loop. See line 172
    is::loadSFMLSoundBuffer(musicBuffer, is::GameConfig::MUSIC_DIR + "game_music.wav");
    sf::Sound music(musicBuffer);
    music.play();

    // Load texture
    sf::Texture texture;
    is::loadSFMLTexture(texture, is::GameConfig::GUI_DIR + "icon.png");

    // Create Sprite and set Texture
    sf::Sprite image(texture);
    is::centerSFMLObj(image); // Allows to center the sprite
    image.setPosition(is::GameConfig::VIEW_WIDTH / 2.f, is::GameConfig::VIEW_HEIGHT / 2.f);

    // Load font
    sf::Font font;
    is::loadSFMLFont(font, is::GameConfig::FONT_DIR + "font_system.ttf", 16); // When you develop for the Web you must define
                                                                            // the size that the texts will have with this font
    // Create text and set font
    sf::Text text;
    text.setFont(font);
    text.setString("Hello World !");
    is::centerSFMLObj(text); // Allows to center the text
    text.setPosition(is::GameConfig::VIEW_WIDTH / 2.f, 64.f);

    bool focus = true; // Doesn't work when you're on the web version

////////////////////////////////////////////////////////////
//                    RENDER LOOP                         //
////////////////////////////////////////////////////////////
// This starts the render loop.                           //
// Don't touch unless you know what you're doing.         //
#if !defined(IS_ENGINE_HTML_5)                            //
    while (m_window.isOpen()                              //
#ifdef __SWITCH__                   			          //
        && appletMainLoop()       	                      //
#endif                            						  //
        )                             					  //
#else                                                     //
    EM_ASM(console.log("Start successfully!");, 0);       //
    execMainLoop([&]                                      //
    {                                                     //
    if (emscripten_run_script_int("Module.syncdone") == 1)//
#endif                                                    //
    {                                                     //
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//                       EVENT
////////////////////////////////////////////////////////////
        sf::Vector2i mousePosition(-1, -1); // Allows to get mouse or touch position
                                            // A negative value means that no position has been recorded
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    m_window.close();
                break;

                #if (defined(__ANDROID__) || defined(__SWITCH__))
                case sf::Event::TouchBegan:
                    if (event.touch.finger == 0)
                    {
                        mousePosition.x = is::getCursor(m_window, 0).x;
                        mousePosition.y = is::getCursor(m_window, 0).y;
                        is::vibrate(100);
                    }
                break;
                #else
                case sf::Event::MouseButtonPressed:
                    mousePosition.x = is::getCursor(m_window).x;
                    mousePosition.y = is::getCursor(m_window).y;
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

////////////////////////////////////////////////////////////
//                    UPDATE OBJECTS
////////////////////////////////////////////////////////////

        if (mousePosition.x != -1 && mousePosition.y != -1) image.setPosition(mousePosition.x, mousePosition.y);

////////////////////////////////////////////////////////////
//                     DRAW OBJECTS
////////////////////////////////////////////////////////////
        if (focus)
        {
            m_window.clear(sf::Color::Blue);
            m_window.draw(text);
            m_window.draw(image);
            m_window.display();
        }
    }

////////////////////////////////////////////////////////////
// Don't touch unless you know what you're doing.         //
    #if defined(IS_ENGINE_HTML_5)                         //
    });                                                   //
    #endif                                                //
////////////////////////////////////////////////////////////
    return true;
}
}
