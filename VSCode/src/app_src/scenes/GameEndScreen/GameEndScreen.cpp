#include "GameEndScreen.h"

GameEndScreen::GameEndScreen(sf::RenderWindow &window, sf::View &view, sf::RenderTexture &surface, GameSystemExtended& GameSystemExtended):
    GameDisplay(window, view, surface, GameSystemExtended, sf::Color::White),
    m_oscillation(0.f),
    m_bgX(-64.f),
    m_bgY(-64.f),
    m_isStart(true),
    m_isOnPad(false)
{
    m_sprButtonSelectScale = 0.f;
}

GameEndScreen::~GameEndScreen() {}

void GameEndScreen::step()
{
    DELTA_TIME = getDeltaTime();

    // allow to know if mouse is in collision with sprite
    bool mouseInCollison(false);

    // even loop
    while (m_window.pollEvent(m_event)) controlEventFocusClosing();

    // Camera
    setView();

    // starting mechanism
    if (m_isStart)
    {
        // if window has focus
        if (m_windowIsActive)
        {
            // allow to use the keys
            if (!m_gameSysExt.isPressed()) m_gameSysExt.m_keyIsPressed = false;

            // m_isClose allow to deactivate scene object
            if (!m_isClose)
            {
                if (mouseCollision(m_sprButtonSelect)) mouseInCollison = true;
                else m_isOnPad = false;

                // avoid the long pressing button effect
                if (!mouseInCollison && m_gameSysExt.isPressed(is::GameSystem::ValidationButton::MOUSE)) m_gameSysExt.m_keyIsPressed = true;

                if (!m_isOnPad)
                {
                    if (mouseCollision(m_sprButtonSelect))
                    {
                        setOptionIndex(0, true, 1.4f);
                        m_isOnPad = true;
                    }
                }

                // validate option
                if ((m_gameSysExt.isPressed(is::GameSystem::ValidationButton::KEYBOARD) ||
                     (m_gameSysExt.isPressed(is::GameSystem::ValidationButton::MOUSE) && mouseInCollison)) &&
                    (m_waitTime == 0 && !m_gameSysExt.m_keyIsPressed))
                {
                    m_gameSysExt.playSound(m_sndSelectOption);
                    m_gameSysExt.useVibrate(m_vibrateTimeDuration);
                    m_sprButtonSelectScale = 1.6f;
                    m_gameSysExt.m_launchOption = is::DisplayOption::MAIN_MENU;
                    m_isClose = true;
                }
            }
        }
    }

    // title animation
    m_oscillation += is::radToDeg((0.08f * is::VALUE_CONVERSION) * DELTA_TIME);

    // background animation
    if (m_bgX < 0.f) m_bgX += (0.5f * is::VALUE_CONVERSION) * DELTA_TIME; else m_bgX = -64.f;
    if (m_bgY < 0.f) m_bgY += (0.5f * is::VALUE_CONVERSION) * DELTA_TIME; else m_bgY = -64.f;
    is::setSFMLObjX_Y(m_sprScreenBG, m_bgX, m_bgY);

    // pad animation
    is::scaleAnimation(DELTA_TIME, m_sprButtonSelectScale, m_sprButtonSelect);

    if (m_isClose) m_isRunning = false;
}

void GameEndScreen::draw()
{
    m_surface.draw(m_sprScreenBG);
    m_surface.draw(m_sprButtonSelect);
    m_surface.draw(m_txtQuitScreen);
    m_surface.draw(m_txtEndTitle);
    m_surface.draw(m_txtEndMsg);
}

bool GameEndScreen::loadResources()
{
    // load resources
    if (!GameDisplay::loadParentResources())                                return false;
    if (!m_texPad.loadFromFile(is::GameConfig::GUI_DIR + "main_menu_pad.png"))          return false;
    if (!m_texScreenBG.loadFromFile(is::GameConfig::GUI_DIR + "screen_background.png")) return false;
    if (!m_fontTitle.loadFromFile(is::GameConfig::FONT_DIR + "space_ranger_3d_mp_pv.otf"))  return false;

    float txtY(180.f);
    is::createWText(m_fontTitle, m_txtEndTitle, is::lang::end_msg_congrat[m_gameSysExt.m_gameLanguage], 0.f, 0.f, sf::Color(0, 0, 0), 48);
    is::centerSFMLObj(m_txtEndTitle);
    is::setSFMLObjX_Y(m_txtEndTitle, m_viewX, m_viewY - txtY);
    is::createWText(m_fontMsg, m_txtEndMsg, is::lang::end_msg_sentences[m_gameSysExt.m_gameLanguage], 32.f, m_viewY - (txtY - 80.f), sf::Color(0, 0, 0), 26);

    float btX(230.f), btY(310.f);
    is::createSprite(m_texPad, m_sprButtonSelect, sf::IntRect(192, 0, 192, 48), sf::Vector2f(btX, btY + 66.f), sf::Vector2f(96.f, 24.f));
    is::createText(m_fontSystem, m_txtQuitScreen, is::lang::pad_main_menu[m_gameSysExt.m_gameLanguage],
                   is::getSFMLObjX(m_sprButtonSelect), is::getSFMLObjY(m_sprButtonSelect) - 6.f, sf::Color::Black, true, 25);
    is::createSprite(m_texScreenBG, m_sprScreenBG, sf::IntRect(0, 0, 740, 580), sf::Vector2f(m_bgX, m_bgY), sf::Vector2f(0.f, 0.f), true);
    return true;
}
