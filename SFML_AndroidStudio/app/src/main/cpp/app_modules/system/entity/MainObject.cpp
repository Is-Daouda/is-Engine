#include "MainObject.h"

namespace is
{
int MainObject::instanceNumber = 0;

MainObject::MainObject():
    m_x(0.f),
    m_y(0.f),
    m_xStart(0.f),
    m_yStart(0.f),
    m_w(32),
    m_h(32)
{
    updateCollisionMask();
    instanceNumber++;
    m_instanceId = instanceNumber;
}

MainObject::MainObject(float x, float y):
    m_x(x),
    m_y(y),
    m_xStart(x),
    m_yStart(y),
    m_w(32),
    m_h(32)
{
    updateCollisionMask();
    instanceNumber++;
    m_instanceId = instanceNumber;
}

MainObject::~MainObject()
{
    instanceNumber--;
}

void MainObject::setPosition(float x, float y)
{
    m_x = x;
    m_y = y;
}

void MainObject::setSpriteScale(float x, float y)
{
    m_sprParent.setScale(x, y);
}

void MainObject::setXStart(float x)
{
    m_xStart = x;
}

void MainObject::setYStart(float y)
{
    m_yStart = y;
}

void MainObject::setStartPosition(float x, float y)
{
    m_xStart = x;
    m_yStart = y;
}

void MainObject::setX(float x)
{
    m_x = x;
}

void MainObject::setY(float y)
{
    m_y = y;
}

void MainObject::moveX(float x, float const& DELTA_TIME)
{
    m_x += x * DELTA_TIME;
}

void MainObject::moveY(float y, float const& DELTA_TIME)
{
    m_y += y * DELTA_TIME;
}

void MainObject::setFrame(sf::Sprite &m_sprite, float frame, int subFrame, int frameSize, int m_recWidth, int m_recHeight)
{
    // description of the image decoupage algorithm
    // be << frame >> number of the image to get (to have it start counting images from 0 to X)
    // either << subFrame >> number of images on one line
    // be << frameLineIndex >> number of the line corresponding to the image
    // (frame / subFrame) returns the number of times there is << frame >> in << subFrame >> to determine the number of the line of the sprite
    // 32 * (frame - (subFrame * frameLineIndex)) returns the position (number) of the sprite on the X axis can return the value 0 (1st sprite on the line)
    // when the value of << frame >> exceeds the number of sprite on the X axis (the value of << subFrame >>) then we are on a new line
    // (32 * frameLineIndex) gives the position of the image on the Y axis its value varies according to the << frame >>
    // example: 32 * frameLineIndex = 1 when frame > subFrame; 32 * frameLineIndex = 2 when frame > subFrame * 2; ...
    int frameLineIndex = (frame / subFrame);
    m_sprite.setTextureRect(sf::IntRect(frameSize * (static_cast<int>(frame) - (subFrame * frameLineIndex)), frameSize * frameLineIndex, m_recWidth, m_recHeight));
}

void MainObject::updateCollisionMask()
{
    m_aabb.m_left   = static_cast<int>(m_x);
    m_aabb.m_top    = static_cast<int>(m_y);
    m_aabb.m_right  = static_cast<int>(m_x) + m_w;
    m_aabb.m_bottom = static_cast<int>(m_y) + m_h;
}

void MainObject::updateCollisionMask(int x, int y)
{
    m_aabb.m_left   = static_cast<int>(x);
    m_aabb.m_top    = static_cast<int>(y);
    m_aabb.m_right  = static_cast<int>(x) + m_w;
    m_aabb.m_bottom = static_cast<int>(y) + m_h;
}

void MainObject::centerCollisionMask(int x, int y)
{
    // center the mask by reducing the edge towards the inside
    m_aabb.m_left   = static_cast<int>(m_x + x);
    m_aabb.m_top    = static_cast<int>(m_y + y);
    m_aabb.m_right  = static_cast<int>(m_x - x) + m_w;
    m_aabb.m_bottom = static_cast<int>(m_y - y) + m_h;
}

float MainObject::distantToPoint(float x, float y) const
{
   float X = (getX() + getMaskWidth() / 2)  - x;
   float Y = (getY() + getMaskHeight() / 2) - y;
   return sqrt(X * X + Y * Y);
}

float MainObject::distantToObject(MainObject const *other) const
{
   float X = (getX() + (getMaskWidth() / 2))  - (other->getX() + (other->getMaskWidth() / 2));
   float Y = (getY() + (getMaskHeight() / 2)) - (other->getY() + (other->getMaskHeight() / 2));
   return sqrt(X * X + Y * Y);
}

float MainObject::pointDirection(float x, float y) const
{
    return (is::pointDirection<float>(m_x, m_y, x, y));
}

float MainObject::pointDirection(MainObject const *other) const
{
    return (is::pointDirection<float>(m_x, m_y, other->getX(), other->getY()));
}

float MainObject::pointDirectionSprite(float x, float y) const
{
    return (is::pointDirection<float>(getSpriteX(), getSpriteY(), x, y));
}

float MainObject::pointDirectionSprite(MainObject const *other) const
{
    return (is::pointDirection<float>(getSpriteX(), getSpriteY(), other->getSpriteX(), other->getSpriteY()));
}

float MainObject::getX() const
{
    return m_x;
}

float MainObject::getY() const
{
    return m_y;
}

float MainObject::getXStart() const
{
    return m_xStart;
}

float MainObject::getYStart() const
{
    return m_yStart;
}

int MainObject::getInstanceId() const
{
    return m_instanceId;
}

int MainObject::getMaskWidth() const
{
    return m_w;
}

int MainObject::getMaskHeight() const
{
    return m_h;
}

int MainObject::getSpriteWidth() const
{
    return m_sprParent.getTextureRect().width;
}

int MainObject::getSpriteHeight() const
{
    return m_sprParent.getTextureRect().height;
}

float MainObject::getSpriteX() const
{
    return m_sprParent.getPosition().x;
}

float MainObject::getSpriteY() const
{
    return m_sprParent.getPosition().y;
}

int MainObject::getSpriteCenterX() const
{
    return (m_sprParent.getTextureRect().width / 2);
}

int MainObject::getSpriteCenterY() const
{
    return (m_sprParent.getTextureRect().height / 2);
}

bool MainObject::placeMetting(int x, int y, MainObject const *other)
{
    is::Rectangle testRec = this->getMask();

    testRec.m_left += x;
    testRec.m_right += x;
    testRec.m_top += y;
    testRec.m_bottom += y;

    bool isCollision = false;

    is::Rectangle otherRectangle = other->getMask();

    if (is::collisionTest(testRec, otherRectangle))
    {
        isCollision = true;
    }
    return isCollision;
}

bool MainObject::inViewRec(sf::View const &m_view, bool useTexRec)
{
    is::Rectangle testRec;

    if (useTexRec)
    {
        testRec.m_left = m_x;
        testRec.m_top = m_y;
        testRec.m_right = m_x + m_sprParent.getGlobalBounds().width;
        testRec.m_bottom = m_y + m_sprParent.getGlobalBounds().height;
    }
    else testRec = this->getMask();


    bool isCollision = false;

    is::Rectangle viewRec;
    viewRec.m_left   = m_view.getCenter().x - 320.f;
    viewRec.m_right  = m_view.getCenter().x + 320.f;
    viewRec.m_top    = m_view.getCenter().y - 240.f;
    viewRec.m_bottom = m_view.getCenter().y + 240.f;

    if (is::collisionTest(testRec, viewRec))
    {
        isCollision = true;
    }
    return isCollision;
}

Rectangle MainObject::getMask() const
{
    return m_aabb;
}

sf::Sprite MainObject::getSprite() const
{
    return m_sprParent;
}

bool CompareX::operator()(MainObject const *a, MainObject const *b) const
{
    return (a->getX() < b->getX());
}

bool operator<(const MainObject *a, const MainObject &b)
{
    if (is::instanceExist(a)) return a->getX()  < (b.getX() - 460.f);
    else return false;
}

bool operator<(const MainObject &b, const MainObject *a)
{
    if (is::instanceExist(a)) return (b.getX() + 460.f) < a->getX();
    else return false;
}
}
