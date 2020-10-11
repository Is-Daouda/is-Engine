#pragma once
#include "../../../isEngine/system/entity/Background.h"
#include "../../objects/widgets/GameDialog.h"
#include "../../objects/HelloWorld.h"

class HelloScene : public is::GameDisplay
{
public:
    HelloScene(sf::RenderWindow &window, sf::View &view, is::Render &surface, is::GameSystemExtended &gameSysExt):
        GameDisplay(window, view, surface, gameSysExt, sf::Color::White /* => scene color*/) {}

    void loadResources() {
        m_gameSysExt.m_gameLanguage = is::lang::ENGLISH; // set default game language

        // uncomment to change English language in French
        // m_gameSysExt.m_gameLanguage = is::lang::FRANCAIS;

        // load font and texture
        GameDisplay::loadParentResources(); // allows to load system resource (very important never forgot to call him)
        GRMaddTexture("is_engine_logo", is::GameConfig::SPRITES_DIR + "is_engine_logo.png");
        GRMaddTexture("hello_world",    is::GameConfig::SPRITES_DIR + "hello_world.png");
        auto &texBg = GRMaddTexture("background",     is::GameConfig::TILES_DIR + "background.png");
        auto &texDialog = GRMaddTexture("dialog_box", is::GameConfig::GUI_DIR     + "dialog_box.png");

        // add a background that will fill the scene and scroll it (scroll speed = 0.5)
        SDMaddSceneObject(std::make_shared<is::Background>(texBg, 0.f, 0.f, this, 0.5f, -0.5f, false, false));

        // add a SFML sprite that will be above the background
        SDMaddSprite(sf::Sprite(GRMgetTexture("is_engine_logo")), "Logo", -1);
        SDMgetObject("Logo")->setY(85.5f); // change the logo position

        // add an object that will be updated and displayed
        SDMaddSceneObject(std::make_shared<HelloWorld>(0.f, 0.f, this));

        // add RPG style game dialog
        auto gameDialog = std::make_shared<is::GameDialog>(texDialog, GRMgetFont("font_msg"), this);
        gameDialog->setDepth(-2); // the display depth (make it appear on all objects. The object with the smallest value appears on the others)
        gameDialog->setDialog(is::GameDialog::DialogIndex::DIALOG_HELLO); // set the corresponding dialog (See GameDialog.h and GameLanguage.h for more details on creating a message for dialogue)
        SDMaddSceneObject(gameDialog);

        // add and play music
        GSMaddMusic("game_music", is::GameConfig::MUSIC_DIR + "game_music.ogg");
        GSMplayMusic("game_music");
    }
};
