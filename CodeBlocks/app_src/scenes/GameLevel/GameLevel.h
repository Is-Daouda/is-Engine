#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <memory>

#include "../../../isEngine/system/display/GameDisplay.h"
#include "../../../isEngine/system/function/GameKeyData.h"

#include "../../objects/gamelevel/Player.h"
#include "../../objects/gamelevel/Block.h"
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
    void draw();

    bool loadResources();

private:
    void gamePlay();
    void levelSpecialAction();
    void stopSounds(bool val);
    void playerHurt(bool canContinue = true);

	/// define the game control mechanism
	void commandController();
    void pauseGame();
    void stopLevelMusic();
    void updatePauseObj(bool useMoveAnimation);
    void updateBackground();
    void updateObjBonusList();
    void updateObjEnemyList();
    void updateObjView();

    bool clearObject(float const &x) const;
    bool playerIsVulnerable() const;
    bool isInPlayerRay(std::shared_ptr<is::MainObject> &obj) const;
	float getPlayerOtherObjPtDir(std::shared_ptr<is::MainObject> &obj);

private:

    void updateObjFinish();
    void updateObjGameplayController();

    std::vector<std::shared_ptr<Block>> m_blockList;
    std::vector<std::shared_ptr<Limiter>> m_limiterList;
    std::vector<std::shared_ptr<Bonus>> m_bonusList;
    std::vector<std::shared_ptr<Enemy>> m_enemyList;
    std::vector<std::shared_ptr<LevelTile>> m_levelBackTile;

    sf::Texture m_texPad, m_texToolsPad;
    sf::Texture m_texPlayer, m_texFinishObject, m_texEnemy, m_texBonus;
    sf::Texture m_texIcoMenuBtn;
    sf::Texture m_texDialog, m_texJoystick;

    sf::Texture m_texLevelBg, m_texTile;

    sf::Sprite m_sprLevelBg;
    sf::Sprite m_sprPad1, m_sprPad2, m_sprPad3;

    sf::RectangleShape m_recPauseBG;

    sf::Font m_fontLevel;

    sf::Text m_txtContinue, m_txtQuit, m_txtRestart;
    #if !defined(__ANDROID__)
    sf::Text m_txtDebugInfo;
    #endif

    sf::SoundBuffer sdEnemyDestroy, m_sbHaveHealth, m_sbHurt, m_sbAttack, m_sbLose;
    sf::SoundBuffer m_sbHaveBonus, m_sbHaveLife, m_sbJump;
    sf::SoundBuffer m_sbPlayerWin;

    sf::Sound m_sndEnemyDestroy, m_sndHaveHealth, m_sndHurt, m_sndAttack, m_sndLose;
    sf::Sound m_sndHaveBonus, m_sndHaveLife, m_sndJump;
    sf::Sound m_sndPlayerWin;

    sf::Music m_mscLevel;

    // permanents objects
    Player m_player;
    HUD m_gameHud;
    FinishObject m_finishObject;
    is::GameTime m_gameTime;
    CancelButton m_cancelBt;
    GameKeyData m_gameKey;
    GameDialog m_gameDialog;

    // temporal objects
    std::shared_ptr<PauseOption> m_pauseOption;
    std::shared_ptr<ElectroShock> m_electroShock;
    std::shared_ptr<LevelTitle> m_levelTitle;

    int const CURRENT_LEVEL;
    unsigned int m_levelWidth, m_levelHeight;
    int m_mscLevelVolume;
    int m_playerInvicibilityTime, m_restartTime, m_validationKeyPressedTime;
    float m_timeCancelCollision, m_pauseObjMove;
    bool m_isOnMovingBloc;
    bool m_isPlaying, m_levelStart, m_levelEnd, m_levelCompleted;
    bool m_timeUp, m_countLevelTime;
};

#endif // GAMELEVEL_H
