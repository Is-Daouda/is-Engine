#include "Player.h"

Player::Player():
    MainObject(),
    ObjectActivity(),
    m_rotation(90.f),
    m_speed(0.f),
    m_angle(0.f),
    m_imageAngle(0.f),
    m_frame(0.f),
    MAX_SPEED(4.f),
    m_rotationRight(false),
    m_hurt(false)
{
    // define mask collision size
    m_w = 32;
    m_h = 32;

    // update collision mask
    updateCollisionMask();
}

void Player::loadResources(sf::Texture &m_tex)
{
    is::createSprite(m_tex, m_sprParent, sf::IntRect(0, 0, 48, 48), sf::Vector2f(m_x, m_y), sf::Vector2f(24.f, 24.f));
}

void Player::step(float const &DELTA_TIME, bool &leftJoystickPressed, bool &rigthJoystickPressed)
{
    if (m_active)
    {
        if (!m_hurt)
        {
            // if key is pressed do this action
            if (leftJoystickPressed)
            {
                if (m_rotationRight) m_rotation -= (5.f * is::VALUE_CONVERSION) * DELTA_TIME;
                else m_rotation += (5.f * is::VALUE_CONVERSION) * DELTA_TIME;
                m_imageAngle = -m_rotation + 90.f;
                if (std::fabs(m_rotation) > 360.f) m_rotation = 0.f;
            }
            if (rigthJoystickPressed)
            {
                m_frame += (0.4f * is::VALUE_CONVERSION) * DELTA_TIME; // image speed animation
                if (m_frame > 2.6f) m_frame = 0.f;
                m_angle = m_rotation;
                if (m_speed < MAX_SPEED) m_speed += (0.09f * is::VALUE_CONVERSION) * DELTA_TIME;
            }
            else
            {
                m_frame = 0.f;
                if (m_speed > 0.f) m_speed -= (0.2f * is::VALUE_CONVERSION) * DELTA_TIME;
                else m_speed = 0.f;
            }
        }
        else
        {
            m_frame += (0.4f * is::VALUE_CONVERSION) * DELTA_TIME; // image speed animation
            if (m_frame < 2.6f) m_frame = 3.f;
            if (m_frame > 7.6f) m_frame = 3.f;
            m_speed = 0.f;
        }

        // update collision mask in relation position
        updateCollisionMask(m_x - 24, m_y - 24);
        m_x += (is::lengthDirX(m_speed, m_angle) * is::VALUE_CONVERSION) * DELTA_TIME;
        m_y -= (is::lengthDirY(m_speed, m_angle) * is::VALUE_CONVERSION) * DELTA_TIME;
    }

    // update sprite
    is::setSFMLObjAngle(m_sprParent, m_imageAngle);

    // set sprite image index
    setFrame(m_sprParent, m_frame, 4, 48, 48, 48);
    is::setSFMLObjX_Y(m_sprParent, m_x, m_y);
}

void Player::draw(sf::RenderWindow &app)
{
    app.draw(m_sprParent);
}

void Player::setAngle(float val)
{
    m_angle = val;
}

void Player::setSpeed(float val)
{
    m_speed = val;
}

void Player::setRotationRight(bool val)
{
    m_rotationRight = val;
}

void Player::setHurt(bool val)
{
    m_hurt = val;
}

bool Player::getHurt() const
{
    return m_hurt;
}

bool Player::getRotationRight() const
{
    return m_rotationRight;
}

float Player::getImageAngle() const
{
    return m_imageAngle;
}

float Player::getAngle() const
{
    return m_angle;
}

float Player::getSpeed() const
{
    return m_speed;
}
