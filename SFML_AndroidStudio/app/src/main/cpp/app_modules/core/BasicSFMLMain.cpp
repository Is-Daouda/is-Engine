#include "GameEngine.h"

bool GameEngine::basicSFMLMain()
{
    #if defined(__ANDROID__)
    m_app.create(sf::VideoMode::getDesktopMode(), "");
    #else
    m_app.create(sf::VideoMode(640, 480), "is::engine Demo", sf::Style::Close);

    // load application icon
    sf::Image iconTex;
    if (!iconTex.loadFromFile(is::GUI_DIR + "icon.png")) return false;
    m_app.setIcon(32, 32, iconTex.getPixelsPtr());
    #endif // defined

    sf::Texture texture;
    if(!texture.loadFromFile(is::GUI_DIR + "icon.png")) return false;

    sf::Sprite image(texture);
    image.setPosition(0, 0);
    image.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

    sf::Music music;
    if (!music.openFromFile(is::SFX_DIR + "speed_up.ogg")) return false;

    music.play();

    m_view = m_app.getDefaultView();

    bool focus = true;

    while (m_app.isOpen())
    {
        sf::Event event;
        while (m_app.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    m_app.close();
                break;

                case sf::Event::Resized:
                    m_view.setSize(event.size.width, event.size.height);
                    m_view.setCenter(event.size.width / 2, event.size.height / 2);
                    m_app.setView(m_view);
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
                    image.setPosition(sf::Mouse::getPosition(m_app).x, sf::Mouse::getPosition(m_app).y);
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
            }
        }

        if (focus)
        {
            m_app.clear(sf::Color::White);
            m_app.draw(image);
            m_app.display();
        }
    }

    return true;
}
