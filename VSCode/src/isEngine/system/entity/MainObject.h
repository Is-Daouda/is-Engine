#ifndef MAINOBJECT_H_INCLUDED
#define MAINOBJECT_H_INCLUDED

#include <memory>

#include "../entity/Forme.h"
#include "../function/GameFunction.h"
#include "../display/GameDisplay.h"

namespace is
{
////////////////////////////////////////////////////////////
/// \brief Main Class for all game play objects
////////////////////////////////////////////////////////////
class MainObject
{
public:
    MainObject();
    MainObject(float x, float y);
    virtual ~MainObject();

    /// Return the instance number
    static int instanceNumber;

    /// Check if the object is in view surface
    virtual bool inViewRec(GameDisplay const &app, bool useTexRec = true);

    /// Set x initial position
    virtual void setXStart(float x);

    /// Set y initial position
    virtual void setYStart(float y);

    /// Set x preview position
    virtual void setXPrevious(float x);

    /// Set y preview position
    virtual void setYPrevious(float y);

    /// Set x, y initial position
    virtual void setStartPosition(float x, float y);

    /// Set x position
    virtual void setX(float x);

    /// Set y position
    virtual void setY(float y);

    /// Move object on x axis
    virtual void moveX(float x);

    /// Move object on y axis
    virtual void moveY(float y);

    /// Set x, y position
    virtual void setPosition(float x, float y);

    /// Set x, y scale of main sprite
    virtual void setSpriteScale(float x, float y);

    /// Set speed
    virtual void setSpeed(float val);

    /// Set horizontal speed
    virtual void setHsp(float val);

    /// Set vertical speed
    virtual void setVsp(float val);

    /// Set angular move
    virtual void setAngularMove(float const &DELTA_TIME, float speed, float angle);

    /// Set the x scale
    virtual void setImageXscale(float val);

    /// Set the y scale
    virtual void setImageYscale(float val);

    /// Set the scale
    virtual void setImageScale(float val);

    /// Set the angle
    virtual void setImageAngle(float val);

    /// Set the x offset
    virtual void setXOffset(float val);

    /// Set the y offset
    virtual void setYOffset(float val);

    /// Set the x, y offset in relation to parent sprite origin
    virtual void setXYOffset();

    /// Set image scale
    virtual void setImageScale(float x, float y);

    /// Set time
    void setTime(float x);

    /// Set alpha
    virtual void setImageAlpha(int val);

    /// Set image index
    virtual void setImageIndex(int val);

    /// Set mask w
    virtual void setMaskW(int val);

    /// Set mask h
    virtual void setMaskH(int val);

    /// Set active
    virtual void setIsActive(bool val);

    /// Update the collision mask
    virtual void updateCollisionMask();

    /// Update the collision mask with independent x, y point
    virtual void updateCollisionMask(int x, int y);

    /// Update the collision mask by centering it in relation to the position of the object
    virtual void centerCollisionMask(int x, int y);

    /// Update object main sprite
    virtual void updateSprite();

    /// Update object main sprite with external parameter
    virtual void updateSprite(float x, float y, float angle = 0.f, int alpha = 255, float xScale = 1.f, float yScale = 1.f, float xOffset = 0.f, float yOffset = 0.f);

    /// Draw the main sprite of object
    virtual void draw(sf::RenderTexture &surface);

    /// Return the rectangle mask
    virtual is::Rectangle getMask() const;

    /// Return the x position
    virtual float getX() const;

    /// Return the y position
    virtual float getY() const;

    /// Return the x initial position
    virtual float getXStart() const;

    /// Return the y initial position
    virtual float getYStart() const;

    /// Return the x previous position
    virtual float getXPrevious() const;

    /// Return the y previous position
    virtual float getYPrevious() const;

    /// Return the distance between this object and point (x, y)
    virtual float distantToPoint(float x, float y) const;

    /// Return the distance between this object and another
    virtual float distantToObject(std::shared_ptr<MainObject> const &other, bool useSpritePosition) const;

