#include "MainObject.h"

namespace is
{
int MainObject::instanceNumber = 0;

MainObject::MainObject():
    Name(),
    #if defined(IS_ENGINE_USE_SDM)
    Destructible(),
    DepthObject(DepthObject::NORMAL_DEPTH),
    #endif // defined
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
    m_isActive(false),
    m_drawMask(false)
{
    updateCollisionMask();
    instanceNumber++;
    m_instanceId = instanceNumber;
}

MainObject::MainObject(float x, float y):
    Name(),
    #if defined(IS_ENGINE_USE_SDM)
    Destructible(),
    DepthObject(DepthObject::NORMAL_DEPTH),
    #endif // defined
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
    m_isActive(false),
    m_drawMask(false)
{
    updateCollisionMask();
    instanceNumber++;
    m_instanceId = instanceNumber;
}

MainObject::MainObject(sf::Sprite &spr, float x, float y):
    Name(),
    #if defined(IS_ENGINE_USE_SDM)
    Destructible(),
    DepthObject(DepthObject::NORMAL_DEPTH),
    #endif // defined
    m_x((static_cast<int>(x) == 0) ? x : spr.getPosition().x),
    m_y((static_cast<int>(y) == 0) ? y : spr.getPosition().y),
    m_xStart(m_x),
    m_yStart(m_y),
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
    m_isActive(false),
    m_drawMask(false),
    m_sprParent(spr)
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

void MainObject::setFrame(float val)
{
    m_frame = val;
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

void MainObject::setXYOffset(float x, float y)
{
    m_xOffset = x;
    m_yOffset = y;
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

void MainObject::setRectangleMask(int width, int height)
{
    m_w = width;
    m_h = height;
    m_circle.m_raduis = 0.f;
    updateCollisionMask();
}

void MainObject::setCircleMask(float raduis)
{
    m_circle.m_raduis = raduis;
    m_w = 0;
    m_h = 0;
    updateCollisionMask();
}

void MainObject::setIsActive(bool val)
{
    m_isActive = val;
}

void MainObject::updateCollisionMask()
{
    if (m_w > 0 && m_h > 0)
    {
        m_aabb.m_left   = static_cast<int>(m_x);
        m_aabb.m_top    = static_cast<int>(m_y);
        m_aabb.m_right  = static_cast<int>(m_x) + m_w;
        m_aabb.m_bottom = static_cast<int>(m_y) + m_h;
    }
    else {m_circle.m_x = m_x; m_circle.m_y = m_y;}
}

void MainObject::updateCollisionMask(int x, int y)
{
    if (m_w > 0 && m_h > 0)
    {
        m_aabb.m_left   = static_cast<int>(x);
        m_aabb.m_top    = static_cast<int>(y);
        m_aabb.m_right  = static_cast<int>(x) + m_w;
        m_aabb.m_bottom = static_cast<int>(y) + m_h;
    }
    else {m_circle.m_x = x; m_circle.m_y = y;}
}

void MainObject::centerCollisionMask(int x, int y)
{
    if (m_w > 0 && m_h > 0)
    {
        m_aabb.m_left   = static_cast<int>(x - m_w / 2.f);
        m_aabb.m_top    = static_cast<int>(y - m_h / 2.f);
        m_aabb.m_right  = static_cast<int>(x + m_w / 2.f);
        m_aabb.m_bottom = static_cast<int>(y + m_h / 2.f);
    }
    else {m_circle.m_x = x; m_circle.m_y = y;}
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
    updateSprite();
    surface.draw(m_sprParent);
    if (m_drawMask) drawMask(surface);
}

void MainObject::drawMask(sf::RenderTexture &surface, sf::Color color)
{
    // We draw the AABB (rectangle, square) mask only if it has dimensions
    if (m_w > 0 && m_h > 0)
    {
        sf::RectangleShape rec({static_cast<float>(m_w), static_cast<float>(m_h)});
        rec.setOutlineThickness(1.f);
        rec.setFillColor(sf::Color::Transparent);
        rec.setOutlineColor(color);
        rec.setPosition({static_cast<float>(m_aabb.m_left), static_cast<float>(m_aabb.m_top)});
        surface.draw(rec);
    }
    else if (m_circle.m_raduis > 0.f) // We draw the circle mask only if it has dimensions
    {
        sf::CircleShape circle(m_circle.m_raduis);
        circle.setOutlineThickness(1.f);
        circle.setFillColor(sf::Color::Transparent);
        is::centerSFMLObj(circle);
        circle.setOutlineColor(color);
        circle.setPosition({m_circle.m_x, m_circle.m_y});
        surface.draw(circle);
    }
}

void MainObject::setFrameLimit(float frameStart, float frameEnd)
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
   float X = (getX() + getMaskW() / 2)  - x;
   float Y = (getY() + getMaskH() / 2) - y;
   return sqrt(X * X + Y * Y);
}

float MainObject::distantToObject(MainObject const *other, bool useSpritePosition) const
{
   float X = ((useSpritePosition) ? getSpriteX() - other->getSpriteX() : (getX() + (getMaskW() / 2))  - (other->getX() + (other->getMaskW() / 2)));
   float Y = ((useSpritePosition) ? getSpriteY() - other->getSpriteY() : (getY() + (getMaskH() / 2)) - (other->getY() + (other->getMaskH() / 2)));
   return sqrt(X * X + Y * Y);
}

float MainObject::distantToObject(std::shared_ptr<MainObject> const &other, bool useSpritePosition) const
{
   float X = ((useSpritePosition) ? getSpriteX() - other->getSpriteX() : (getX() + (getMaskW() / 2))  - (other->getX() + (other->getMaskW() / 2)));
   float Y = ((useSpritePosition) ? getSpriteY() - other->getSpriteY() : (getY() + (getMaskH() / 2)) - (other->getY() + (other->getMaskH() / 2)));
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

unsigned int MainObject::getMaskW() const
{
    return m_w;
}

unsigned int MainObject::getMaskH() const
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

bool MainObject::placeMettingSubFunction(float x, float y, MainObject const *other) const
{
    is::Rectangle testRec = this->getMask();
    testRec.m_left += x;
    testRec.m_right += x;
    testRec.m_top += y;
    testRec.m_bottom += y;
    is::Circle testCircle = this->getCircleMask();
    testCircle.m_x += x;
    testCircle.m_y += y;

    is::Rectangle otherRectangle = other->getMask();
    is::Circle otherCircle = other->getCircleMask();

    if (m_w > 0 && m_h > 0 && other->getMaskW() > 0 && other->getMaskH() > 0)
    {
        return (is::collisionTest(testRec, otherRectangle));
    }
    else if ((m_w == 0 || m_h == 0) && other->getMaskW() > 0 && other->getMaskH() > 0)
    {
        return (is::collisionTest(testCircle, otherRectangle));
    }
    else if ((m_w > 0 && m_h > 0) && (other->getMaskW() == 0 || other->getMaskH() == 0))
    {
        return (is::collisionTest(testRec, otherCircle));
    }
    else if ((m_w == 0 || m_h == 0) && testCircle.m_raduis > 0.f &&
             (other->getMaskW() == 0 || other->getMaskH() == 0) && otherCircle.m_raduis > 0.f)
    {
        return (is::collisionTest(testCircle, otherCircle));
    }
    else
    {
        is::showLog("ERROR: Badly defined collision masks between these objects: <" + m_strName +
                    "> & <" + other->getName() + ">", true);
    }
    return false;
}

bool MainObject::placeMetting(int x, int y, MainObject const *other)
{
    return placeMettingSubFunction(x, y, other);
}

bool MainObject::placeMetting(int x, int y, std::shared_ptr<MainObject> const &other)
{
    return placeMettingSubFunction(x, y, other.get());
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
