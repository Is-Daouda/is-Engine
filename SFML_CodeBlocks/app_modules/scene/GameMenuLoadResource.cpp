#include "GameMenu.h"

bool GameMenu::loadResources()
{
    // load parent resource
    if (!GameDisplay::loadParentResources()) return false;

    // load textures
    if (!m_texButton.loadFromFile(is::GUI_DIR + "button.png")) return false;
    if (!m_texBg.loadFromFile(is::GUI_DIR + "menu_bg.png")) return false;

    // create option text
    float const TXT_OPTION_Y(300.f);
    is::createText(m_font1, m_txtOptionValue[0], "Enable SOUND            :    ",
                   m_viewX - 180.f, TXT_OPTION_Y , sf::Color(sf::Color(0, 255, 0)), 30);
    is::createText(m_font1, m_txtOptionValue[1], "Enable MUSIC             :    ",
                   m_viewX - 180.f, TXT_OPTION_Y + 50.f, sf::Color(sf::Color(0, 255, 0)), 30);
    is::createText(m_font1, m_txtOptionValue[2], "Enable VIBRATE          :    ",
                   m_viewX - 180.f, TXT_OPTION_Y + 100.f, sf::Color(sf::Color(0, 255, 0)), 30);

    // create stretched background
    is::createSprite(m_texBg, m_sprBg, sf::IntRect(0, 0, 640, 480), sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), true);

    float const BT_X(250.f),
                BT_Y(180.f);

    // creation button sprite
    for (int i(0); i < 2; i++)
    {
        is::createSprite(m_texButton, m_sprButton[i], sf::IntRect(0, 0, 160, 32), sf::Vector2f(BT_X, BT_Y + (48.f * i)), sf::Vector2f(80.f, 16.f));
        is::centerSFMLObj(m_sprButton[i]);
    }
    is::createSprite(m_texButton, m_sprButtonSelect, sf::IntRect(0, 32, 160, 32), sf::Vector2f(0.f, 0.f), sf::Vector2f(80.f, 16.f));
    is::centerSFMLObj(m_sprButtonSelect);
    is::setSFMLObjX_Y(m_sprButtonSelect, is::getSFMLObjX(m_sprButton[0]), is::getSFMLObjY(m_sprButton[0]));

    // create text on button with another font
    is::createText(m_font2, m_txtStartGame, "Start Game",   0.f, 0.f, sf::Color::White, 20);
    is::createText(m_font2, m_txtContinue, "Continue Game", 0.f, 0.f, 20);
    is::centerSFMLObj(m_txtStartGame);
    is::centerSFMLObj(m_txtContinue);
    is::setSFMLObjX_Y(m_txtStartGame, is::getSFMLObjX(m_sprButton[0]), is::getSFMLObjY(m_sprButton[0]) - 8.f);
    is::setSFMLObjX_Y(m_txtContinue, is::getSFMLObjX(m_sprButton[1]), is::getSFMLObjY(m_sprButton[1]) - 8.f);

    // create game version text
    is::createText(m_font2, m_txtVersion, "v : " + is::GameVersion::getGameVersion(), 0.f, 0.f, sf::Color::White, 20);
    is::centerSFMLObj(m_txtVersion);
    is::setSFMLObjX_Y(m_txtVersion, 600.f, 460.f);

    // create Main Menu text
    is::createText(m_font2, m_txtTitle, "Main Menu", 0.f, 0.f, sf::Color::White, 48);
    is::centerSFMLObj(m_txtTitle);
    is::setSFMLObjX_Y(m_txtTitle, 320.f, 64.f);

    // load data if exists
    if (m_gameSysExt.fileExist(is::DATA_FILE))
    {
        m_gameSysExt.loadData(is::DATA_FILE);
        m_saveFileOpen = true;
    }

    // load configuration data if exists
    if (m_gameSysExt.fileExist(is::CONFIG_FILE))
    {
        m_gameSysExt.loadConfig(is::CONFIG_FILE);
    }

    return true; // resource loaded successfully
}
