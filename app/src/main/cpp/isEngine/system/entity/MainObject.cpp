/*
  is::Engine (Infinity Solutions Engine)
  Copyright (C) 2018-2022 Is Daouda <isdaouda.n@gmail.com>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include "MainObject.h"

namespace is
{
int MainObject::instanceNumber = 0;

MainObject::MainObject():
    Name(),
#if defined(IS_ENGINE_USE_SDM)
    Destructible(),
    DepthObject(DepthObject::NORMAL_DEPTH),
    Visibility(),
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
    m_isSDMSprite(false),
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
    Visibility(),
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
    m_isSDMSprite(false),
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
    Visibility(),
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
    m_isSDMSprite(true),
    m_drawMask(false),
    m_sprParent(spr)
{
#if defined(IS_ENGINE_USE_SDM)
    m_SDMcallStep = false;
    m_SDMcallEvent = false;
#endif // defined
    setRectangleMask(spr.getTexture()->getSize().x, spr.getTexture()->getSize().y);
    updateCollisionMask();
    updateSprite();
    instanceNumber++;
    m_instanceId = instanceNumber;
}

MainObject::MainObject(sf::Texture &tex, float x, float y, bool center):
    Name(),
#if defined(IS_ENGINE_USE_SDM)
    Destructible(),
    DepthObject(DepthObject::NORMAL_DEPTH),
#endif // defined
    m_x(x),
    m_y(y),
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
    m_isSDMSprite(true),
    m_drawMask(false)
{
    m_centerSpr = center;
#if defined(IS_ENGINE_USE_SDM)
    m_SDMcallStep = false;
    m_SDMcallEvent = false;
#endif // defined
    setRectangleMask(tex.getSize().x, tex.getSize().y);
    is::createSprite(tex, m_sprParent, sf::Vector2f(m_x, m_y), sf::Vector2f(0.f, 0.f));
    if (!m_centerSpr) updateCollisionMask();
    else
    {
        is::centerSFMLObj(m_sprParent);
        centerCollisionMask(m_x, m_y);
    }
    updateSprite();
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
    updateSDMsprite();
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
    setPosition(x, m_y);
}

void MainObject::setY(float y)
{
    setPosition(m_x, y);
}

void MainObject::moveX(float x)
{
    setPosition(m_x + x, m_y);
}

void MainObject::moveY(float y)
{
    setPosition(m_x, m_y + y);
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
    updateSDMsprite();
}

void MainObject::setFrame(float val)
{
    m_frame = val;
}

void MainObject::setFrameStart(float val)
{
    m_frameStart = val;
}

void MainObject::setFrameEnd(float val)
{
    m_frameEnd = val;
}

void MainObject::setImageXscale(float val)
{
    setImageScaleX_Y(val, m_imageYscale);
}

void MainObject::setImageYscale(float val)
{
    setImageScaleX_Y(m_imageXscale, val);
}

void MainObject::setImageScale(float val)
{
    m_imageScale = val;
    setImageScaleX_Y(m_imageScale, m_imageScale);
}

void MainObject::setImageAngle(float val)
{
    m_imageAngle = val;
    updateSDMsprite();
}

void MainObject::setXOffset(float val)
{
    setXYOffset(val, m_xOffset);
}

void MainObject::setYOffset(float val)
{
    setXYOffset(m_xOffset, val);
}

void MainObject::setXYOffset(float x, float y)
{
    m_xOffset = x;
    m_yOffset = y;
    updateSDMsprite();
}

void MainObject::setXYOffset()
{
    setXYOffset(is::getSFMLObjOriginX(m_sprParent), is::getSFMLObjOriginY(m_sprParent));
}

void MainObject::setImageScaleX_Y(float x, float y)
{
    m_imageXscale = x;
    m_imageYscale = y;
    updateSDMsprite();
}

void MainObject::setTime(float x)
{
    m_time = x;
}

void MainObject::setImageAlpha(int val)
{
    m_imageAlpha = val;
    updateSDMsprite();
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

void MainObject::draw(is::Render &surface)
{
    is::draw(surface, m_sprParent);
    if (m_drawMask) drawMask(surface);
}

void MainObject::drawMask(is::Render &surface, sf::Color color)
{
    // We draw the AABB (rectangle, square) mask only if it has dimensions
    if (m_w > 0 && m_h > 0)
    {
        sf::RectangleShape rec(sf::Vector2f(static_cast<float>(m_w), static_cast<float>(m_h)));
        rec.setOutlineThickness(1.f);
        rec.setFillColor(sf::Color::Transparent);
        rec.setOutlineColor(color);
        is::setSFMLObjX_Y(rec, static_cast<float>(m_aabb.m_left), static_cast<float>(m_aabb.m_top));
        is::draw(surface, rec);
    }
    else if (m_circle.m_raduis > 0.f) // We draw the circle mask only if it has dimensions
    {
        sf::CircleShape circle(m_circle.m_raduis);
        circle.setOutlineThickness(1.f);
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineColor(color);
        is::centerSFMLObj(circle);
        is::setSFMLObjX_Y(circle, m_circle.m_x, m_circle.m_y);
        is::draw(surface, circle);
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

int MainObject::getTextureWidth() const
{
    return is::getSFMLTextureWidth(m_sprParent.getTexture());
}

int MainObject::getTextureHeight() const
{
    return is::getSFMLTextureHeight(m_sprParent.getTexture());
}

int MainObject::getSpriteCenterX() const
{
    return (m_sprParent.getTextureRect().width / 2);
}

int MainObject::getSpriteCenterY() const
{
    return (m_sprParent.getTextureRect().height / 2);
}

int MainObject::getSpriteNumberSubImage(int subImageWidth) const
{
    return (m_sprParent.getTexture()->getSize().x / subImageWidth);
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

void MainObject::updateSDMsprite()
{
    if (m_isSDMSprite)
    {
        if (m_centerSpr) centerCollisionMask(m_x, m_y); else updateCollisionMask();
        updateSprite();
    }
}

bool MainObject::placeMetting(int x, int y, MainObject const *other)
{
    return placeMettingSubFunction(x, y, other);
}

bool MainObject::placeMetting(int x, int y, std::shared_ptr<MainObject> const &other)
{
    return placeMettingSubFunction(x, y, other.get());
}

bool MainObject::inViewRec(sf::View const &view, bool useTexRec)
{
    is::Rectangle testRec;
    if (useTexRec)
    {
        testRec.m_left   = m_x;
        testRec.m_top    = m_y;
        testRec.m_right  = m_x + ((m_sprParent.getGlobalBounds().width  < 1) ? 32 : m_sprParent.getGlobalBounds().width);
        testRec.m_bottom = m_y + ((m_sprParent.getGlobalBounds().height < 1) ? 32 : m_sprParent.getGlobalBounds().height);
    }
    else testRec = this->getMask();

    is::Rectangle viewRec;
    viewRec.m_left   = view.getCenter().x - (view.getSize().x / 2.f);
    viewRec.m_right  = view.getCenter().x + (view.getSize().x / 2.f);
    viewRec.m_top    = view.getCenter().y - (view.getSize().y / 2.f);
    viewRec.m_bottom = view.getCenter().y + (view.getSize().y / 2.f);

    if (is::collisionTest(testRec, viewRec)) return true;
    return false;
}

sf::Sprite& MainObject::getSprite()
{
    return m_sprParent;
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
