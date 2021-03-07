#pragma once
#include "../../../isEngine/system/entity/Background.h"
#include "../../objects/widgets/GameDialog.h"
#include "../../objects/HelloWorld.h"

class HelloScene : public is::GameDisplay
{
public:

    /*  					/!\ WARNING! /!\
     * This constructor is no longer supported in this version of the engine. Use the one below.
     *
     * HelloScene(sf::RenderWindow &window, sf::View &view, is::Render &surface, is::GameSystemExtended &gameSysExt):
     * GameDisplay(window, view, surface, gameSysExt, sf::Color::White) {}
     */

    HelloScene(is::GameSystemExtended &gameSysExt):
        GameDisplay(gameSysExt, sf::Color::White /* => scene color*/) {}

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

        // add a background to the position x = 0, y = 0 which will fill the scene and which will be scrolled (scrolling speed = 0.5)
        SDMaddSceneObject(std::make_shared<is::Background>(texBg, 0.f, 0.f, this, 0.5f, -0.5f, false, false));

        // add an SFML sprite which will be above the background and which will have the name "Logo" (by default x = 0 and y = 0)
        SDMaddSprite(GRMgetTexture("is_engine_logo"), "Logo", 0.f, 85.5f, false, -1);

        // add an object at position x = 0, y = 0 which will be updated and displayed in the scene
        SDMaddSceneObject(std::make_shared<HelloWorld>(0.f, 0.f, this));

        // add RPG style game dialog
        auto gameDialog = std::make_shared<is::GameDialog>(texDialog, GRMgetFont("font_msg"), this);
        gameDialog->setDepth(-2); // the display depth (make it appear on all objects. The object with the smallest value appears on the others)
        gameDialog->setDialog(is::GameDialog::DialogIndex::DIALOG_HELLO); // set the corresponding dialog (See GameDialog.h and GameLanguage.h for more details on creating a message for dialogue)
        SDMaddSceneObject(gameDialog);

        // add and play music
        GSMaddSound("game_music", is::GameConfig::MUSIC_DIR + "game_music.wav");
        GSMplaySound("game_music");
        GSMsetSoundLoop("game_music", true);
    }
};
