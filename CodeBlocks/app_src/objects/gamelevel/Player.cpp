#include "Player.h"

Player::Player(is::GameDisplay *scene, bool &timeUp, int &restartTime):
    MainObject(),
    Visibility(),
    Health(4),
    m_scene(scene),
    m_canMove(true),
    m_timeUp(timeUp),
    m_restartTime(restartTime),
    m_vAcc(0.f),
    HSP_NORMAL_ACC(0.15f),
    HSP_MAX(3.5f),
    m_hspAcc(HSP_NORMAL_ACC),
    m_hspLim(HSP_MAX),
    VSP_LIM(9.f),
    VSP_ACC(0.8f),
    VSP_MAX(5.65f),
    VSP_FALL_ACC(0.385f),
    m_playerInvicibilityTime(0),
    m_moveRight(true),
    m_isJumping(false),
    m_onGround(false),
    m_playerIsKO(false),
    m_autoAnim(0.f)
{
    // define collision mask
    m_w = 40;
    m_h = 48;
    m_xOffset = 24.f;
    m_yOffset = 24.f;

    m_isActive = true;

    // initialize collision mask
    updateCollisionMask();
}

void Player::loadResources(sf::Texture &tex)
{
    is::createSprite(tex, m_sprParent, sf::IntRect(0, 0, 32, 32), sf::Vector2f(m_x, m_y), sf::Vector2f(m_xOffset, m_yOffset));
    m_xOffset = 18.f;
}

