#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <memory>

#include "../../../isEngine/system/display/GameDisplay.h"
#include "../../../isEngine/system/function/GameKeyData.h"

#include "../../objects/gamelevel/Player.h"
#include "../../objects/gamelevel/Block.h"
#include "../../objects/gamelevel/BlockPhysic.h"
#include "../../objects/gamelevel/Background.h"
#include "../../objects/gamelevel/HUD.h"
#include "../../objects/gamelevel/Bonus.h"
#include "../../objects/gamelevel/Enemy.h"
#include "../../objects/gamelevel/ElectroShock.h"
#include "../../objects/gamelevel/FinishObject.h"
#include "../../objects/gamelevel/LevelTile.h"
#include "../../objects/gamelevel/LevelTitle.h"
#include "../../objects/gamelevel/Limiter.h"
#include "../../objects/widgets/CancelButton.h"
#include "../../objects/widgets/PauseOption.h"
#include "../../objects/widgets/GameDialog.h"

#include "../../levels/Level.h"
#include "../../language/GameLanguage.h"

/// uncomment to use Box 2D
//#include "../../../isEngine/ext_lib/Box2D/Box2D.h"

class GameLevel : public is::GameDisplay
{
public:
    GameLevel(sf::RenderWindow &window, sf::View &swooshView, sf::RenderTexture &surface, GameSystemExtended &gameSysExt);
    ~GameLevel();

    void step();

    //////////////////////////////////////////////////////
    // void draw();
    //
    // This method is no longer used because the SDM is
    // responsible for displaying the objects of the scene
    // for us.
    //////////////////////////////////////////////////////

    void loadResources();

private:
    void gamePlay();
    void levelSpecialAction();
    void stopSounds(bool val);
    void pauseGame();

private:
    sf::Texture m_texPad, m_texToolsPad;
    sf::Texture m_texPlayer, m_texFinishObject, m_texEnemy, m_texBonus, m_texBackground, m_texTile;
    sf::Texture m_texIcoMenuBtn;
    sf::Texture m_texDialog, m_texJoystick;
    sf::Font m_fontLevel;

    // permanents objects
    is::GameTime m_gameTime;

    int const CURRENT_LEVEL;
    int m_restartTime;
    bool m_timeUp, m_countLevelTime;
};

#endif // GAMELEVEL_H
