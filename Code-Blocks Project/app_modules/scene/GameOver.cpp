#include "GameOver.h"


GameOver::GameOver(sf::RenderWindow &window, DisplayOption &m_launchOption, GameSystemExtended& GameSystemExtended):
    GameDisplay(window, m_launchOption, GameSystemExtended, sf::Color::Black),
    m_isStarted(false),
    m_isClosed(false)
{
}

GameOver::~GameOver()
{
}

void GameOver::step()
{
    // delta time
    float DELTA_TIME = getDeltaTime();

    // wait time when cancel option
    if (m_waitTime > 0) m_waitTime -= is::getMSecond<int>(DELTA_TIME);
    else m_waitTime = 0;

    const int OP_CONTINUE(0), OP_QUIT(1);

    // check collision on sprite with mouse
    bool mouseInCollison(false);

    // event loop
    while (m_app.pollEvent(m_event)) controlEventFocusClosing();

    // view
    m_view.setCenter(m_viewX, m_viewY);
    m_app.setView(m_view);

    auto setButtonSelectScale = [this](float x = 1.4f)
    {
        m_sprButtonSelectScale = x;
    };

    // launch the scene
    if (m_isStarted)
    {
        // application has focus
        if (m_appIsActive)
        {
            // check collision on button sprites
            for (int i(0); i < 2; i++)
            {
                if (is::mouseCollision(m_app, m_sprButton[i])) mouseInCollison = true;
            }

            // allow to activate button
            if ((!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                || (!m_gameSysExt.isPressed()))
                m_gameSysExt.m_keyIsPressed = false;

            if (!m_isClosed)
            {
                auto setOptionIndex = [this, &setButtonSelectScale](int m_optionIndexValue)
                {
                    ////////////////////////////////////////////////////////////
                    #if defined(__ANDROID__)
                    m_gameSysExt.useVibrate(m_vibrateTimeDuration);
                    #else
                    m_gameSysExt.playSound(m_sndSwitch);
                    #endif
                    ////////////////////////////////////////////////////////////
                    setButtonSelectScale();
                    m_optionIndex = m_optionIndexValue;
                };

                // switch with mouse
                if (is::mouseCollision(m_app, m_sprButton[0]) && m_optionIndex != OP_CONTINUE)  setOptionIndex(OP_CONTINUE);
                else if (is::mouseCollision(m_app, m_sprButton[1]) && m_optionIndex != OP_QUIT) setOptionIndex(OP_QUIT);

                // avoid press key loop
                if (!mouseInCollison && m_gameSysExt.isPressed()) m_gameSysExt.m_keyIsPressed = true;

                ////////////////////////////////////////////////////////////
                // PC version code
                #if !defined(__ANDROID__)
                // switch button with keyboard. This code will work until mouse isn't on button
                if (!mouseInCollison)
                {
                    auto setChangeOptionIndex = [this, &setButtonSelectScale](short int value)
                    {
                        m_optionIndex += value;
                        setButtonSelectScale();
                        m_gameSysExt.playSound(m_sndSwitch);
                        m_gameSysExt.m_keyIsPressed = true;
                    };

                    if (!m_gameSysExt.m_keyIsPressed)
                    {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_optionIndex == OP_QUIT) setChangeOptionIndex(-1);
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_optionIndex == OP_CONTINUE) setChangeOptionIndex(+1);
                    }
                }
                #endif
                ////////////////////////////////////////////////////////////

                // validate options
                if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || (m_gameSysExt.isPressed() && mouseInCollison)) &&
                    (m_waitTime == 0 && !m_gameSysExt.m_keyIsPressed))
                {
                    m_gameSysExt.playSound(m_sndSelectOption);

                    switch (m_optionIndex)
                    {
                    // restart current level
                    case OP_CONTINUE:
                        m_launchOption = is::GameDisplay::DisplayOption::GAME_LEVEL;
                        setButtonSelectScale(1.6f);
                        m_gameSysExt.saveData(is::DATA_FILE); // save data
                        m_isClosed = true;
                    break;

                    // return to main menu
                    case OP_QUIT:
                        setButtonSelectScale(1.6f);
                        m_launchOption = is::GameDisplay::MAIN_MENU;
                        m_isClosed = true;
                    break;
                    }
                }
            }
        }
    }

    // control the limit of option
    if (m_optionIndex < OP_CONTINUE) m_optionIndex = OP_QUIT;
    if (m_optionIndex > OP_QUIT) m_optionIndex = OP_CONTINUE;

    // change text color animation according to button selected
    setTextAnimation(m_txtRestartGame, m_sprButton[0], OP_CONTINUE);
    setTextAnimation(m_txtQuitGame, m_sprButton[1], OP_QUIT);

    // animation of button
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

void GameOver::draw()
{
    m_app.draw(m_sprBg);
    m_app.draw(m_txtTitle);
    for (int i(0); i < 2; i++) m_app.draw(m_sprButton[i]);
    m_app.draw(m_sprButtonSelect);
    m_app.draw(m_txtRestartGame);
    m_app.draw(m_txtQuitGame);

    // transition rectangle
    m_app.draw(m_recTransition);
}

bool GameOver::loadResources()
{
    // load parent class resource
    if (!GameDisplay::loadParentResources()) return false;

    // load texture
    if (!m_texBg.loadFromFile(is::GUI_DIR + "menu_bg.png")) return false;
    if (!m_texButton.loadFromFile(is::GUI_DIR + "button.png")) return false;

    float const BT_X(250.f),
                BT_Y(240.f);

    // create stretched background
    is::createSprite(m_texBg, m_sprBg, sf::IntRect(0, 0, 640, 480), sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), true);

    // create sprite
    for (int i(0); i < 2; i++)
        is::createSprite(m_texButton, m_sprButton[i], sf::IntRect(0, 0, 160, 32), sf::Vector2f(BT_X, BT_Y + (48.f * i)), sf::Vector2f(80.f, 16.f));
    is::createSprite(m_texButton, m_sprButtonSelect, sf::IntRect(0, 32, 160, 32),sf::Vector2f(0.f, 0.f) , sf::Vector2f(80.f, 16.f));
    is::centerSFMLObj(m_sprButtonSelect);
    is::setSFMLObjX_Y(m_sprButtonSelect, is::getSFMLObjX(m_sprButton[0]), is::getSFMLObjY(m_sprButton[0]));

    // create text
    is::createText(m_font1, m_txtRestartGame, "Restart Game", 0.f, 0.f);
    is::createText(m_font1, m_txtQuitGame, "Quit Game", 0.f, 0.f);
    is::centerSFMLObj(m_txtRestartGame);
    is::centerSFMLObj(m_txtQuitGame);
    is::setSFMLObjX_Y(m_txtRestartGame, is::getSFMLObjX(m_sprButton[0]), is::getSFMLObjY(m_sprButton[0]) - 8.f);
    is::setSFMLObjX_Y(m_txtQuitGame, is::getSFMLObjX(m_sprButton[1]), is::getSFMLObjY(m_sprButton[1]) - 8.f);

    // create game over text
    is::createText(m_font2, m_txtTitle, "Game Over", 0.f, 0.f, sf::Color::White, 48);
    is::centerSFMLObj(m_txtTitle);
    is::setSFMLObjX_Y(m_txtTitle, 320.f, 64.f);

    return true; // resource loaded successfully
}
