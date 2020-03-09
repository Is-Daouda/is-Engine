#include "GameLevel.h"

bool GameLevel::loadResources()
{
    // load parent resource
    if (!GameDisplay::loadParentResources()) return false;

    is::createText(m_font1, m_txtContinue, "Continue Game", 0.f, 0.f);
    is::createText(m_font1, m_txtQuit, "Quit Game", 0.f, 0.f);
    is::createText(m_font1, m_txtRestart, "Restart Game", 0.f, 0.f);

    // create advice text only in LEVEL 1
    if (CURRENT_LEVEL == LevelId::LEVEL_1)
    {
        is::createText(m_font2, m_txtAdvice, "\t\t\tCollect all bonus to finish level\n"
                                             "Use Left and Right button to control the Ship"
                                             , 0.f, 0.f, sf::Color::White, 20);
        is::centerSFMLObj(m_txtAdvice);
        is::setSFMLObjX_Y(m_txtAdvice, 320.f, 240.f);
    }

    // load GUI sprite
    if (!m_texButton.loadFromFile(is::GUI_DIR + "button.png")) return false;
    if (!m_texPauseButton.loadFromFile(is::GUI_DIR + "pause_button.png")) return false;
    if (!m_texJoystick.loadFromFile(is::GUI_DIR + "joystick.png")) return false;

    // create pause button
    for (int i(0); i < 3; i++)
    {
        is::createSprite(m_texButton, m_sprButton[i], sf::IntRect(0, 0, 160, 32), sf::Vector2f(0.f, 0.f), sf::Vector2f(80.f, 16.f));
    }
    is::createSprite(m_texButton, m_sprButtonSelect, sf::IntRect(0, 32, 160, 32), sf::Vector2f(0.f, 0.f), sf::Vector2f(80.f, 16.f));

    // create pause button locate at right top corner
    m_pauseBt.loadResources(m_texPauseButton);

    // create pause background rectangle
    is::createRectangle(m_recPauseBg, sf::Vector2f(640.f, 480.f), sf::Color(0, 0, 0, 150), 0.f, 0.f, true);

    // create the joystick for control player
    // joystick left for movement
    is::createSprite(m_texJoystick, m_sprJoystick[0], sf::IntRect(0, 0, 96, 96), sf::Vector2f(0.f, 0.f), sf::Vector2f(48.f, 48.f));

    // joystick right for acceleration
    is::createSprite(m_texJoystick, m_sprJoystick[1], sf::IntRect(96, 0, 96, 96), sf::Vector2f(0.f, 0.f), sf::Vector2f(48.f, 48.f));

    // create joystick mask
    for (int i(0); i < 2; i++)
    {
        is::createRectangle(m_recJoystickMask[i], sf::Vector2f(96.f, 96.f), sf::Color::Black,
                            is::getSFMLObjX(m_sprJoystick[i]), is::getSFMLObjY(m_sprJoystick[i]), true);
    }

    // load game play sprite
    if (!m_texPlayer.loadFromFile(is::SPRITES_DIR + "player.png")) return false;
    if (!m_texBonus.loadFromFile(is::SPRITES_DIR + "bonus.png")) return false;
    if (!m_texGoal.loadFromFile(is::SPRITES_DIR + "goal.png")) return false;

    // load tile
    if (!m_texTile.loadFromFile(is::TILES_DIR + "tiles.png"))  return false;

    // load buffers
    if (!m_sbExplosion.loadFromFile(is::SFX_DIR + "explosion.ogg"))  return false;
    if (!m_sbSpeedUp.loadFromFile(is::SFX_DIR + "speed_up.ogg"))     return false;
    if (!m_sbHaveBonus.loadFromFile(is::SFX_DIR + "have_bonus.ogg")) return false;
    if (!m_sbPlayerWin.loadFromFile(is::SFX_DIR + "player_win.ogg")) return false;

    // set sound buffer
    m_sndExplosion.setBuffer(m_sbExplosion);
    m_sndSpeedUp.setBuffer(m_sbSpeedUp);
    m_sndHaveBonus.setBuffer(m_sbHaveBonus);
    m_sndPlayerWin.setBuffer(m_sbPlayerWin);

    // pointer the corresponding level map array
    short const *mapIndex;
    switch (CURRENT_LEVEL)
    {
        case LEVEL_1  : mapIndex = LEVEL_1_MAP; break;
        case LEVEL_2  : mapIndex = LEVEL_2_MAP; break;
        case LEVEL_3  : mapIndex = LEVEL_3_MAP; break;
    }

    // for make operation with the level map array values
    int dataIndex(0);

    // variable for position objects on the level grid
    float i(0.f), j(0.f);

    // array to build tile
    std::vector<short> backTileValue;

    // 999 represent empty tile
    short backTileNumber(999);

    // define level time
    m_gameTime.setValue(2, 0, 0);

    // read values in level map array (7 represent end of map)
    // each value represent a things of tile map in level map array
    do
    {
        if (mapIndex[dataIndex] == 0) // empty space (without tiles and objects)
        {
            backTileNumber = 999; // empty tile
        }
        else if (mapIndex[dataIndex] == 1) // block object + tile 1
        {
            m_blockList.push_back(new Block(32.f * j, 32.f * i)); // create block
            backTileNumber = 0; // tile 1
        }
        else if (mapIndex[dataIndex] == 2) // bonus
            m_bonusList.push_back(new Bonus(m_texBonus, 32.f * j, 32.f * i));

        else if (mapIndex[dataIndex] == 3) // player
        {
            m_player.loadResources(m_texPlayer);
            m_player.setPosition(32.f * j, 32.f * i);
        }
        else if (mapIndex[dataIndex] == 4) // goal
        {
            m_goal.loadResources(m_texGoal);
            m_goal.setPosition(32.f * j, 32.f * i);
        }
        else if (mapIndex[dataIndex] == 5) // tile 2
            backTileNumber = 1;
        else if (mapIndex[dataIndex] == 6) // tile 2
            backTileNumber = 2;
        else if (mapIndex[dataIndex] == 7) // move cursor
        {
            // fetch the tile map array
            backTileValue.push_back(backTileNumber);

            // empty tile
            backTileNumber = 999;
            j++;
        }
        else if (mapIndex[dataIndex] == 8) // return cursor to next line
        {
            if (m_levelWidth == 0) m_levelWidth = static_cast<unsigned int>(j); // define level width
            j = 0.f;
            i++;
            backTileNumber = 999; // empty tile
            m_levelHeight = static_cast<unsigned int>(i); // define level hight
        }
        else // error when is unknown value and show it
        {
            is::showLog("\nUnknown value  : " + is::numToStr(mapIndex[dataIndex]) + "\n");
        }

        // allow to get current line
        dataIndex++;
    }
    while(mapIndex[dataIndex] != 9);

    // show the level information in c++ console
    is::showLog("\nLevel             : " + is::numToStr(CURRENT_LEVEL + 1) +
                "\nLevel Global Time : " +
                    is::numToStr(m_gameTime.getMinute()) + "m " +
                    is::numToStr(m_gameTime.getSecond()) + "s " +
                    is::numToStr(m_gameTime.getMSecond()) + "ms" +
                "\nInstance Number   : " + is::numToStr(is::MainObject::instanceNumber) +
                "\nLevel Width       : " + is::numToStr(m_levelWidth) +
                "\nLevel Height      : " + is::numToStr(m_levelHeight) +
                "\n");

    // sort object in relation to position
    std::sort(m_bonusList.begin(), m_bonusList.end(), is::CompareX());
    std::sort(m_blockList.begin(), m_blockList.end(), is::CompareX());

    // create the backgrounds
    unsigned int valX(0), valY(0);
    int const bgSize(35); // size of vertex array
    bool stop(false);
    while (!stop)
    {
        m_levelTile.push_back(new LevelTile(m_texTile));
        m_levelTile[m_levelTile.size() - 1]->load(sf::Vector2u(32, 32), backTileValue, m_levelWidth, m_levelHeight, valX, valY, bgSize, stop);
    }
    WITH (m_levelTile.size())
    {
        if (!m_levelTile[_I]->hasTile())
        {
            delete m_levelTile[_I];
            m_levelTile[_I] = 0;
        }
    }

    // positioning the view in relation to player
    m_viewX = m_player.getX();
    m_viewY = m_player.getY();
    if (m_viewX < VIEW_W / 2) m_viewX = VIEW_W / 2;
    if (m_viewX > static_cast<float>(m_levelWidth) * 32.f - VIEW_W / 2) m_viewX = static_cast<float>(m_levelWidth) * 32.f - VIEW_W / 2;
    if (m_viewY < VIEW_H / 2) m_viewY = VIEW_H / 2;
    if (m_viewY > static_cast<float>(m_levelHeight) * 32.f - VIEW_H / 2) m_viewY = static_cast<float>(m_levelHeight) * 32.f - VIEW_H / 2;

    // positioning of the view
    m_view.setCenter(m_viewX, m_viewY);
    m_app.setView(m_view);

    // create sprite for the pause menu
    for (int i(0); i < 3; i++) is::setSFMLObjX_Y(m_sprButton[i], m_viewX, m_viewY + m_buttonY + (48.f * i));
    is::setSFMLObjX_Y(m_sprButtonSelect, m_viewX , m_viewY + m_buttonY);
    is::setSFMLObjX_Y(m_txtContinue, m_viewX, m_viewY + m_buttonY - 10.f);
    is::setSFMLObjX_Y(m_txtRestart, m_viewX, m_viewY + m_buttonY + 42.f);
    is::setSFMLObjX_Y(m_txtQuit, m_viewX, m_viewY + m_buttonY + 94.f);
    is::setSFMLObjX_Y(m_recTransition, m_viewX, m_viewY);

    // load HUD resource
    m_gameHud.loadResources(m_font1);
    is::setSFMLObjX_Y(m_gameHud, m_viewX, m_viewY);

    return true; // load resource successfully
}
