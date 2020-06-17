#include "MainObject.h"

namespace is
{
int MainObject::instanceNumber = 0;

MainObject::MainObject():
    m_x(0.f),
    m_y(0.f),
    m_xStart(0.f),
    m_yStart(0.f),
    m_xPrevious(m_x),
    m_yPrevious(m_y),
    m_speed(0.f),
    m_hsp(0.f),
    m_vsp(0.f),
    m_frameStart(0.f),
    m_frameEnd(0.f),
    m_frame(0.f),
    m_imageXscale(1.f),
    m_imageYscale(1.f),
    m_imageScale(1.f),
    m_imageAngle(0.f),
    m_xOffset(0.f),
    m_yOffset(0.f),
    m_time(0.f),
    m_w(32),
    m_h(32),
    m_imageAlpha(255),
    m_imageIndex(0),
    m_isActive(false)
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
    m_xPrevious(m_x),
    m_yPrevious(m_y),
    m_speed(0.f),
    m_hsp(0.f),
    m_vsp(0.f),
    m_frameStart(0.f),
    m_frameEnd(0.f),
    m_frame(0.f),
    m_imageXscale(1.f),
    m_imageYscale(1.f),
    m_imageScale(1.f),
    m_imageAngle(0.f),
    m_xOffset(0.f),
    m_yOffset(0.f),
    m_time(0.f),
    m_w(32),
    m_h(32),
    m_imageAlpha(255),
    m_imageIndex(0),
    m_isActive(false)
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
    m_xPrevious = m_x;
    m_yPrevious = m_y;
    m_x = x;
    m_y = y;
}

void MainObject::setSpriteScale(float x, float y)
{
    is::setSFMLObjScaleX_Y(m_sprParent, x, y);
}

void MainObject::setXStart(float x)
{
    m_xStart = x;
}

void MainObject::setYStart(float y)
{
    m_yStart = y;
}

void MainObject::setXPrevious(float x)
{
    m_xPrevious = x;
}

void MainObject::setYPrevious(float y)
{
    m_yPrevious = y;
}

void MainObject::setStartPosition(float x, float y)
{
    m_xStart = x;
    m_yStart = y;
}

void MainObject::setX(float x)
{
    m_xPrevious = m_x;
    m_x = x;
}

void MainObject::setY(float y)
{
    m_yPrevious = m_y;
    m_y = y;
}

void MainObject::moveX(float x)
{
    m_xPrevious = m_x;
    m_x += x;
}

void MainObject::moveY(float y)
{
    m_yPrevious = m_y;
    m_y += y;
}

void MainObject::setSpeed(float val)
{
    m_speed = val;
}

void MainObject::setHsp(float val)
{
    m_hsp = val;
}

void MainObject::setVsp(float val)
{
    m_vsp = val;
}

void MainObject::setAngularMove(float const &DELTA_TIME, float speed, float angle)
{
    m_x += (is::lengthDirX(speed, angle) * is::VALUE_CONVERSION) * DELTA_TIME;
    m_y -= (is::lengthDirY(speed, angle) * is::VALUE_CONVERSION) * DELTA_TIME;
}

void MainObject::setImageXscale(float val)
{
    m_imageXscale = val;
}

void MainObject::setImageYscale(float val)
{
    m_imageYscale = val;
}

void MainObject::setImageScale(float val)
{
    m_imageScale = val;
}

void MainObject::setImageAngle(float val)
{
    m_imageAngle = val;
}

void MainObject::setXOffset(float val)
{
    m_xOffset = val;
}

void MainObject::setYOffset(float val)
{
    m_yOffset = val;
}

void MainObject::setXYOffset()
{
    m_xOffset = is::getSFMLObjOriginX(m_sprParent);
    m_yOffset = is::getSFMLObjOriginY(m_sprParent);
}

void MainObject::setImageScale(float x, float y)
{
    m_imageXscale = x;
    m_imageYscale = y;
}

void MainObject::setTime(float x)
{
    m_time = x;
}

void MainObject::setImageAlpha(int val)
{
    m_imageAlpha = val;
}

void MainObject::setImageIndex(int val)
{
    m_imageIndex = val;
}

void MainObject::setMaskW(int val)
{
    m_w = val;
}

void MainObject::setMaskH(int val)
{
    m_h = val;
}

