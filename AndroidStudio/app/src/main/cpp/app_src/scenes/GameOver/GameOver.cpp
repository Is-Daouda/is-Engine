#include "GameOver.h"

GameOver::GameOver(sf::RenderWindow &window, sf::View &view, sf::RenderTexture &surface, GameSystemExtended& gameSystemExtended):
    GameDisplay(window, view, surface, gameSystemExtended, sf::Color::White),
    m_oscillation(0.f),
    m_bgX(-64.f),
    m_bgY(-64.f),
    m_TitleX(320.f),
    m_TitleY(110.f),
    m_isStart(true)
{
    srand(time(NULL));
}

GameOver::~GameOver()
{
}

void GameOver::step()
{
    DELTA_TIME = getDeltaTime();

    updateTimeWait(DELTA_TIME);

    const int OP_CONTINUE(0), OP_QUIT(1);

    bool mouseInCollison(false);

    // even loop
    while (m_window.pollEvent(m_event)) controlEventFocusClosing();

    // Camera
    setView();

    // starting mechanism
    if (m_isStart)
    {
        // windows has focus
        if (m_windowIsActive)
        {
            // check collision with sprite
            if (mouseCollision(m_sprPad1) || mouseCollision(m_sprPad2)) mouseInCollison = true;

            if (!m_gameSysExt.keyIsPressed(is::GameConfig::KEY_UP) &&
                !m_gameSysExt.keyIsPressed(is::GameConfig::KEY_DOWN) &&
                !m_gameSysExt.isPressed())
                    m_gameSysExt.m_keyIsPressed = false;

            if (!m_isClose)
            {
                // change option with mouse (touch on Android)
                if (mouseCollision(m_sprPad1) && m_optionIndex != OP_CONTINUE)  setOptionIndex(OP_CONTINUE, true);
                else if (mouseCollision(m_sprPad2) && m_optionIndex != OP_QUIT) setOptionIndex(OP_QUIT, true);

                // avoid the long pressing button effect
                if (!mouseInCollison && m_gameSysExt.isPressed(is::GameSystem::ValidationButton::MOUSE)) m_gameSysExt.m_keyIsPressed = true;

                // change option with keyboard (only for PC)
                if (!m_gameSysExt.m_keyIsPressed && !mouseInCollison)
                {
                    if (m_gameSysExt.keyIsPressed(is::GameConfig::KEY_UP)) setOptionIndex(-1, false);
                    else if (m_gameSysExt.keyIsPressed(is::GameConfig::KEY_DOWN)) setOptionIndex(1, false);
                    if (m_optionIndex < 0) m_optionIndex = OP_QUIT;
                    if (m_optionIndex > OP_QUIT) m_optionIndex = 0;
                }

                // validate option
                if ((m_gameSysExt.isPressed(is::GameSystem::ValidationButton::KEYBOARD) ||
                     (m_gameSysExt.isPressed(is::GameSystem::ValidationButton::MOUSE) && mouseInCollison)) &&
                    (m_waitTime == 0 && !m_gameSysExt.m_keyIsPressed))
                {
                    m_gameSysExt.playSound(m_sndSelectOption);
                    m_sprButtonSelectScale = 1.6f;

                    switch (m_optionIndex)
                    {
                    case OP_CONTINUE:
                        m_gameSysExt.m_launchOption = GameSystemExtended::DisplayOption::GAME_LEVEL;
                        m_gameSysExt.saveData(is::GameConfig::GAME_DATA_FILE); // save data
                        m_isClose = true;
                    break;

                    case OP_QUIT:
                        m_gameSysExt.m_launchOption = GameSystemExtended::DisplayOption::MAIN_MENU;
                        m_isClose = true;
                    break;
                    }
                }
            }
        }
    }

    // change text color
    setTextAnimation(m_txtRestartGame, m_sprPad1, OP_CONTINUE);
    setTextAnimation(m_txtQuitGame, m_sprPad2, OP_QUIT);

    // pad animation
    is::scaleAnimation(DELTA_TIME, m_sprButtonSelectScale, m_sprButtonSelect);

    // title animation
    m_oscillation += is::radToDeg((0.08f * is::VALUE_CONVERSION) * DELTA_TIME);
    is::setSFMLObjX_Y(m_txtGameOver, m_TitleX, m_TitleY + is::lengthDirY(5.f, m_oscillation));

    // background animation
    if (m_bgX < 0.f) m_bgX += (0.5f * is::VALUE_CONVERSION) * DELTA_TIME; else m_bgX = -64.f;
    if (m_bgY < 0.f) m_bgY += (0.5f * is::VALUE_CONVERSION) * DELTA_TIME; else m_bgY = -64.f;
    is::setSFMLObjX_Y(m_sprScreenBG, m_bgX, m_bgY);

    if (m_isClose) m_isRunning = false;
}

