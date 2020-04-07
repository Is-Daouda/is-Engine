#include "isEngine/core/GameEngine.h"

bool GameEngine::basicSFMLmain()
{
    #if defined(__ANDROID__)
    m_window.create(sf::VideoMode::getDesktopMode(), "");
    #else
    m_window.create(sf::VideoMode(is::GameConfig::WINDOW_WIDTH,
                                  is::GameConfig::WINDOW_HEIGHT),
                                  is::GameConfig::GAME_NAME,
                                  sf::Style::Close);

    // load application icon
    sf::Image iconTex;
    if (!iconTex.loadFromFile(is::GameConfig::GUI_DIR + "icon.png")) return false;
    m_window.setIcon(32, 32, iconTex.getPixelsPtr());
    #endif // defined

    sf::View m_view(m_window.getDefaultView());

    sf::Texture texture;
    if(!texture.loadFromFile(is::GameConfig::GUI_DIR + "icon.png")) return false;

    sf::Sprite image(texture);
    image.setPosition(m_view.getCenter().x / 2.f, m_view.getCenter().y / 2.f);
    image.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

    sf::Music music;
    if (!music.openFromFile(is::GameConfig::MUSIC_DIR + "world_1_music.ogg")) return false;
    music.play();

    bool focus = true;

    while (m_window.isOpen())
    {
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
                        image.setPosition(event.touch.x, event.touch.y);
                        is::vibrate(sf::milliseconds(100));
                        is::showLog("Vibrate");
                    }
                break;
                #else
                case sf::Event::MouseButtonPressed:
                    image.setPosition(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y);
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

        if (focus)
        {
            m_window.clear(sf::Color::White);
            m_window.draw(image);
            m_window.display();
        }
    }

    return true;
}