    /// Return the angle between this object and point (x, y)
    virtual float pointDirection(float x, float y) const;

    /// Return the angle between this object and another
    virtual float pointDirection(std::shared_ptr<MainObject> const &other) const;

    /// Return the angle between this object main sprite and point (x, y)
    virtual float pointDirectionSprite(float x, float y) const;

    /// Return the angle between this object main sprite and another object
    virtual float pointDirectionSprite(std::shared_ptr<MainObject> const &other) const;

    /// Return the speed
    virtual float getSpeed() const;

    /// Return the horizontal speed
    virtual float getHsp() const;

    /// Return the vertical speed
    virtual float getVsp() const;

    /// Return frame
    virtual float getFrame() const;

    /// Return frame start
    virtual float getFrameStart() const;

    /// Return frame end
    virtual float getFrameEnd() const;

    /// Return the x scale
    virtual float getImageXscale() const;

    /// Return the y scale
    virtual float getImageYscale() const;

    /// Return the x scale
    float getImageScale() const;

    /// Return the angle
    virtual float getImageAngle() const;

    /// Return x offset
    virtual float getXOffset() const;

    /// Return y offset
    virtual float getYOffset() const;

    /// Return object timing variable
    virtual float getTime() const;

    /// Return the ID of object (instance number)
    virtual int getInstanceId() const;

    /// Return the width of collision mask
    virtual int getMaskWidth() const;

    /// Return the height of collision mask
    virtual int getMaskHeight() const;

    /// Return the active value
    virtual bool getIsActive() const;

    /// Return image alpha
    virtual int getImageAlpha() const;

    /// Return image index
    virtual int getImageIndex() const;

    /// Return the width of main sprite
    virtual int getSpriteWidth() const;

    /// Return the height of main sprite
    virtual int getSpriteHeight() const;

    /// Return x of main sprite
    virtual float getSpriteX() const;

    /// Return y of main sprite
    virtual float getSpriteY() const;

    /// Return the x center of main sprite
    virtual int getSpriteCenterX() const;

    /// Return the y center of main sprite
    virtual int getSpriteCenterY() const;

    /// Test collision in comparison with another
    virtual bool placeMetting(int x, int y, MainObject const *other);

    /// Test collision in comparison with another
    virtual bool placeMetting(int x, int y, std::shared_ptr<MainObject> const &other);

    /// Return the sprite of object
    virtual sf::Sprite& getSprite();

protected:
    /// Set frame limit
    virtual void setFrame(float frameStart, float frameEnd = -1.f);

    float m_x, m_y, m_xStart, m_yStart, m_xPrevious, m_yPrevious;
    float m_speed, m_hsp, m_vsp;
    float m_frameStart, m_frameEnd, m_frame, m_imageXscale, m_imageYscale, m_imageScale, m_imageAngle;
    float m_xOffset, m_yOffset;
    float m_time;
    int m_w, m_h, m_instanceId, m_imageAlpha, m_imageIndex;
    bool m_isActive;
    is::Rectangle m_aabb;
    sf::Sprite m_sprParent;
};

/// Check if instance exists
template<class T>
bool instanceExist(std::shared_ptr<T> const &obj)
{
    return (obj.get() != nullptr);
}

/// Check if instance exists
template<class T>
bool instanceExist(T const *obj)
{
    return (obj != nullptr);
}

/// Functor for compare the x position of objects
class CompareX
{
public:
    bool operator()(std::shared_ptr<MainObject> const &a, std::shared_ptr<MainObject> const &b) const
    {
        if (is::instanceExist(a) && is::instanceExist(b)) return (a->getX() < b->getX());
        return false;
    }
};

/// Sort object array
template<class T>
void sortObjArray(std::vector<std::shared_ptr<T>> &v)
{
    std::sort(v.begin(), v.end(), is::CompareX());
}

bool operator<(std::shared_ptr<MainObject> const &a, const MainObject &b);
bool operator<(const MainObject &b, std::shared_ptr<MainObject> const &a);
}

#endif // MAINOBJECT_H_INCLUDED
