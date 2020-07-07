#include "GameMenu.h"

void GameMenu::loadResources()
{
    GameDisplay::loadParentResources();

    // load textures
    is::loadSFMLObjResource(m_texPad, is::GameConfig::GUI_DIR + "main_menu_pad.png");
    is::loadSFMLObjResource(m_texPad2, is::GameConfig::GUI_DIR + "option_pad.png");
    is::loadSFMLObjResource(m_texScreenBG, is::GameConfig::GUI_DIR + "screen_background.png");
    is::loadSFMLObjResource(m_texToolsPad, is::GameConfig::GUI_DIR + "tools_pad.png");
    is::loadSFMLObjResource(m_texGamePad, is::GameConfig::GUI_DIR + "game_pad.png");

    is::loadSFMLObjResource(m_fontTitle, is::GameConfig::FONT_DIR + "space_ranger_3d_mp_pv.otf");
    m_cancelBt.loadResources(m_texToolsPad);

    // load configuration file
    if (m_gameSysExt.fileExist(is::GameConfig::CONFIG_FILE)) m_gameSysExt.loadConfig(is::GameConfig::CONFIG_FILE);

    // game title
    is::createWText(m_fontTitle, m_txtGameTitle, L"is::Engine v" + is::GameConfig::getGameVersion() + L"\n\t  Demo",
                    65.f, 32.f, sf::Color(0, 0, 0), 64);

    float distance(5.f), widgetSpace(65.f);

    // create sprites
    is::createSprite(m_texPad, m_sprPad1, sf::IntRect(0, 0, 192, 48), sf::Vector2f(m_xPos, m_yPos + distance), sf::Vector2f(96.f, 24.f));
    is::createSprite(m_texPad, m_sprPad2, sf::IntRect(0, 0, 192, 48), sf::Vector2f(m_xPos, m_yPos + widgetSpace + distance), sf::Vector2f(96.f, 24.f));
    is::createSprite(m_texPad, m_sprPad3, sf::IntRect(0, 0, 192, 48), sf::Vector2f(m_xPos, m_yPos + widgetSpace * 2.f + distance), sf::Vector2f(96.f, 24.f));
    is::createSprite(m_texPad, m_sprButtonSelect, sf::IntRect(192, 0, 192, 48), sf::Vector2f(m_xPos, m_yPos + distance), sf::Vector2f(96.f, 24.f));
    float btYSize(0.9f);
    is::setSFMLObjScaleX_Y(m_sprPad1, 1.f, btYSize);
    is::setSFMLObjScaleX_Y(m_sprPad2, 1.f, btYSize);
    is::setSFMLObjScaleX_Y(m_sprPad3, 1.f, btYSize);

    // sprite background
    is::createSprite(m_texScreenBG, m_sprScreenBG, sf::IntRect(0, 0, 672, 512),sf::Vector2f(m_bgX, m_bgY), sf::Vector2f(0.f , 0.f), true);

    // create text for main menu
    float const TXT_Y_ON_BT(8.f);
    int const _PAD_TXT_SIZE(22);
    is::createText(m_fontSystem, m_txtStartGame, is::lang::pad_new_game[m_gameSysExt.m_gameLanguage],
                   is::getSFMLObjX(m_sprPad1), is::getSFMLObjY(m_sprPad1) - TXT_Y_ON_BT, sf::Color::Blue, true, _PAD_TXT_SIZE);
    is::createText(m_fontSystem, m_txtContinue, is::lang::pad_continue_game[m_gameSysExt.m_gameLanguage],
                   is::getSFMLObjX(m_sprPad2), is::getSFMLObjY(m_sprPad2) - TXT_Y_ON_BT, true, _PAD_TXT_SIZE);
    is::createWText(m_fontSystem, m_txtPadConfig, is::lang::pad_controller[m_gameSysExt.m_gameLanguage],
                   is::getSFMLObjX(m_sprPad3), is::getSFMLObjY(m_sprPad3) - TXT_Y_ON_BT, sf::Color(0, 0, 0), _PAD_TXT_SIZE);
    is::centerSFMLObj(m_txtPadConfig);

    // create text for game option
    int const _SIZE(26);
    float const _X_OPT(m_viewX - 50.f), _Y_OPT(m_viewY - 30.f), _OPT_SPACE(50.f);
    is::createText(m_fontSystem, m_txtOptionValue[0], is::lang::opt_enable_sound[m_gameSysExt.m_gameLanguage],
                   _X_OPT, _Y_OPT, sf::Color(sf::Color(0, 0, 0)), _SIZE);
    is::createText(m_fontSystem, m_txtOptionValue[1], is::lang::opt_enable_music[m_gameSysExt.m_gameLanguage],
                   _X_OPT, _Y_OPT + _OPT_SPACE, sf::Color(sf::Color(0, 0, 0)), _SIZE);
    is::createText(m_fontSystem, m_txtOptionValue[2], is::lang::opt_enable_vibrate[m_gameSysExt.m_gameLanguage],
                   _X_OPT, _Y_OPT + _OPT_SPACE * 2.f, sf::Color(sf::Color(0, 0, 0)), _SIZE);
    is::createText(m_fontSystem, m_txtOptionValue[3], is::lang::opt_game_lang[m_gameSysExt.m_gameLanguage],
                   _X_OPT, _Y_OPT + _OPT_SPACE * 3.f, sf::Color(sf::Color(0, 0, 0)), _SIZE);

    // load game data
    if (m_gameSysExt.fileExist(is::GameConfig::GAME_DATA_FILE))
    {
        m_gameSysExt.loadData(is::GameConfig::GAME_DATA_FILE);
        if (m_gameSysExt.m_gameProgression > m_gameSysExt.m_levelNumber) m_gameSysExt.m_gameProgression = m_gameSysExt.m_levelNumber;
        m_saveFileOpen = true;
    }

    m_gameSysExt.loadPadConfig(is::GameConfig::GAME_PAD_FILE);
    float _xPos(150.f);
    is::createSprite(m_texPad2, m_sprPermuteAB, sf::IntRect(160, 0, 160, 32), sf::Vector2f(0.f, 0.f), sf::Vector2f(80.f, 16.f));
    is::setSFMLObjX_Y(m_sprPermuteAB, m_viewX - _xPos - 20.f, m_viewY - 80.f);
    is::createWText(m_fontSystem, m_txtPermuteAB, is::lang::msg_permute_AB[m_gameSysExt.m_gameLanguage] + getABPlace(), 0.f, 0.f, sf::Color(255, 255, 255));
    is::centerSFMLObj(m_txtPermuteAB);
    is::setSFMLObjX_Y(m_txtPermuteAB, is::getSFMLObjX(m_sprPermuteAB), is::getSFMLObjY(m_sprPermuteAB) - TXT_Y_ON_BT + 1.f);

    is::createWText(m_fontSystem, m_txtMovePad, is::lang::msg_how_move_control[m_gameSysExt.m_gameLanguage], 0.f, 0.f, sf::Color(255, 255, 255, 80));
    is::centerSFMLObj(m_txtMovePad);
    is::setSFMLObjX_Y(m_txtMovePad, m_viewX, m_viewY);

    is::createText(m_fontSystem, m_txtSetAlpha, "Transparence", m_viewX + _xPos, m_viewY - 85.f, true, 20);
    is::setSFMLObjFillColor(m_txtSetAlpha, sf::Color::White);
    float const _DIST(65.f);
    is::createSprite(m_texToolsPad, m_sprAddAlpha, sf::IntRect(32, 0, 32, 32),
                     sf::Vector2f(is::getSFMLObjX(m_txtSetAlpha) + _DIST, is::getSFMLObjY(m_txtSetAlpha) - 10.f), sf::Vector2f(16.f, 16.f));
    is::createSprite(m_texToolsPad, m_sprReduceAlpha, sf::IntRect(96, 0, 32, 32),
                     sf::Vector2f(is::getSFMLObjX(m_txtSetAlpha) - _DIST - 32.f, is::getSFMLObjY(m_txtSetAlpha) - 10.f), sf::Vector2f(16.f, 16.f));
    is::createSprite(m_texGamePad, m_sprJoystick[0], sf::IntRect(0, 0, 134, 134), sf::Vector2f(0.f, 0.f), sf::Vector2f(67.f, 67.f));
    is::createSprite(m_texGamePad, m_sprJoystick[1], sf::IntRect(134, ((!m_gameSysExt.m_permutePadAB) ? 0 : 67), 144, 67), sf::Vector2f(0.f, 0.f), sf::Vector2f(72.f, 37.f));
    is::createRectangle(m_recLine, sf::Vector2f(650.f, 1.5f), sf::Color::White, m_viewX, m_viewY - 34.f, true);
    is::createRectangle(m_recSelectPad, sf::Vector2f(134.f, 134.f), sf::Color::Transparent, 0.f, 0.f, true);
    is::setSFMLObjOutlineColor(m_recSelectPad, 1.f, sf::Color::Red);

    is::createRectangle(m_recCfgBg, sf::Vector2f(m_viewW + 10.f, m_viewH + 10.f), sf::Color(0, 0, 0, 230), m_viewX, m_viewY, true);
}
