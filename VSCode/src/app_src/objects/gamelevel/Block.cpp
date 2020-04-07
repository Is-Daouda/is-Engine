#include "Block.h"

Block::Block(BlockType type, float x, float y, sf::Texture *tex):
    MainObject(x, y),
    m_sprOrigin(16.f),
    m_type(type),
    m_textureExiste((tex == 0) ? false : true),
    m_changeDir(false),
    m_moveHorizontal(false),
    m_moveVertical(false)
{
    m_isActive = true;
    m_time = 20.f;

    // define collision mask
    m_w = 32;
    m_h = 32;

    // load texture if it exists
    switch (type)
    {
        case Block::BlockType::BLOCK_MOVE_HORIZ:
            is::createSprite(*tex, m_sprParent, sf::IntRect(0, 64, 64, 32), sf::Vector2f(m_x, m_y),
                             sf::Vector2f(0.f, 0.f), false, false);
            m_w = 64;
            m_speed = -1.f;
            m_sprOrigin = 0.f;
        break;

        case Block::BlockType::BLOCK_MOVE_VERTI:
            is::createSprite(*tex, m_sprParent, sf::IntRect(64, 64, 64, 32), sf::Vector2f(m_x, m_y),
                             sf::Vector2f(0.f, 0.f), false, false);
            m_w = 64;
            m_speed = -1.f;
            m_sprOrigin = 0.f;
        break;

        default: break;
    }

    updateCollisionMask();
}

Block::~Block()
{
}

void Block::step(float const& DELTA_TIME, bool isInView)
{
    if (m_isActive)
    {
        if (m_type == Block::BlockType::BLOCK_MOVE_HORIZ)
        {
            if (m_x > m_xStart && m_changeDir)
            {
                m_changeDir = false;
                m_speed = -m_speed;
            }
            m_x += ((m_speed * is::VALUE_CONVERSION) * DELTA_TIME);
        }

        if (m_type == Block::BlockType::BLOCK_MOVE_VERTI)
        {
            if (m_y > m_yStart && m_changeDir)
            {
                m_changeDir = false;
                m_speed = -m_speed;
            }
            m_y += ((m_speed * is::VALUE_CONVERSION) * DELTA_TIME);
        }

        if (is::isIn(2, m_type, BLOCK_MOVE_VERTI, BLOCK_MOVE_HORIZ))
        {
            is::setSFMLObjX_Y(m_sprParent, m_x + m_sprOrigin, (m_y + m_sprOrigin));
        }

        updateCollisionMask();
    }
}

void Block::setMoveHorizontal(bool val)
{
    m_moveHorizontal = val;
}

void Block::setMoveVertical(bool val)
{
    m_moveVertical = val;
}

void Block::setChangeDir(bool val)
{
    m_changeDir = val;
}

bool Block::getChangeDir() const
{
    return m_changeDir;
}

bool Block::getMoveHorizontal() const
{
    return m_moveHorizontal;
}

bool Block::getMoveVertical() const
{
    return m_moveVertical;
}

bool Block::hasTexture() const
{
    return m_textureExiste;
}

Block::BlockType Block::getType() const
{
    return m_type;
}

void Block::draw(sf::RenderTexture &surface)
{
    surface.draw(m_sprParent);
}
