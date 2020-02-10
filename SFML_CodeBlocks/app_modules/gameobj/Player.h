#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "../core/GameSystemExtended.h"
#include "../system/entity/MainObject.h"
#include "../system/entity/ObjectActivity.h"
#include "Block.h"

class Player : public is::MainObject, public is::ObjectActivity
{
public:
    Player();

    void loadResources(sf::Texture &m_tex);
    void step(float const &DELTA_TIME, bool &leftJoystickPressed, bool &rigthJoystickPressed);
    void draw(sf::RenderWindow &app);
    void setAngle(float val);
    void setSpeed(float val);
    void setHurt(bool val);
    void setRotationRight(bool val);

    float getAngle()        const;
    float getSpeed()        const;
    float getImageAngle()   const;
    bool getHurt()          const;
    bool getRotationRight() const;

private:
    float m_rotation, m_speed, m_angle, m_imageAngle;
    float m_frame;
    float const MAX_SPEED;
    bool m_rotationRight, m_hurt;
};

#endif // PLAYER_H_INCLUDED