void MainObject::setIsActive(bool val)
{
    m_isActive = val;
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

void MainObject::updateSprite()
{
    is::setSFMLObjAlpha(m_sprParent, m_imageAlpha);
    is::setSFMLObjAngle(m_sprParent, m_imageAngle);
    is::setSFMLObjScaleX_Y(m_sprParent, m_imageXscale, m_imageYscale);
    is::setSFMLObjX_Y(m_sprParent, m_x + m_xOffset, m_y + m_yOffset);
}

void MainObject::updateSprite(float x, float y, float angle, int alpha, float xScale, float yScale, float xOffset, float yOffset)
{
    is::setSFMLObjAlpha(m_sprParent, alpha);
    is::setSFMLObjAngle(m_sprParent, angle);
    is::setSFMLObjScaleX_Y(m_sprParent, xScale, yScale);
    is::setSFMLObjX_Y(m_sprParent, x + xOffset, y + yOffset);
}

void MainObject::draw(sf::RenderTexture &surface)
{
    surface.draw(m_sprParent);
}

void MainObject::setFrame(float frameStart, float frameEnd)
{
    if (frameEnd > -1.f)
    {
        if (m_frame > frameEnd) m_frame = frameStart;
        if (m_frame < frameStart)  m_frame = frameStart;
    }
    else m_frame = frameStart;
}

float MainObject::distantToPoint(float x, float y) const
{
   float X = (getX() + getMaskWidth() / 2)  - x;
   float Y = (getY() + getMaskHeight() / 2) - y;
   return sqrt(X * X + Y * Y);
}

float MainObject::distantToObject(std::shared_ptr<MainObject> const &other, bool useSpritePosition) const
{
   float X = ((useSpritePosition) ? getSpriteX() - other->getSpriteX() : (getX() + (getMaskWidth() / 2))  - (other->getX() + (other->getMaskWidth() / 2)));
   float Y = ((useSpritePosition) ? getSpriteY() - other->getSpriteY() : (getY() + (getMaskHeight() / 2)) - (other->getY() + (other->getMaskHeight() / 2)));
   return sqrt(X * X + Y * Y);
}

float MainObject::pointDirection(float x, float y) const
{
    return (is::pointDirection<float>(m_x, m_y, x, y));
}

float MainObject::pointDirection(std::shared_ptr<MainObject> const &other) const
{
    return (is::pointDirection<float>(m_x, m_y, other->getX(), other->getY()));
}

float MainObject::pointDirectionSprite(float x, float y) const
{
    return (is::pointDirection<float>(getSpriteX(), getSpriteY(), x, y));
}

float MainObject::pointDirectionSprite(std::shared_ptr<MainObject> const &other) const
{
    return (is::pointDirection<float>(getSpriteX(), getSpriteY(), other->getSpriteX(), other->getSpriteY()));
}

float MainObject::getSpeed() const
{
    return m_speed;
}

float MainObject::getHsp() const
{
    return m_hsp;
}

float MainObject::getVsp() const
{
    return m_vsp;
}

float MainObject::getFrame() const
{
    return m_frame;
}

float MainObject::getFrameStart() const
{
    return m_frameStart;
}

float MainObject::getFrameEnd() const
{
    return m_frameEnd;
}

float MainObject::getImageXscale() const
{
    return m_imageXscale;
}

float MainObject::getImageYscale() const
{
    return m_imageYscale;
}

float MainObject::getImageScale() const
{
    return m_imageScale;
}

float MainObject::getImageAngle() const
{
    return m_imageAngle;
}

float MainObject::getXOffset() const
{
    return m_xOffset;
}

float MainObject::getYOffset() const
{
    return m_yOffset;
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

float MainObject::getXPrevious() const
{
    return m_xPrevious;
}

float MainObject::getYPrevious() const
{
    return m_yPrevious;
}

float MainObject::getTime() const
{
    return m_time;
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

bool MainObject::getIsActive() const
{
    return m_isActive;
}

int MainObject::getImageAlpha() const
{
    return m_imageAlpha;
}

int MainObject::getImageIndex() const
{
    return m_imageIndex;
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

bool MainObject::placeMetting(int x, int y, std::shared_ptr<MainObject> const &other)
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

bool MainObject::inViewRec(GameDisplay const &app, bool useTexRec)
{
    is::Rectangle testRec;

    if (useTexRec)
    {
        testRec.m_left = m_x;
        testRec.m_top = m_y;
        testRec.m_right = m_x + is::getSFMLObjWidth(m_sprParent);
        testRec.m_bottom = m_y + is::getSFMLObjHeight(m_sprParent);
    }
    else testRec = this->getMask();


    bool isCollision = false;

    is::Rectangle viewRec;
    viewRec.m_left   = app.getViewX() - (app.getViewW() / 2) - 16;
    viewRec.m_right  = app.getViewX() + (app.getViewW() / 2) + 16;
    viewRec.m_top    = app.getViewY() - (app.getViewH() / 2);
    viewRec.m_bottom = app.getViewY() + (app.getViewH() / 2);

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

sf::Sprite& MainObject::getSprite()
{
    return m_sprParent;
}

bool operator<(std::shared_ptr<MainObject> const &a, const MainObject &b)
{
    if (is::instanceExist(a)) return a->getX() < (b.getX() - 460.f);
    else return false;
}

bool operator<(const MainObject &b, std::shared_ptr<MainObject> const &a)
{
    if (is::instanceExist(a)) return (b.getX() + 460.f) < a->getX();
    else return false;
}
}
