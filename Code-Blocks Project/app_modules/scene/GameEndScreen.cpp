#include "GameEndScreen.h"

GameEndScreen::GameEndScreen(sf::RenderWindow &window, DisplayOption &m_launchOption, GameSystemExtended& GameSystemExtended):
    GameDisplay(window, m_launchOption, GameSystemExtended, sf::Color::Black),
    m_isStarted(false),
    m_isClosed(false),
    m_isOnButton(false)
{

}

GameEndScreen::~GameEndScreen()
{
}

void GameEndScreen::step()
{
    // delta time
    float DELTA_TIME = getDeltaTime();

    // allow to check collision on sprite
    bool mouseInCollison(false);

    // event loop
    while (m_app.pollEvent(m_event)) controlEventFocusClosing();

    // view
    m_view.setCenter(m_viewX, m_viewY);
    m_app.setView(m_view);

    auto setButtonSelectScale = [this]()
    {
        m_sprButtonSelectScale = 1.6f;
    };

    // launch scene
    if (m_isStarted)
    {
        // if application have focus
        if (m_appIsActive)
        {
            // allow to activate button
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !m_gameSysExt.isPressed()) m_gameSysExt.m_keyIsPressed = false;

            if (!m_isClosed)
            {
                // check collision on button sprite
                if (is::mouseCollision(m_app, m_sprButtonSelect)) mouseInCollison = true;
                else m_isOnButton = false;

                // allow to activate button
                if (!mouseInCollison && m_gameSysExt.isPressed()) m_gameSysExt.m_keyIsPressed = true;

                auto tempFnct = [this, &setButtonSelectScale](int index)
                {
                    ////////////////////////////////////////////////////////////
                    // PC version code
                    #if !defined(__ANDROID__)
                    m_gameSysExt.playSound(m_sndSwitch);
                    #endif
                    ////////////////////////////////////////////////////////////
                    setButtonSelectScale();
                    m_optionIndex = index;
                    m_isOnButton = true;
                };

                // make switch animation if mouse overflown the button
                if (!m_isOnButton)
                {
                    if (is::mouseCollision(m_app, m_sprButtonSelect)) tempFnct(0);
                }

                // validate option
                if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || (m_gameSysExt.isPressed() && mouseInCollison)) &&
                    (m_waitTime == 0 && !m_gameSysExt.m_keyIsPressed))
                {
                    m_gameSysExt.playSound(m_sndSelectOption);

                    ////////////////////////////////////////////////////////////
                    // Android version code
                    #if defined(__ANDROID__)
                    m_gameSysExt.useVibrate(m_vibrateTimeDuration);
                    #endif
                    ////////////////////////////////////////////////////////////

                    setButtonSelectScale();
                    m_launchOption = is::GameDisplay::MAIN_MENU;
                    m_isClosed = true;
                }
            }
        }
    }

    // button animation
    is::scaleAnimation(DELTA_TIME, m_sprButtonSelectScale, m_sprButtonSelect);

    // transition effect at beginning
    if (!m_isStarted)
    {
        if (m_alphaRec > 5) m_alphaRec -= static_cast<int>((5.f * is::VALUE_CONVERSION) * DELTA_TIME);
        else
        {
            m_alphaRec = 0;
            m_isStarted = true;
        }
        is::setSFMLRecColor(m_recTransition, sf::Color(0, 0, 0, m_alphaRec));
    }

    // transition effect at ending
    if (m_isClosed)
    {
       if (m_alphaRec < 250) m_alphaRec += static_cast<int>((5.f * is::VALUE_CONVERSION) * DELTA_TIME);
       else
       {
            m_alphaRec = 255;
            m_isRunning = false; // quit the scene main loop
       }
       is::setSFMLRecColor(m_recTransition, sf::Color(0, 0, 0, m_alphaRec));
    }
}

void GameEndScreen::draw()
{
    m_app.draw(m_sprBg);
    m_app.draw(m_txtTitle);
    m_app.draw(m_sprButtonSelect);
    m_app.draw(m_txtQuitScreen);
    m_app.draw(m_recTransition);
}

bool GameEndScreen::loadResources()
{
    m_view.setCenter(m_viewX, m_viewY);
    m_app.setView(m_view);

    // load parent resources
    if (!is::GameDisplay::loadParentResources()) return false;

    // load texture
    if (!m_texBg.loadFromFile(is::GUI_DIR + "menu_bg.png")) return false;
    if (!m_texButton.loadFromFile(is::GUI_DIR + "button.png")) return false;

    // create stretched background
    is::createSprite(m_texBg, m_sprBg, sf::IntRect(0, 0, 640, 480), sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), true);

    // create button sprite
    float BT_X(230.f);
    is::createSprite(m_texButton, m_sprButtonSelect, sf::IntRect(0, 32, 160, 32), sf::Vector2f(BT_X, 376.f), sf::Vector2f(80.f, 16.f));

    // create text on button
    is::createText(m_font1, m_txtQuitScreen, "Main Menu", 0.f, 0.f, sf::Color::White, 25);
    is::centerSFMLObj(m_txtQuitScreen);
    is::setSFMLObjX_Y(m_txtQuitScreen, is::getSFMLObjX(m_sprButtonSelect), is::getSFMLObjY(m_sprButtonSelect) - 8.f);

    // create game end text
    is::createText(m_font2, m_txtTitle, "\t  Congratulation !!!\nYou finished the Game !", 0.f, 0.f, sf::Color::White, 32);
    is::centerSFMLObj(m_txtTitle);
    is::setSFMLObjX_Y(m_txtTitle, 320.f, 64.f);

    return true; // resource loaded successfully
}
