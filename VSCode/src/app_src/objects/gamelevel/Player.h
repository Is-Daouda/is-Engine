#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "../../../isEngine/system/entity/MainObject.h"
#include "../../../isEngine/system/entity/Visibilty.h"
#include "../../../isEngine/system/function/GameKeyData.h"
#include "../../gamesystem_ext/GameSystemExtended.h"
#include "Block.h"
#include "Enemy.h"
#include "../parents/Health.h"

class Player : public is::MainObject, public is::Visibility, public Health
{
public:
    Player();

    void loadResources(sf::Texture &tex, sf::SoundBuffer const &sbJump);

    void step(GameSystemExtended &gameSysExt, float const &DELTA_TIME, GameKeyData &gameKey,
              bool canMove, bool &createElectroShock);
    void setIsKO(bool val);
    void setTimeWait(int val);
    void setVspAcc(float val);
    void setMTime(int val);
    void setMoveRight(bool state);
    void setOnGround(bool val);
    void setJumpAfter(bool val);
    void setVerticalMove(bool val);
    void setIsJumping(bool val);
    void makeJump(float vspLim, bool &_keyState);
    void moveDown(float y);
    void stopAllSounds(bool val);
    void redefineMaskLR(int val);
    void draw(sf::RenderTexture &surface);

    bool placeMetting(int x, int y, std::shared_ptr<Block> const &other);
    bool placeMetting(int x, int y, std::shared_ptr<Enemy> const &other);

    bool getIsKO()             const;
    bool getOnGround()         const;
    bool getMoveRight()        const;
    bool getImageFace()        const;
    bool getIsJumping()        const;
    bool getIsHurt()           const;
    bool getVerticalMove()     const;
    bool getJumpAfter()        const;
    float getVspAcc()          const;
    float getMaxHsp()          const;
    float getHspAcc()          const {return HSP_NORMAL_ACC;}
    int getImageSign()         const;
    int getTimeWait()          const;

private:
    float m_vAcc;
    int   m_contactDir;
    float const HSP_NORMAL_ACC, HSP_MAX;
    float m_hspAcc, m_hspLim;
    float const VSP_LIM, VSP_ACC, VSP_MAX, VSP_FALL_ACC;
    int   m_timeWait;
    bool  m_moveRight;
    bool  m_isJumping;
    bool  m_onGround;
    bool  m_playerIsKO;
    bool  m_verticalMove;
    bool  m_jumpAfter;
    float m_autoAnim;

    sf::Sound m_sndJump;
};

#endif // PLAYER_H_INCLUDED
