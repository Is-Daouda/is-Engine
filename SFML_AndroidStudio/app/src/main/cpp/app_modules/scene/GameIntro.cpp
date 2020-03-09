#include "GameIntro.h"

GameIntro::GameIntro(sf::RenderWindow &window, DisplayOption &m_launchOption, GameSystemExtended &gameSysExt):
    GameDisplay(window, m_launchOption, gameSysExt, sf::Color::Black),
    m_timeEv(0),
    m_introStep(0),
    m_imgAlpha(0),
    m_blind(false)
{
}

void GameIntro::step()
{
    // DELTA_TIME
    float DELTA_TIME = getDeltaTime();

    // event loop
    while (m_app.pollEvent(m_event)) controlEventFocusClosing();

    // view
    m_view.setCenter(m_viewX, m_viewY);
    m_app.setView(m_view);

    if (m_appIsActive)
    {
        // wait time
        if (m_waitTime > 0) m_waitTime -= static_cast<int>(is::VALUE_CONVERSION * DELTA_TIME);
        else m_waitTime = 0;

        // intro blind animation step
        if (m_introStep == 0)
        {
            if (!m_blind)
            {
                if (m_imgAlpha < 250) m_imgAlpha += static_cast<int>((4.f * is::VALUE_CONVERSION) * DELTA_TIME);
                else
                {
                    m_imgAlpha = 0;
                    //////////////////////////////////////////////////////////
                    // make vibrate on android
                    #if defined(__ANDROID__)
                    m_gameSysExt.useVibrate(m_vibrateTimeDuration);
                    #endif
                    //////////////////////////////////////////////////////////
                    is::setSFMLTextAlpha(m_txtTitle, m_imgAlpha);
                    m_blind = true;
                }
            }
            else
            {
                if (m_imgAlpha < 240) m_imgAlpha += static_cast<int>((10.f * is::VALUE_CONVERSION) * DELTA_TIME);
                else m_imgAlpha = 255;
                is::setSFMLTextAlpha(m_txtTitle, m_imgAlpha);
            }

            // fade in transition start
            if (m_alphaRec > 5) m_alphaRec -= static_cast<int>((4.f * is::VALUE_CONVERSION) * DELTA_TIME);
            else
            {
                m_alphaRec = 0;
                if (m_timeEv < 50) m_timeEv += static_cast<int>(is::VALUE_CONVERSION * DELTA_TIME);
                else m_introStep++;
            }
        }
        else if (m_introStep == 1)
        {
            // fade in transition end
            if (m_alphaRec < 250) m_alphaRec += static_cast<int>((4.f * is::VALUE_CONVERSION) * DELTA_TIME);
            else
            {
                if (m_timeEv < 55)
                {
                    m_alphaRec = 255;
                    m_timeEv += static_cast<int>(is::VALUE_CONVERSION * DELTA_TIME);
                }
                else
                {
                    m_isRunning = false;  // quit the scene loop in GameEngine source
                    m_launchOption = is::GameDisplay::MAIN_MENU;  // go to main menu
                    m_introStep++;
                }
            }
        }
        is::setSFMLRecColor(m_recTransition, sf::Color(0, 0, 0, m_alphaRec));
    }
}

void GameIntro::draw()
{
    // draw demo text
    m_app.draw(m_txtTitle);

    // transition rectangle
    m_app.draw(m_recTransition);
}

bool GameIntro::loadResources()
{
    // load parent resource
    if (!GameDisplay::loadParentResources()) return false;

    // create text
    is::createText(m_font2, m_txtTitle, "is::Engine Demo", 0.f, 0.f, 24);
    is::centerSFMLObj(m_txtTitle);
    is::setSFMLObjX_Y(m_txtTitle, m_viewX, m_viewY);

    return true; // resource loaded successfully
}
