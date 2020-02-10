#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include "../system/display/GameDisplay.h"
#include "../gameobj/Player.h"
#include "../gameobj/Block.h"
#include "../gameobj/HUD.h"
#include "../gameobj/Bonus.h"
#include "../gameobj/Goal.h"
#include "../gameobj/PauseButton.h"
#include "../gameobj/LevelTile.h"
#include "../level/Level.h"

class GameLevel : public is::GameDisplay
{
public:
    GameLevel(sf::RenderWindow &window, DisplayOption &m_launchOption, GameSystemExtended &gameSysExt, bool &launchAd);
    ~GameLevel();

    void step();
    void draw();

    bool loadResources();

private:
    void updateObjView();
    void joystickController();
    void updateObjPause(const float &DELTA_TIME);
    void updateObjBlockList();
    void updateObjBonusList(float const &DELTA_TIME);
    void updateObjPlayer(float const &DELTA_TIME);
    void updateObjGameplayController(float const &DELTA_TIME);

    std::vector<Block*> m_blockList;
    std::vector<Bonus*> m_bonusList;
    std::vector<LevelTile*> m_levelTile;

    sf::Texture m_texButton, m_texPauseButton, m_texJoystick;
    sf::Texture m_texPlayer, m_texBlock, m_texBonus, m_texGoal;
    sf::Texture m_texHUD;
    sf::Texture m_texTile;
    sf::Sprite m_sprButton[3], m_sprJoystick[2];

    sf::RectangleShape m_recJoystickMask[2], m_recPauseBg;

    sf::Text m_txtContinue, m_txtQuit, m_txtRestart, m_txtAdvice;

    sf::SoundBuffer m_sbHaveBonus, m_sbPlayerWin, m_sbExplosion, m_sbSpeedUp;
    sf::Sound m_sndHaveBonus, m_sndPlayerWin, m_sndExplosion, m_sndSpeedUp;

    Player m_player;
    HUD m_gameHud;
    Goal m_goal;
    PauseButton m_pauseBt;
    GameTime m_gameTime;

    int const CURRENT_LEVEL;
    unsigned int m_levelWidth, m_levelHeight;
    int m_restartTime;
    float m_buttonY;
    bool m_isPlaying, m_levelStart, m_levelEnd, m_levelCompleted;
    bool m_pauseKeyPressed, m_rotationKeyPressed, m_speedKeyPression, m_timeUp;
    bool m_playerExploseSnd; // allow to play sound on time
    bool &m_launchAd;
};

#endif // GAMELEVEL_H
