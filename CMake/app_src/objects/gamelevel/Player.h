#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "../../../isEngine/system/display/GameDisplay.h"
#include "../../../isEngine/system/entity/MainObject.h"
#include "../../../isEngine/system/entity/parents/Visibilty.h"
#include "../../../isEngine/system/entity/parents/Health.h"
#include "../../../isEngine/system/function/GameKeyData.h"
#include "Block.h"
#include "ElectroShock.h"

class Player : public is::MainObject, public is::Visibility, public is::Health
{
public:
    Player(is::GameDisplay *scene, bool &timeUp, int &restartTime);

    void loadResources(sf::Texture &tex);

    void step(float const &DELTA_TIME);
    void setIsKO(bool val);
    void setVspAcc(float val);
    void setMoveRight(bool state);
    void setOnGround(bool val);
    void setIsJumping(bool val);
    void setCanMove(bool val);
    void makeJump(float vspLim, bool &_keyState);
    void moveDown(float y);
    void playerHurt(bool canContinue = true);
    void stopAllSounds(bool val);
    void redefineMaskLR(int val);
    void draw(sf::RenderTexture &surface);

    bool placeMetting(int x, int y, Block *other);
    bool getIsKO()             const;
    bool getOnGround()         const;
    bool getMoveRight()        const;
    bool getIsJumping()        const;
    bool getIsHurt()           const;
    bool playerIsVulnerable()  const;
    float getVspAcc()          const;
    float getMaxHsp()          const;
    float getHspAcc()          const;

private:
    is::GameDisplay *m_scene;
    bool m_canMove;
    bool &m_timeUp;
    int  &m_restartTime;
    float m_vAcc;
    float const HSP_NORMAL_ACC, HSP_MAX;
    float m_hspAcc, m_hspLim;
    float const VSP_LIM, VSP_ACC, VSP_MAX, VSP_FALL_ACC;
    int   m_playerInvicibilityTime;
    bool  m_moveRight;
    bool  m_isJumping;
    bool  m_onGround;
    bool  m_playerIsKO;
    float m_autoAnim;
};

#endif // PLAYER_H_INCLUDED
