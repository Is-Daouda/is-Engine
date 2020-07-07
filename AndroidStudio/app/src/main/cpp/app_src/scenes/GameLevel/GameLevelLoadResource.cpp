#include "GameLevel.h"

void GameLevel::loadResources()
{
    GameDisplay::loadParentResources();

    is::loadSFMLObjResource(m_fontLevel, is::GameConfig::FONT_DIR + "space_ranger_halftone_italic_qz_30.otf");

    is::loadSFMLObjResource(m_texToolsPad, is::GameConfig::GUI_DIR + "tools_pad.png");
    is::loadSFMLObjResource(m_texJoystick, is::GameConfig::GUI_DIR + "game_pad.png");
    is::loadSFMLObjResource(m_texIcoMenuBtn, is::GameConfig::GUI_DIR + "ico_button.png");

    auto gameKey = std::shared_ptr<is::GameKeyData>(new is::GameKeyData(this));
    gameKey->loadResources(m_texJoystick);
    gameKey->setDepth(-9);

    // We add the object to the SDM container but we order it to display it only
    // We also give it a name that will allow us to identify it in the container
    SDMaddSceneObject(gameKey, false, true, "GameKeyData");

    // load sounds with GSM
    GSMaddSound("enemy_destroy", is::GameConfig::SFX_DIR + "enemy_destroy.wav");
    GSMaddSound("have_health", is::GameConfig::SFX_DIR + "have_health.ogg");
    GSMaddSound("hurt", is::GameConfig::SFX_DIR + "hurt.ogg");
    GSMaddSound("attack", is::GameConfig::SFX_DIR + "attack.wav");
    GSMaddSound("lose", is::GameConfig::SFX_DIR + "lose.ogg");
    GSMaddSound("have_bonus", is::GameConfig::SFX_DIR + "have_bonus.ogg");
    GSMaddSound("have_life", is::GameConfig::SFX_DIR + "have_life.wav");
    GSMaddSound("jump", is::GameConfig::SFX_DIR + "jump.wav");
    GSMaddSound("finish", is::GameConfig::SFX_DIR + "finish.ogg");

    // GUI resources
    is::loadSFMLObjResource(m_texPad, is::GameConfig::GUI_DIR + "option_pad.png");
    is::loadSFMLObjResource(m_texDialog, is::GameConfig::GUI_DIR + "dialog_box.png");
    is::createSprite(m_texPad, m_sprButtonSelect, sf::IntRect(160, 0, 160, 32), sf::Vector2f(0.f, 0.f) , sf::Vector2f(80.f, 16.f));

    // tiles
    is::loadSFMLObjResource(m_texTile, is::GameConfig::TILES_DIR + "tileset.png");

    // sprites
    is::loadSFMLObjResource(m_texPlayer, is::GameConfig::SPRITES_DIR + "player.png");
    is::loadSFMLObjResource(m_texBonus, is::GameConfig::SPRITES_DIR + "bonus_icon.png");
    is::loadSFMLObjResource(m_texEnemy, is::GameConfig::SPRITES_DIR + "enemy.png");
    is::loadSFMLObjResource(m_texFinishObject, is::GameConfig::SPRITES_DIR + "finish_flag.png");

    // background
    is::loadSFMLObjResource(m_texBackground, is::GameConfig::TILES_DIR + "level_bg.png");

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

    auto gameDialog = std::shared_ptr<GameDialog>(new GameDialog(this));
    gameDialog->setName("GameDialog");
    gameDialog->loadResources(m_texDialog, m_fontSystem);
    gameDialog->setDepth(-8);
    SDMaddSceneObject(gameDialog); // We add the object in the SDM container

    auto player = std::shared_ptr<Player>(new Player(this, m_timeUp, m_restartTime));
    player->setName("Player");
    player->setDepth(-1);
    SDMaddSceneObject(player); // We add the object in the SDM container

    auto finishObject = std::shared_ptr<FinishObject>(new FinishObject(this));
    finishObject->setName("FinishObject");
    finishObject->setDepth(-1);
    SDMaddSceneObject(finishObject); // We add the object in the SDM container

    auto gameHud = std::shared_ptr<HUD>(new HUD(this, m_gameTime));
    gameHud->setName("HUD");
    gameHud->loadResources(m_fontSystem);
    gameHud->setDepth(-7);
    SDMaddSceneObject(gameHud); // We add the object in the SDM container

    auto cancelBt = std::shared_ptr<CancelButton>(new CancelButton(this));
    cancelBt->setName("CancelButton");
    cancelBt->loadResources(m_texToolsPad);
    cancelBt->setDepth(-9);
    SDMaddSceneObject(cancelBt); // We add the object in the SDM container

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
            SDMaddSceneObject(std::shared_ptr<Block>(new Block(Block::BlockType::BLOCK_NORMAL, 32.f * j, 32.f * i, 0)), true, false, "Block");
        else if (mapIndex[dataIndex] == 1) // block transparent (crossing block)
            SDMaddSceneObject(std::shared_ptr<Block>(new Block(Block::BlockType::BLOCK_TRANSPARENT, 32.f * j, 32.f * i, 0)), true, false, "Block");
        else if (mapIndex[dataIndex] == 2) // block horizontal moving
        {
            auto block = std::shared_ptr<Block>(new Block(Block::BlockType::BLOCK_MOVE_HORIZ, 32.f * j, 32.f * i, &m_texTile));
            block->setMoveHorizontal(true);
            SDMaddSceneObject(block, true, true, "Block");
        }
        else if (mapIndex[dataIndex] == 3) // block vertical moving
        {
            auto block = std::shared_ptr<Block>(new Block(Block::BlockType::BLOCK_MOVE_VERTI, 32.f * j, 32.f * i, &m_texTile));
            block->setMoveVertical(true);
            SDMaddSceneObject(block, true, true, "Block");
        }

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      BONUS
//////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (mapIndex[dataIndex] == 100) // Bonus
            SDMaddSceneObject(std::shared_ptr<Bonus>(new Bonus(m_texBonus, Bonus::BonusType::BONUS_NORMAL, 32.f * j, 32.f * i, this)));
        else if (mapIndex[dataIndex] == 101) // Health
            SDMaddSceneObject(std::shared_ptr<Bonus>(new Bonus(m_texBonus, Bonus::BonusType::BONUS_HEALTH, 32.f * j, 32.f * i, this)));
        else if (mapIndex[dataIndex] == 102) // Life
            SDMaddSceneObject(std::shared_ptr<Bonus>(new Bonus(m_texBonus, Bonus::BonusType::BONUS_1_UP, 32.f * j, 32.f * i, this)));

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      ENEMY
//////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (mapIndex[dataIndex] == 200)
            SDMaddSceneObject(std::shared_ptr<Enemy>(new Enemy(m_texEnemy, Enemy::EnemyType::ENEMY_SPIKE_BALL, 32.f * j, 32.f * i, this)));
        else if (mapIndex[dataIndex] == 201)
            SDMaddSceneObject(std::shared_ptr<Enemy>(new Enemy(m_texEnemy, Enemy::EnemyType::ENEMY_BALL, 32.f * j, 32.f * i, this, 50)));

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      PLAYER
//////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (mapIndex[dataIndex] == 300) // player
        {
            // load player resources
            player->loadResources(m_texPlayer);
            player->setPosition(32.f * j, (32.f * i) - 16.f);
            player->setStartPosition(player->getX(), player->getY());
        }

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      GAMEPLAY OBJECT
//////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (mapIndex[dataIndex] == 400) // limiter
            SDMaddSceneObject(std::shared_ptr<Limiter>(new Limiter(32.f * j, 32.f * i)), false, false, "Limiter");
        else if (mapIndex[dataIndex] == 401) // finish level
        {
            finishObject->setPosition(32.f * j, 32.f * i);
            finishObject->loadResources(m_texFinishObject);
            finishObject->setStartPosition(finishObject->getX(), finishObject->getY());
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
            if (m_sceneWidth == 0) m_sceneWidth = static_cast<unsigned int>(j); // define the level width
            j = 0.f;
            i++;
            backTileNumber = 999; // empty tile
            m_sceneHeight = static_cast<unsigned int>(i); // define the level height
        }
        else // error
        {
            is::showLog("\nUnknown value  : " + is::numToStr(mapIndex[dataIndex]) + "\n");
            ///std::terminate();
        }

        // allow to now the line of cursor
        dataIndex++;
    }
    while (mapIndex[dataIndex] != 1003); // read values in array (1003 = end of tile map)

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      SET LEVEL TIME
//////////////////////////////////////////////////////////////////////////////////////////////////////
    m_gameTime.setTimeValue(2, 59, 59);

    // level information
    is::showLog("\nLevel           : " + is::numToStr(CURRENT_LEVEL + 1) +
                "\nInstance Number : " + is::numToStr(is::MainObject::instanceNumber) +
                "\nLevel Width     : " + is::numToStr(m_sceneWidth) +
                "\nLevel Height    : " + is::numToStr(m_sceneHeight) +
                "\nLevel Time      : " + is::numToStr(m_gameTime.getMinute()) + "min : " + is::numToStr(m_gameTime.getSecond()) + "s" +
                "\n");

    // create background
    auto bg = std::shared_ptr<Background>(new Background(this, m_texBackground));
    bg->setDepth(is::DepthObject::VERY_BIG_DEPTH);
    SDMaddSceneObject(bg); // We add the object in the SDM container

    // create the tile map with vertex array
    unsigned int valX(0), valY(0);
    int const bgSize(35); // size of vertex array
    bool stop(false);

    while (!stop)
    {
        auto tile = std::shared_ptr<LevelTile>(new LevelTile(this, m_texTile));
        tile->loadResources(sf::Vector2u(32, 32), backTileValue, m_sceneWidth, m_sceneHeight, valX, valY, bgSize, stop);
        tile->setDepth(is::DepthObject::BIG_DEPTH);
        SDMaddSceneObject(tile); // We add the object in the SDM container
    }
    WITH (m_SDMsceneObjects.size())
    {
        if (dynamic_cast<LevelTile*>(m_SDMsceneObjects[_I].get()) != nullptr)
        {
            if (!static_cast<LevelTile*>(m_SDMsceneObjects[_I].get())->hasTile())
            {
                m_SDMsceneObjects[_I].reset();
            }
        }
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      CREATION OF THE LEVEL
//////////////////////////////////////////////////////////////////////////////////////////////////////

    // set view position in relation to player
    m_viewX = player->getX();
    m_viewY = player->getY();

    if (m_viewX < m_viewW / 2) m_viewX = m_viewW / 2;
    if (m_viewX > static_cast<float>(m_sceneWidth) * 32.f - m_viewW / 2)
        m_viewX = static_cast<float>(m_sceneWidth) * 32.f - m_viewW / 2;

    if (m_viewY < m_viewH / 2) m_viewY = m_viewH / 2;
    if (m_viewY > static_cast<float>(m_sceneHeight) * 32.f - m_viewH / 2)
        m_viewY = static_cast<float>(m_sceneHeight) * 32.f - m_viewH / 2;

    // creation of the object which manages the physics of the level
    // but avoid the SDM drawing it
    SDMaddSceneObject(std::shared_ptr<BlockPhysic>(new BlockPhysic(this)), true, false);

    auto pauseOption = std::shared_ptr<PauseOption>(new PauseOption(this, m_texIcoMenuBtn, m_texPad));
    pauseOption->setName("PauseOption");
    pauseOption->setDepth(-10);
    SDMaddSceneObject(pauseOption, false); // We add the object in the SDM container, but avoid SDM updating it

    // load HUD resources
    gameHud->setPosition(m_viewX, m_viewY);

    // create level title object
    auto lvlTitle = std::shared_ptr<LevelTitle>(new LevelTitle(m_fontLevel, m_viewX, m_viewY,
                                                    is::lang::title_level_number[m_gameSysExt.m_gameLanguage] +
                                                    is::numToStr(CURRENT_LEVEL + 1)));
    lvlTitle->setDepth(-5);
    SDMaddSceneObject(lvlTitle); // We add the object in the SDM container

    // load level music
    GSMaddMusic("level_music", is::GameConfig::MUSIC_DIR + "world_1_music.ogg");
    GSMgetMusic("level_music")->setLoop(true);
    GSMgetMusic("level_music")->play();

    // don't play music if this option is off
    if (!m_gameSysExt.m_enableMusic) GSMgetMusic("level_music")->pause();
}
