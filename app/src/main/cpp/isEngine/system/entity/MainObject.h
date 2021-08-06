/*
  is::Engine (Infinity Solution Engine)
  Copyright (C) 2018-2021 Is Daouda <isdaouda.n@gmail.com>

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

#ifndef MAINOBJECT_H_INCLUDED
#define MAINOBJECT_H_INCLUDED

#include <memory>
#include <list>

#include "../entity/Form.h"
#include "../entity/parents/Name.h"
#include "../function/GameFunction.h"

#if defined(IS_ENGINE_USE_SDM)
#include "parents/Destructible.h"
#include "parents/DepthObject.h"
#include "parents/Visibilty.h"
#endif // defined

namespace is
{
////////////////////////////////////////////////////////////
/// \brief Main Class for all game play objects
////////////////////////////////////////////////////////////
class MainObject : public Name
#if defined(IS_ENGINE_USE_SDM)
                 , public Destructible, public DepthObject, public is::Visibility
#endif // defined
{
public:
    explicit MainObject();
    MainObject(float x, float y);
    MainObject(sf::Sprite &spr, float x = 0.f, float y = 0.f);
    MainObject(sf::Texture &tex, float x, float y, bool center = false);
    virtual ~MainObject();

    /// Return the instance number
    static int instanceNumber;

    #if defined(IS_ENGINE_USE_SDM)
    /// on SDL it allows to blit sprites.
    /// Also prevents the object's sprite from being drawn outside the view (works on SDL and SFML).
    std::string m_SDMblitSprTextureName = "";

    /// lets SDM know if it can call its Step method (update function)
    bool m_SDMcallStep = true;

    /// lets SDM know if it can call its Draw method
    bool m_SDMcallDraw = true;

    /// lets SDM know if it can call its Event method
    bool m_SDMcallEvent = false;

    /// Allows to update object, to overload if necessary
    virtual void step(float const &DELTA_TIME)
    {
        updateCollisionMask();
    }

    /// Allows to use object event
    virtual void event(sf::Event &ev)
    {
        is::showLog("WARNING: MainObject event called in object <" + m_strName + ">! This method must be overloaded!");
    }
    #endif

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

    /// Set image frame
    virtual void setFrame(float val);

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

    /// Set the x, y offset
    virtual void setXYOffset(float x, float y);

    /// Set the x, y offset in relation to parent sprite origin
    virtual void setXYOffset();

    /// Set image scale
    virtual void setImageScaleX_Y(float x, float y);

    /// Set time
    virtual void setTime(float x);

    /// Set alpha
    virtual void setImageAlpha(int val);

    /// Set image index
    virtual void setImageIndex(int val);

    /// Set mask width
    virtual void setMaskW(int val);

    /// Set mask height
    virtual void setMaskH(int val);

    /// Set the size of the Rectangle mask and use it as the object's default mask
    virtual void setRectangleMask(int width, int height);

    /// Set the radius of the Circle mask and use it as the object's default mask
    virtual void setCircleMask(float raduis);

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
    virtual void draw(is::Render &surface);

    /// Draw the collision mask
    virtual void drawMask(is::Render &surface, sf::Color color = sf::Color::Blue);

    /// Return the rectangle (default) mask
    virtual const Rectangle& getMask() const noexcept {return m_aabb;}

    /// Return the circle mask
    virtual const Circle& getCircleMask() const noexcept {return m_circle;}

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
    virtual float distantToObject(MainObject const *other, bool useSpritePosition) const;

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
    virtual float getImageScale() const;

    /// Return the angle
    virtual float getImageAngle() const;

    /// Return x offset
    virtual float getXOffset() const;

    /// Return y offset
    virtual float getYOffset() const;

    /// Return object timing variable
    virtual float getTime() const;

    /// Return x of main sprite
    virtual float getSpriteX() const;

    /// Return y of main sprite
    virtual float getSpriteY() const;

    /// Return the sprite texture width
    virtual int getTextureWidth() const;

    /// Return the sprite texture height
    virtual int getTextureHeight() const;

    /// Return the ID of object (instance number)
    virtual int getInstanceId() const;

    /// Return the width of collision mask
    virtual unsigned int getMaskW() const;

    /// Return the height of collision mask
    virtual unsigned int getMaskH() const;

    /// Return image alpha
    virtual int getImageAlpha() const;

    /// Return image index
    virtual int getImageIndex() const;

    /// Return the width of main sprite
    virtual int getSpriteWidth() const;

    /// Return the height of main sprite
    virtual int getSpriteHeight() const;

    /// Return the x center of main sprite
    virtual int getSpriteCenterX() const;

    /// Return the y center of main sprite
    virtual int getSpriteCenterY() const;

    /// Return the number of sub-images according to the width of the sprite
    virtual int getSpriteNumberSubImage(int subImageWidth) const;

    /// Return the active value
    virtual bool getIsActive() const;

    /// Test collision in comparison with another
    bool placeMetting(int x, int y, MainObject const *other);

    /// Test collision in comparison with another
    bool placeMetting(int x, int y, std::shared_ptr<MainObject> const &other);

    /// Test if object is in view rectangle (vision)
    bool inViewRec(sf::View const &view, bool useTexRec = true);

    /// Return the sprite of object
    virtual sf::Sprite& getSprite();

protected:

    /// Set frame limit
    virtual void setFrameLimit(float frameStart, float frameEnd = -1.f);

    /// Sub function of placeMeting method
    bool placeMettingSubFunction(float x, float y, MainObject const *other) const;

    /// Allows to update sprite when step function is disabled
    void updateSDMsprite();

    float m_x, m_y, m_xStart, m_yStart, m_xPrevious, m_yPrevious;
    float m_speed, m_hsp, m_vsp;
    float m_frameStart, m_frameEnd, m_frame, m_imageXscale, m_imageYscale, m_imageScale, m_imageAngle;
    float m_xOffset, m_yOffset;
    float m_time;
    unsigned int m_w, m_h;
    int m_instanceId, m_imageAlpha, m_imageIndex;
    bool m_isActive, m_isSDMSprite;

    /// Allows to draw collision mask
    bool m_drawMask;
    bool m_centerSpr = false;
    is::Rectangle m_aabb;
    is::Circle m_circle;
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
bool instanceExist(std::unique_ptr<T> const &obj)
{
    return (obj.get() != nullptr);
}

/// Check if instance exists
template<class T>
bool instanceExist(T const *obj)
{
    return (obj != nullptr);
}

/// destroye instance
template<class T>
void instanceDestroy(T *obj)
{
    if (is::instanceExist(obj))
    {
        delete obj;
        obj = 0;
    }
}

/// Functor for compare the x position of objects
class CompareX
{
public:
    bool operator()(std::shared_ptr<MainObject> const &a, std::shared_ptr<MainObject> const &b) const
    {
        float xA = ((is::instanceExist(a)) ? a->getX() : 0.f);
        float xB = ((is::instanceExist(b)) ? b->getX() : 0.f);
        return (xA < xB);
    }
    bool operator()(MainObject const *a, MainObject const *b) const
    {
        float xA = ((is::instanceExist(a)) ? a->getX() : 0.f);
        float xB = ((is::instanceExist(b)) ? b->getX() : 0.f);
        return (xA < xB);
    }
};
bool operator<(const MainObject *a, const MainObject &b);
bool operator<(const MainObject &b, const MainObject *a);
bool operator<(std::shared_ptr<MainObject> const &a, const MainObject &b);
bool operator<(const MainObject &b, std::shared_ptr<MainObject> const &a);

/// Sort object array by x position
template<class T>
void sortObjArrayByX(std::list<std::shared_ptr<T>> &v)
{
    std::sort(v.begin(), v.end(), is::CompareX());
}

#if defined(IS_ENGINE_USE_SDM)
/// Functor for compare the depth of objects
class CompareDepth
{
public:
    bool operator()(std::shared_ptr<MainObject> const &a, std::shared_ptr<MainObject> const &b) const
    {
        int depthA = ((is::instanceExist(a)) ? a->getDepth() : DepthObject::VERY_BIG_DEPTH + 1);
        int depthB = ((is::instanceExist(b)) ? b->getDepth() : DepthObject::VERY_BIG_DEPTH + 1);
        return (depthA > depthB);
    }
};

/// Sort object array by depth
template<class T>
void sortObjArrayByDepth(std::list<std::shared_ptr<T>> &v)
{
    v.sort(is::CompareDepth());
}
#endif // defined
}

#endif // MAINOBJECT_H_INCLUDED
