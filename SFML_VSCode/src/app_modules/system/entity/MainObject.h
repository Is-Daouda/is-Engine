#ifndef MAINOBJECT_H_INCLUDED
#define MAINOBJECT_H_INCLUDED

#include "../entity/Forme.h"
#include "../function/GameFunction.h"

namespace is
{
////////////////////////////////////////////////////////////
/// \brief Main Class for all physiques objects
////////////////////////////////////////////////////////////
class MainObject
{
public:
    MainObject();
    MainObject(float x, float y);
    virtual ~MainObject();

    /// return the instance number
    static int instanceNumber;

    /// check if the object is in view surface
    virtual bool inViewRec(sf::View const &m_view, bool useTexRec = true);

    /// set x initial position
    virtual void setXStart(float x);

    /// set y initial position
    virtual void setYStart(float y);

    /// set x, y initial position
    virtual void setStartPosition(float x, float y);

    /// set x position
    virtual void setX(float x);

    /// set y position
    virtual void setY(float y);

    /// move object on x axis
    virtual void moveX(float x, float const& DELTA_TIME);

    /// move object on y axis
    virtual void moveY(float y, float const& DELTA_TIME);

    /// set the sprite frame (animation)
    virtual void setFrame(sf::Sprite &m_sprite, float frame, int subFrame, int frameSize = 32, int m_recWidth = 32, int m_recHeight = 32);

    /// set x, y position
    virtual void setPosition(float x, float y);

    /// set x, y scale of main sprite
    virtual void setSpriteScale(float x, float y);

    /// update the collision mask
    virtual void updateCollisionMask();

    /// update the collision mask with independent x, y point
    virtual void updateCollisionMask(int x, int y);

    /// update the collision mask by centering it in relation to the position of the object
    virtual void centerCollisionMask(int x, int y);

    /// draw the main sprite of object
    virtual void draw(sf::RenderWindow &app) = 0;

    /// return the rectangle mask
    virtual is::Rectangle getMask() const;

    /// return the x position
    virtual float getX() const;

    /// return the y position
    virtual float getY() const;

    /// return the x initial position
    virtual float getXStart() const;

    /// return the y initial position
    virtual float getYStart() const;

    /// return the distance between this object and point (x, y)
    virtual float distantToPoint(float x, float y) const;

    /// return the distance between this object and another
    virtual float distantToObject(MainObject const *other) const;

    /// return the angle between this object and point (x, y)
    virtual float pointDirection(float x, float y) const;

    /// return the angle between this object and another
    virtual float pointDirection(MainObject const *other) const;

    /// return the angle between this object main sprite and point (x, y)
    virtual float pointDirectionSprite(float x, float y) const;

    /// return the angle between this object main sprite and another object
    virtual float pointDirectionSprite(MainObject const *other) const;

    /// return the ID of object (instance number)
    virtual int getInstanceId() const;

    /// return the width of collision mask
    virtual int getMaskWidth() const;

    /// return the height of collision mask
    virtual int getMaskHeight() const;

    /// return the width of main sprite
    virtual int getSpriteWidth() const;

    /// return the height of main sprite
    virtual int getSpriteHeight() const;

    /// return x of main sprite
    virtual float getSpriteX() const;

    /// return y of main sprite
    virtual float getSpriteY() const;

    /// return the x center of main sprite
    virtual int getSpriteCenterX() const;

    /// return the y center of main sprite
    virtual int getSpriteCenterY() const;

    /// test collision in comparison with another
    virtual bool placeMetting(int x, int y, MainObject const *other);

    /// return the sprite of object
    virtual sf::Sprite getSprite() const;

protected:
    float m_x, m_y, m_xStart, m_yStart;
    int m_w, m_h, m_instanceId;
    is::Rectangle m_aabb;
    sf::Sprite m_sprParent;
};

/// functor for compare the x position of objects
class CompareX
{
public:
    bool operator()(MainObject const *a, MainObject const *b) const;
};
bool operator<(const MainObject *a, const MainObject &b);
bool operator<(const MainObject &b, const MainObject *a);

/// check if instance exists
template<class T>
bool instanceExist(T const *obj)
{
    return (obj != 0);
}

/// check if instance is destroyed
template<class T>
void instanceDestroy(T *obj)
{
    if (is::instanceExist(obj))
    {
        delete obj;
        obj = 0;
    }
}
}

#endif // MAINOBJECT_H_INCLUDED
