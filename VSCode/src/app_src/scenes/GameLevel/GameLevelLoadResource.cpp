#include "GameLevel.h"

bool GameLevel::loadResources()
{
    if (!GameDisplay::loadParentResources()) return false;

    ////////////////////////////////////////////////////
    #if !defined(__ANDROID__)
    is::createText(m_fontSystem, m_txtDebugInfo, "", 0.f, 0.f, 20);
    #endif
    ////////////////////////////////////////////////////

    is::createText(m_fontSystem, m_txtContinue, is::lang::pad_continue_game[m_gameSysExt.m_gameLanguage], 0.f, 0.f, true);
    is::createText(m_fontSystem, m_txtQuit, is::lang::pad_quit_game[m_gameSysExt.m_gameLanguage], 0.f, 0.f, true);
    is::createText(m_fontSystem, m_txtRestart, is::lang::pad_restart_game[m_gameSysExt.m_gameLanguage], 0.f, 0.f, true);

    if (!m_fontLevel.loadFromFile(is::GameConfig::FONT_DIR + "space_ranger_halftone_italic_qz_30.otf")) return false;

    if (!m_texToolsPad.loadFromFile(is::GameConfig::GUI_DIR + "tools_pad.png"))      return false;
    if (!m_texJoystick.loadFromFile(is::GameConfig::GUI_DIR + "game_pad.png"))       return false;
    if (!m_texIcoMenuBtn.loadFromFile(is::GameConfig::GUI_DIR + "ico_button.png"))   return false;
    m_cancelBt.loadResources(m_texToolsPad);
    m_gameKey.loadResources(m_texJoystick);

    setView();

    // load buffers
    if (!sdEnemyDestroy.loadFromFile(is::GameConfig::SFX_DIR + "enemy_destroy.wav")) return false;
    if (!m_sbHaveHealth.loadFromFile(is::GameConfig::SFX_DIR + "have_health.ogg"))   return false;
    if (!m_sbHurt.loadFromFile(is::GameConfig::SFX_DIR + "hurt.ogg"))                return false;
    if (!m_sbAttack.loadFromFile(is::GameConfig::SFX_DIR + "attack.wav"))            return false;
    if (!m_sbLose.loadFromFile(is::GameConfig::SFX_DIR + "lose.ogg"))                return false;
    if (!m_sbHaveBonus.loadFromFile(is::GameConfig::SFX_DIR + "have_bonus.ogg"))     return false;
    if (!m_sbHaveLife.loadFromFile(is::GameConfig::SFX_DIR + "have_life.wav"))       return false;
    if (!m_sbJump.loadFromFile(is::GameConfig::SFX_DIR + "jump.wav"))                return false;
    if (!m_sbPlayerWin.loadFromFile(is::GameConfig::SFX_DIR + "finish.ogg"))         return false;

    // sound
    m_sndEnemyDestroy.setBuffer(sdEnemyDestroy);
    m_sndHaveHealth.setBuffer(m_sbHaveHealth);
    m_sndAttack.setBuffer(m_sbAttack);
    m_sndHurt.setBuffer(m_sbHurt);
    m_sndLose.setBuffer(m_sbLose);
    m_sndHaveBonus.setBuffer(m_sbHaveBonus);
    m_sndHaveLife.setBuffer(m_sbHaveLife);
    m_sndJump.setBuffer(m_sbJump);
    m_sndPlayerWin.setBuffer(m_sbPlayerWin);

    // GUI resources
    if (!m_texPad.loadFromFile(is::GameConfig::GUI_DIR + "option_pad.png"))    return false;
    if (!m_texDialog.loadFromFile(is::GameConfig::GUI_DIR + "dialog_box.png")) return false;

    is::createSprite(m_texPad, m_sprPad1, sf::IntRect(0, 0, 160, 32), sf::Vector2f(0.f, 0.f), sf::Vector2f(80.f, 16.f));
    is::createSprite(m_texPad, m_sprPad2, sf::IntRect(0, 0, 160, 32), sf::Vector2f(0.f, 0.f), sf::Vector2f(80.f, 16.f));
    is::createSprite(m_texPad, m_sprPad3, sf::IntRect(0, 0, 160, 32), sf::Vector2f(0.f, 0.f) , sf::Vector2f(80.f, 16.f));
    is::createSprite(m_texPad, m_sprButtonSelect, sf::IntRect(160, 0, 160, 32), sf::Vector2f(0.f, 0.f) , sf::Vector2f(80.f, 16.f));

    // tiles
    if (!m_texTile.loadFromFile(is::GameConfig::TILES_DIR + "tileset.png")) return false;

    // sprites
    if (!m_texPlayer.loadFromFile(is::GameConfig::SPRITES_DIR + "player.png"))    return false;
    if (!m_texBonus.loadFromFile(is::GameConfig::SPRITES_DIR + "bonus_icon.png")) return false;
    if (!m_texEnemy.loadFromFile(is::GameConfig::SPRITES_DIR + "enemy.png"))      return false;
    if (!m_texFinishObject.loadFromFile(is::GameConfig::SPRITES_DIR + "finish_flag.png")) return false;

    // background
    if (!m_texLevelBg.loadFromFile(is::GameConfig::TILES_DIR + "level_bg.png"))   return false;

    // chose the corresponding level map array
    short const *mapIndex = is::level::getLevelMap(CURRENT_LEVEL);
    if (!mapIndex)
    {
        is::showLog("Level Map not found !");
        std::terminate();
    }

    // allow to browse the map array
    int dataIndex(0);

    // variable to position the objects in level
    float i(0.f), j(0.f);

    // allow to build tile map
    std::vector<short> backTileValue;

    // this variables allow to store tile id
    // signification of 999 = empty tile
    short backTileNumber(999);

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      LEVEL INTERPRETER
//////////////////////////////////////////////////////////////////////////////////////////////////////

    /*
     * How does the level interpreter work?
     * ------------------------------------------------------------------------------------------
     * It works like the way you write in a book i.e you write from right to left and when you reach
     * the end you come back to the line and so on. Except that here writing is replaced by the
     * creation or positioning of level objects.
     *
     * Here's how the mechanism works?
     * -----------------------------------------------------------------------------------------
     * i, j represents the position of the virtual cursor (represents the hand that writes).
     * For each value of mapIndex[dataIndex] we execute a specific instruction(s)
     * The value 1000 represents an empty case (space),
     * the 1001 allows to move the cursor to the right,
     * the 1002 puts it back on the line,
     * 1003 represents the end of the level and the other values allows to manipulate the
     * objects of the levels.
     */
    do
    {
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      BLOCK
//////////////////////////////////////////////////////////////////////////////////////////////////////
        if (mapIndex[dataIndex] == 0) // block mask
            m_blockList.push_back(std::shared_ptr<Block>(new Block(Block::BlockType::BLOCK_NORMAL, 32.f * j, 32.f * i, 0)));
        else if (mapIndex[dataIndex] == 1) // block transparent (crossing block)
            m_blockList.push_back(std::shared_ptr<Block>(new Block(Block::BlockType::BLOCK_TRANSPARENT, 32.f * j, 32.f * i, 0)));
        else if (mapIndex[dataIndex] == 2) // block horizontal moving
        {
            m_blockList.push_back(std::shared_ptr<Block>(new Block(Block::BlockType::BLOCK_MOVE_HORIZ, 32.f * j, 32.f * i, &m_texTile)));
            m_blockList[m_blockList.size() - 1]->setMoveHorizontal(true);
        }
        else if (mapIndex[dataIndex] == 3) // block vertical moving
        {
            m_blockList.push_back(std::shared_ptr<Block>(new Block(Block::BlockType::BLOCK_MOVE_VERTI, 32.f * j, 32.f * i, &m_texTile)));
            m_blockList[m_blockList.size() - 1]->setMoveVertical(true);
        }

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      BONUS
//////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (mapIndex[dataIndex] == 100) // Bonus
            m_bonusList.push_back(std::shared_ptr<Bonus>(new Bonus(m_texBonus, Bonus::BonusType::BONUS_NORMAL, 32.f * j, 32.f * i)));
        else if (mapIndex[dataIndex] == 101) // Health
            m_bonusList.push_back(std::shared_ptr<Bonus>(new Bonus(m_texBonus, Bonus::BonusType::BONUS_HEALTH, 32.f * j, 32.f * i)));
        else if (mapIndex[dataIndex] == 102) // Life
            m_bonusList.push_back(std::shared_ptr<Bonus>(new Bonus(m_texBonus, Bonus::BonusType::BONUS_1_UP, 32.f * j, 32.f * i)));

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      ENEMY
//////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (mapIndex[dataIndex] == 200)
            m_enemyList.push_back(std::shared_ptr<Enemy>(new Enemy(m_texEnemy, Enemy::EnemyType::ENEMY_SPIKE_BALL, 32.f * j, 32.f * i)));
        else if (mapIndex[dataIndex] == 201)
            m_enemyList.push_back(std::shared_ptr<Enemy>(new Enemy(m_texEnemy, Enemy::EnemyType::ENEMY_BALL, 32.f * j, 32.f * i, 50)));

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      PLAYER
//////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (mapIndex[dataIndex] == 300) // player
        {
            // load player resources
            m_player.loadResources(m_texPlayer, m_sbJump);
            m_player.setX(32.f * j);
            m_player.setY((32.f * i) - 16.f);
            m_player.setStartPosition(m_player.getX(), m_player.getY());
        }

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      GAMEPLAY OBJECT
//////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (mapIndex[dataIndex] == 400) // limiter
            m_limiterList.push_back(std::shared_ptr<Limiter>(new Limiter(32.f * j, 32.f * i)));
        else if (mapIndex[dataIndex] == 401) // finish level
        {
            m_finishObject.setX(32.f * j);
            m_finishObject.setY(32.f * i);
            m_finishObject.loadResources(m_texFinishObject);
            m_finishObject.setStartPosition(m_finishObject.getX(), m_finishObject.getY());
        }

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      TILES
//////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (mapIndex[dataIndex] >= 500 && mapIndex[dataIndex] < 700)
        {
            backTileNumber = (mapIndex[dataIndex] - 500);
        }

        else if (mapIndex[dataIndex] == 1000) // empty tile (empty space)
        {
            // empty tile
            backTileNumber = 999;
        }

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      CURSOR MOVEMENT
//////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (mapIndex[dataIndex] == 1001) // move the cursor
        {
            // filling the tile number array
            backTileValue.push_back(backTileNumber);

            // empty tile
            backTileNumber = 999;
            j++;
        }

        else if (mapIndex[dataIndex] == 1002) // back to the line of cursor
        {
            if (m_levelWidth == 0) m_levelWidth = static_cast<unsigned int>(j); // define the level width
            j = 0.f;
            i++;
            backTileNumber = 999; // empty tile
            m_levelHeight = static_cast<unsigned int>(i); // define the level height
        }

        else // error
        {
            is::showLog("\nUnknown value  : " + is::numToStr(mapIndex[dataIndex]) + "\n");
            //std::terminate();
        }

        // allow to now the line of cursor
        dataIndex++;
    }
    while (mapIndex[dataIndex] != 1003); // read values in array (1003 = end of tile map)

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      SET LEVEL TIME
//////////////////////////////////////////////////////////////////////////////////////////////////////
    m_gameTime.setTimeValue(2, 59, 59);

    // sort object array
    is::sortObjArray(m_bonusList);
    is::sortObjArray(m_enemyList);
    is::sortObjArray(m_blockList);

    // level information
    is::showLog("\nLevel           : " + is::numToStr(CURRENT_LEVEL + 1) +
                "\nInstance Number : " + is::numToStr(is::MainObject::instanceNumber) +
                "\nLevel Width     : " + is::numToStr(m_levelWidth) +
                "\nLevel Height    : " + is::numToStr(m_levelHeight) +
                "\nLevel Time      : " + is::numToStr(m_gameTime.getMinute()) + "min : " + is::numToStr(m_gameTime.getSecond()) + "s" +
                "\n");


//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      BUILD THE BACKGROUND OF LEVEL
//////////////////////////////////////////////////////////////////////////////////////////////////////
    is::createSprite(m_texLevelBg, m_sprLevelBg, sf::IntRect(0, 0, (m_levelWidth * 32), 640), sf::Vector2f(m_viewX * 0.25f - 80.f, m_viewY - 240.f),
                     sf::Vector2f(0.f, 0.f), true);

    // create the tile map with vertex array
    unsigned int valX(0), valY(0);
    int const bgSize(35); // size of vertex array
    bool stop(false);

    while (!stop)
    {
        m_levelBackTile.push_back(std::shared_ptr<LevelTile>(new LevelTile(m_texTile)));
        m_levelBackTile[m_levelBackTile.size() - 1]->load(sf::Vector2u(32, 32), backTileValue, m_levelWidth, m_levelHeight, valX, valY, bgSize, stop);
    }
    WITH (m_levelBackTile.size())
    {
        if (!m_levelBackTile[_I]->hasTile())
        {
            m_levelBackTile[_I].reset();
        }
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      CREATION OF THE LEVEL
//////////////////////////////////////////////////////////////////////////////////////////////////////

    // set view position in relation to player
    m_viewX = m_player.getX();
    m_viewY = m_player.getY();

    if (m_viewX < m_viewW / 2) m_viewX = m_viewW / 2;
    if (m_viewX > static_cast<float>(m_levelWidth) * 32.f - m_viewW / 2)
        m_viewX = static_cast<float>(m_levelWidth) * 32.f - m_viewW / 2;

    if (m_viewY < m_viewH / 2) m_viewY = m_viewH / 2;
    if (m_viewY > static_cast<float>(m_levelHeight) * 32.f - m_viewH / 2)
        m_viewY = static_cast<float>(m_levelHeight) * 32.f - m_viewH / 2;

    m_pauseOption = std::shared_ptr<PauseOption>(new PauseOption(this, m_texIcoMenuBtn));

    // set pause screen object position
    is::setSFMLObjX_Y(m_sprPad1, m_viewX, m_viewY - 32.f);
    is::setSFMLObjX_Y(m_sprPad2, m_viewX, m_viewY + 32.f);
    is::setSFMLObjX_Y(m_sprPad3, m_viewX - (70.f - m_pauseObjMove), m_viewY);
    is::setSFMLObjX_Y(m_sprButtonSelect, is::getSFMLObjX(m_sprPad1), is::getSFMLObjY(m_sprPad1));
    is::setSFMLObjX_Y(m_txtContinue, is::getSFMLObjX(m_sprPad1), is::getSFMLObjY(m_sprPad1));
    is::setSFMLObjX_Y(m_txtQuit, is::getSFMLObjX(m_sprPad3), is::getSFMLObjY(m_sprPad3));
    is::setSFMLObjX_Y(m_recPauseBG, m_viewX, m_viewY);

    // load HUD resources
    m_gameHud.setPosition(m_viewX, m_viewY);
    m_gameHud.loadResources(m_fontSystem);

    // load Dialog Box resources
    m_gameDialog.loadResources(m_texDialog, m_fontSystem);

    // set view param
    setView();

    // create level title object
    m_levelTitle = std::shared_ptr<LevelTitle>(new LevelTitle(m_fontLevel, m_viewX, m_viewY,
                                                              is::lang::title_level_number[m_gameSysExt.m_gameLanguage] +
                                                                is::numToStr(CURRENT_LEVEL + 1)));

    // load level music
    m_mscLevel.openFromFile(is::GameConfig::MUSIC_DIR + "world_1_music.ogg");
    m_mscLevel.setLoop(true);
    m_mscLevel.play();

    // don't play music if this option is off
    if (!m_gameSysExt.m_enableMusic) m_mscLevel.pause();

    // initialize background
    updateBackground();

    return true;
}