void Player::step(float const &DELTA_TIME)
{
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      PLAYER IS ACTIVE
//////////////////////////////////////////////////////////////////////////////////////////////////////
    if (m_isActive)
    {
        // counters
        int const detaTime = is::getMSecond(DELTA_TIME);
        if (m_time > 0) m_time -= detaTime; else m_time = 0;

        // reduce player invincibility time
        if (m_playerInvicibilityTime > 0) m_playerInvicibilityTime -= static_cast<int>(is::VALUE_CONVERSION * DELTA_TIME);
        else m_playerInvicibilityTime = 0;

        // move the view if player is active
        if (!getIsKO())
        {
            if (m_x > m_scene->getViewW() / 2.f && m_x < static_cast<float>(m_scene->getSceneWidth() * 32) - m_scene->getViewW() / 2.f)
                m_scene->setViewX(m_x);

            if (m_y > static_cast<float>(m_scene->getSceneHeight() * 32) - m_scene->getViewH() / 2.f)
                m_scene->setViewY(static_cast<float>(m_scene->getSceneHeight() * 32) - m_scene->getViewH() / 2.f);
            else if (m_y > m_scene->getViewH() / 2.f && m_y < static_cast<float>(m_scene->getSceneHeight() * 32) - m_scene->getViewH() / 2.f)
                m_scene->setViewY(m_y);
            else if (m_y < m_scene->getViewH() / 2.f) m_scene->setViewY(m_scene->getViewH() / 2.f);
        }

        // update scene view
        m_scene->setView();

        // We call the GameKeyData object from the SDM container
        auto gameKey = static_cast<is::GameKeyData*>(m_scene->SDMgetObject("GameKeyData"));

        // Take a test to find out if attack key is pressed
        if (gameKey->m_keyBPressed && !gameKey->m_keyBUsed)
        {
            // create object once
            if (m_scene->SDMgetObject("ElectroShock") == nullptr)
            {
                m_scene->GSMplaySound("attack"); // We play this sound
                auto electroShock = std::shared_ptr<ElectroShock>(new ElectroShock(getSpriteX(), getSpriteY()));

                // Add the object to the SDM container
                m_scene->SDMaddSceneObject(electroShock, true, true, "ElectroShock");

                // orientation
                float const _SPEED(4.f);
                if (gameKey->m_keyRightPressed)     electroShock->setHsp(_SPEED);
                else if (gameKey->m_keyLeftPressed) electroShock->setHsp(-_SPEED);
                else if (gameKey->m_keyDownPressed) electroShock->setVsp(_SPEED);
                else if (gameKey->m_keyUpPressed)   electroShock->setVsp(-_SPEED);
            }
            gameKey->m_keyBUsed = true;
        }

        // sprite framing with respect to the position
        if (m_moveRight) m_xOffset = 18.f;
        else if (static_cast<int>(m_xOffset) != 24) m_xOffset = 24.f;

        // horizontal move
        if (gameKey->m_keyRightPressed)
        {
            if (m_hsp < m_hspLim) m_hsp += (m_hspAcc * is::VALUE_CONVERSION) * DELTA_TIME;
            m_moveRight = true;
        }
        else if (gameKey->m_keyLeftPressed)
        {
            if (m_hsp > -m_hspLim) m_hsp -= (m_hspAcc * is::VALUE_CONVERSION) * DELTA_TIME;
            m_moveRight = false;
        }
        else // friction
        {
            if (m_moveRight)
            {
                if (m_hsp > 0.5f) m_hsp -= 0.25f; else m_hsp = 0.f;
            }
            else
            {
                if (m_hsp < -0.5f) m_hsp += 0.25f; else m_hsp = 0.f;
            }
        }

        if (m_vAcc < 0.f) m_time = 0;

        // if player is on ground
        if (m_onGround)
        {
            // make a jump
            if (gameKey->m_keyAPressed && !gameKey->m_keyAUsed)
            {
                m_scene->GSMplaySound("jump"); // We play this sound
                makeJump(VSP_MAX, gameKey->m_keyAUsed);
            }
        }
        else // in air (gravity effect)
        {
            // if player is jumping
            if (m_isJumping)
            {
                // propulsion speed
                if (m_vsp < m_vAcc) m_vAcc -= (VSP_ACC * is::VALUE_CONVERSION) * DELTA_TIME;
                else m_isJumping = false; // cancel the player's propulsion
            }
            else
            {
                if (m_vAcc < VSP_LIM) m_vAcc += (VSP_FALL_ACC * is::VALUE_CONVERSION) * DELTA_TIME;
                else m_vAcc = VSP_LIM;
            }
        }

        // if the player outs at the bottom of the level then he loses
        if (m_y > (static_cast<float>(m_scene->getSceneHeight() * 32) + 8.f)) playerHurt(false);

        // player will lose if the chronometer reaches 00min : 00s : 00
        if (m_timeUp) playerHurt(false);

        // avoid the player to out at the left of the level
        if (m_x < 5.f && m_hsp < 0.f)
        {
            m_x = m_xPrevious;
            m_hsp = 0.f;
        }

        // avoid the player to out at the right of the level
        if (m_x > static_cast<float>(m_scene->getSceneWidth() * 32) - 32.f)
        {
            m_hsp = 0.f;
            m_x = static_cast<float>(m_scene->getSceneWidth() * 32) - 32.f;
        }

        // avoid the player to out at the top of the level
        if (m_y < -64.f)
        {
            m_vAcc = 0.f;
            m_y = 0.f;
        }

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      ANIMATION
//////////////////////////////////////////////////////////////////////////////////////////////////////
        m_yOffset = 24.f;
        m_hspLim = HSP_MAX;

        if (m_onGround)
        {
            // if player is moving
            if (std::abs(m_hsp) > 0.5f)
            {
                m_frame += (0.33f * is::VALUE_CONVERSION) * DELTA_TIME; // image speed
                setFrame(2.f, 5.6f);
            }
            else // animation stand up
            {
                if (m_autoAnim < 32.5f) m_autoAnim += (0.25f * is::VALUE_CONVERSION) * DELTA_TIME;
                else m_autoAnim = 0.f;
                if (m_autoAnim > 30.f) m_frame = 1.f;
                else m_frame = 0.f;
            }
        }
        else // the various animations in the air
        {
            if (m_vAcc < 0.f) m_frame = 6.f; else m_frame = 7.f;
        }

        // update collision mask (position, size, ...)
        updateCollisionMask();

        // update object position
        m_xPrevious = m_x;
        m_yPrevious = m_y;
        if (m_canMove) m_x += (m_hsp * is::VALUE_CONVERSION) * DELTA_TIME;
        m_y += (m_vAcc * is::VALUE_CONVERSION) * DELTA_TIME;
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      IF PLAYER IS NOT ACTIVE
//////////////////////////////////////////////////////////////////////////////////////////////////////
    else
    {
        // Get the player out of the level when he loses
        if (getHealth() == 0 && m_y < (static_cast<float>(m_scene->getSceneHeight() * 32) + 24.f))
        {
            moveDown((2.153f * is::VALUE_CONVERSION) * DELTA_TIME);
        }
        if (m_restartTime > 0) m_restartTime += static_cast<int>(is::VALUE_CONVERSION * DELTA_TIME);
        if (m_restartTime > 30) setIsKO(true);

        m_yOffset = 24.f;

        // animation : stand up
        if (m_health > 0)
        {
            if (m_autoAnim < 32.5f) m_autoAnim += (0.25f * is::VALUE_CONVERSION) * DELTA_TIME;
            else m_autoAnim = 0.f;
            if (m_autoAnim > 30.f)  m_frame = 1.f; else m_frame = 0.f;
        }
        else // when player is KO
        {
            m_frame = 8.f;
            if (static_cast<int>(m_imageXscale)) m_imageAngle += (10.f * is::VALUE_CONVERSION) * DELTA_TIME;
            else m_imageAngle -= (5.f * is::VALUE_CONVERSION) * DELTA_TIME;
        }
    }

    // change the sprite face
    if (m_hsp > 0.f) m_imageXscale = 1.f;
    if (m_hsp < 0.f) m_imageXscale = -1.f;

    // update sprite
    is::setSFMLObjAngle(m_sprParent, m_imageAngle);
    is::setSFMLObjScaleX_Y(m_sprParent, m_imageXscale, m_imageYscale);
    is::setFrame(m_sprParent, m_frame, 5, 48, 48, 48);
    is::setSFMLObjX_Y(m_sprParent, m_x + m_xOffset, m_y + m_yOffset);
}

bool Player::placeMetting(int x, int y, Block* other)
{
    is::Rectangle testRec = this->getMask();

    if (x > 0) testRec.m_left += 20;
    if (x < 0) testRec.m_right -= 20;

    testRec.m_left += x;
    testRec.m_right += x;
    testRec.m_top += y;
    testRec.m_bottom += y;

    testRec.m_left += 2;
    testRec.m_right -= 2;

    bool isCollision = false;

    is::Rectangle otherRectangle = other->getMask();

    if (is::collisionTest(testRec, otherRectangle))
    {
        isCollision = true;
    }
    return isCollision;
}

bool Player::getIsKO() const
{
    return m_playerIsKO;
}

bool Player::getOnGround() const
{
    return m_onGround;
}

bool Player::getMoveRight() const
{
    return m_moveRight;
}

bool Player::playerIsVulnerable() const
{
    return (m_playerInvicibilityTime == 0 && getIsActive());
}

bool Player::getIsJumping() const
{
    return m_isJumping;
}

float Player::getVspAcc() const
{
    return m_vAcc;
}

float Player::getMaxHsp() const
{
    return m_hspLim;
}

float Player::getHspAcc() const
{
    return HSP_NORMAL_ACC;
}

void Player::redefineMaskLR(int val)
{
    m_aabb.m_left += val;
    m_aabb.m_right -= val;
}

void Player::draw(sf::RenderTexture &surface)
{
    if (m_visible)
    {
        if (m_playerInvicibilityTime % 2 == 0) surface.draw(m_sprParent);
    }
}

void Player::setIsJumping(bool val)
{
    m_isJumping = val;
}

void Player::setCanMove(bool val)
{
    m_canMove = val;
}

void Player::setIsKO(bool val)
{
    m_playerIsKO = val;
}

void Player::setVspAcc(float val)
{
    // if the value of the propulsion speed is positive then cancel the jump
    if (val > 0.f && m_isJumping)
    {
        if (m_time > 5) m_time = 4;
        m_isJumping = false;
    }
    m_vAcc = val;
}

void Player::setMoveRight(bool state)
{
    m_moveRight = state;
}

void Player::setOnGround(bool val)
{
    if (static_cast<int>(m_time) == 0) m_onGround = val;
}

void Player::makeJump(float vspLim, bool &_keyState)
{
    m_isJumping = true;
    m_vAcc = 0.f;
    m_vsp = -vspLim; // limit of the jump height
    m_time = 20;
    _keyState = true;
    m_onGround = false;
}

void Player::moveDown(float y)
{
    m_y += y;
}

void Player::playerHurt(bool canContinue)
{
    if (canContinue)
    {
        // If the number of health is greater than 0 he can continue the game otherwise he loses
        if (getHealth() > 1)
        {
            m_scene->GSMplaySound("hurt"); // We play this sound
            m_scene->getGameSystem().useVibrate(60);
            addHealth(-1);
            m_playerInvicibilityTime = 60;
        }
        else
        {
            if (getIsActive())
            {
                m_scene->GSMplaySound("lose"); // We play this sound
                m_scene->getGameSystem().useVibrate(60);
                setHealth(0);
                m_restartTime++;
                setIsActive(false);
            }
        }
    }
    else
    {
        if (getIsActive())
        {
            m_scene->GSMplaySound("lose"); // We play this sound
            m_scene->getGameSystem().useVibrate(60);
            setHealth(0);
            m_restartTime++;
            setIsActive(false);
        }
    }
}

void Player::stopAllSounds(bool val)
{
    auto sndump = m_scene->GSMgetSound("jump"); // Get the sound from the GSM container
    if (val)
    {
        if (is::getSFMLSndState(sndump, sf::Sound::Playing)) sndump->pause();
    }
    else
    {
        if (is::getSFMLSndState(sndump, sf::Sound::Paused)) sndump->play();
    }
}