void GameOver::draw()
{
    const int OP_CONTINUE(0), OP_QUIT(1);

    m_surface.draw(m_sprScreenBG);
    m_surface.draw(m_txtGameOver);
    if (m_optionIndex != OP_CONTINUE) m_surface.draw(m_sprPad1);
    if (m_optionIndex != OP_QUIT) m_surface.draw(m_sprPad2);
    m_surface.draw(m_sprButtonSelect);
    m_surface.draw(m_txtRestartGame);
    m_surface.draw(m_txtQuitGame);

    ///////////////////////////////////////
    // message box
    drawMsgBox();
    ///////////////////////////////////////
}

bool GameOver::loadResources()
{
    m_gameSysExt.loadConfig(is::GameConfig::CONFIG_FILE);

    if (!GameDisplay::loadParentResources())   return false;

    // load resources
    if (!m_texPad.loadFromFile(is::GameConfig::GUI_DIR + "option_pad.png"))                return false;
    if (!m_texScreenBG.loadFromFile(is::GameConfig::GUI_DIR + "screen_background.png"))    return false;
    if (!m_fontTitle.loadFromFile(is::GameConfig::FONT_DIR + "space_ranger_3d_mp_pv.otf")) return false;

    is::createWText(m_fontTitle, m_txtGameOver, is::lang::game_over[m_gameSysExt.m_gameLanguage], m_TitleX, m_TitleY, sf::Color(0, 0, 0), 56);
    is::centerSFMLObj(m_txtGameOver);

    // create background
    is::createSprite(m_texScreenBG, m_sprScreenBG, sf::IntRect(0, 0, 740, 580), sf::Vector2f(m_bgX, m_bgY), sf::Vector2f(0.f, 0.f), true);

    // create sprites
    float xPos(240.f), yPos(290.f);
    is::createSprite(m_texPad, m_sprPad1, sf::IntRect(0, 0, 160, 32), sf::Vector2f(xPos, yPos), sf::Vector2f(80.f, 16.f));
    is::createSprite(m_texPad, m_sprPad2, sf::IntRect(0, 0, 160, 32), sf::Vector2f(xPos, yPos + 50.f), sf::Vector2f(80.f, 16.f));
    is::createSprite(m_texPad, m_sprButtonSelect, sf::IntRect(160, 0, 160, 32),sf::Vector2f(xPos, yPos) , sf::Vector2f(80.f, 16.f));

    // create texts
    is::createText(m_fontSystem, m_txtRestartGame, is::lang::pad_restart_game[m_gameSysExt.m_gameLanguage], 0.f, 0.f);
    is::createText(m_fontSystem, m_txtQuitGame, is::lang::pad_quit_game[m_gameSysExt.m_gameLanguage], 0.f, 0.f);
    is::centerSFMLObj(m_txtRestartGame);
    is::centerSFMLObj(m_txtQuitGame);
    is::setSFMLObjX_Y(m_txtRestartGame, is::getSFMLObjX(m_sprPad1), is::getSFMLObjY(m_sprPad1) - 6.f);
    is::setSFMLObjX_Y(m_txtQuitGame, is::getSFMLObjX(m_sprPad2), is::getSFMLObjY(m_sprPad2) - 6.f);

    return true;
}
