#ifndef GAME_FONCTION_H_INCLUDED
#define GAME_FONCTION_H_INCLUDED

#include <cmath>
#include <ctime>
#include <sstream>
#include <SFML/Graphics.hpp>

/// allow to browse object container (std::vector, ...)
#define WITH(_SIZE) for(unsigned int _I = 0; _I < _SIZE; ++_I)

#include "../entity/Forme.h"
#include "../function/GameSystem.h"

#if defined(__ANDROID__)
// These headers are only needed for direct NDK/JDK interaction
#include <jni.h>
#include <android/native_activity.h>
#include <android/log.h>

// Since we want to get the native activity from SFML, we'll have to use an
// extra header here:
#include <SFML/System/NativeActivity.hpp>
#endif // defined

namespace is
{
/// game execution timing variables
static float const MAX_CLOCK_TIME(0.018f);
static float const VALUE_CONVERSION(65.f);

#if !defined(__ANDROID__)
static float const M_PI(3.14);
#endif // defined

/// return game execution time in millisecond
template <typename T>
T getMSecond(float const &DELTA_TIME)
{
    return (DELTA_TIME * (1.538f * VALUE_CONVERSION));
}

/// convert number to string (Note : include "sstream" header)
template <class T>
std::string numToStr(T val)
{
    std::ostringstream s;
    s << val;
    return s.str();
}

/// draw zero behind a number (0 to 9)
template <class T>
std::string writeZero(T val)
{
    std::string str;
    if (val < 10) str = "0" + is::numToStr(val);
    else str = is::numToStr(val);
    return str;
}

/// show log message
void showLog(std::string str);

/// test many values in comparison with a variable
template <typename T>
bool isIn(unsigned short valNumber, T const var, T x1, T x2, T x3 = 0, T x4 = 0, T x5 = 0, T x6 = 0, T x7 = 0, T x8 = 0, T x9 = 0)
{
    if (var == x1) return true;
    else if (var == x2) return true;
    else if (var == x3) return (valNumber > 2);
    else if (var == x4) return (valNumber > 3);
    else if (var == x5) return (valNumber > 4);
    else if (var == x6) return (valNumber > 5);
    else if (var == x7) return (valNumber > 6);
    else if (var == x8) return (valNumber > 7);
    else if (var == x9) return (valNumber > 8);
    return false;
}

/// return a random value
template <typename T>
T choose(unsigned short valNumber, T x1, T x2, T x3 = 0, T x4 = 0, T x5 = 0, T x6 = 0, T x7 = 0, T x8 = 0, T x9 = 0)
{
    unsigned int randVal = rand() % valNumber;

    switch(randVal)
    {
        case 1 : return x2; break;
        case 2 : return x3; break;
        case 3 : return x4; break;
        case 4 : return x5; break;
        case 5 : return x6; break;
        case 6 : return x7; break;
        case 7 : return x8; break;
        case 8 : return x9; break;
        default : break;
    }
    return x1;
}

/// return if a is in [b,c]
bool isBetween(float a, float b, float c);

/// return if [l1,r1] intersect [l2,r2]
bool isCrossing(float l1, float r1, float l2, float r2);

/// test if the point m is on the right side of the vector ab
/// return -1 on the left, 1 on the right, o if a b c are aligned
int side(Point m, Point a,Point b);

/// return sign of x
int sign(float x);

/// return angle between two points (x1, y1) and (x2, y2)
template <typename T>
T pointDirection(float x1, float y1, float x2, float y2)
{
    if (static_cast<int>(x1) == static_cast<int>(x2))
    {
        if (y2 > y1) return (0.5f * M_PI);
        else return (1.5f * M_PI);
    }
    float result = std::atan((y2 - y1) / (x2 - x1));
    if (x2 < x1) result += M_PI;
    if (result < 0.f) result += 2.f * M_PI;
    result *= 180.f / M_PI;
    return result;
}

/// return distance between two points (x1, y1) and (x2, y2)
float pointDistance(float x1, float y1, float x2, float y2);

/// convert radian to grade
float radToDeg(float x);

/// convert grade to radian
float degToRad(float x);

/// return x component of the vector
float lengthDirX(float dir, float angle);

/// return y component of the vector
float lengthDirY(float dir, float angle);

/// allow to make scale animation
template <class T>
void scaleAnimation(float const &DELTA_TIME, float &var, T &obj, short varSign = 1, float scaleSize = 1.f)
{
    if (var > scaleSize) var -= ((0.05f * is::VALUE_CONVERSION) * DELTA_TIME);
    else var = scaleSize;
    obj.setScale(varSign * var, varSign * var);
}

/// allows to increment a variable while controlling the upper limit
/// increaseValue parameter will be multiplied later by is::VALUE_CONVERSION
template <typename T>
void increaseVar(const float &DELTA_TIME, T &var, T increaseValue, T varLimit, T varMax)
{
    if (var < varMax) var += ((increaseValue * is::VALUE_CONVERSION) * DELTA_TIME);
    else var = varLimit;
}

/// allows to decrement a variable while controlling the lower limit
/// decreasingValue parameter will be multiplied later by is::VALUE_CONVERSION
template <typename T>
void decreaseVar(const float &DELTA_TIME, T &var, T decreaseValue, T varLimit = 0, T varMin = 0)
{
    if (var > varMin) var -= ((decreaseValue * is::VALUE_CONVERSION) * DELTA_TIME);
    else var = varLimit;
}

/// return the x scale size of SFML object
template <class T>
float getSFMLObjXScale(T obj)
{
    return obj.getScale().x;
}

/// return the y scale size of SFML object
template <class T>
float getSFMLObjYScale(T obj)
{
    return obj.getScale().y;
}

/// return the x width of SFML object
template <class T>
float getSFMLObjWidth(T obj)
{
    return obj.getGlobalBounds().width;
}

/// return the y height of SFML object
template <class T>
float getSFMLObjHeight(T obj)
{
    return obj.getGlobalBounds().height;
}

/// return the x origin of SFML object
template <class T>
float getSFMLObjOriginX(T obj)
{
    return obj.getOrigin().x;
}

/// return the y origin of SFML object
template <class T>
float getSFMLObjOriginY(T obj)
{
    return obj.getOrigin().y;
}

/// return the x position of SFML object
template <class T>
float getSFMLObjX(T obj)
{
    return obj.getPosition().x;
}

/// return the y position of SFML object
template <class T>
float getSFMLObjY(T obj)
{
    return obj.getPosition().y;
}

/// return the x position of SFML object (pointer object)
template <class T>
float getSFMLObjX(T *obj)
{
    return obj->getPosition().x;
}

/// return the y position of SFML object (pointer object)
template <class T>
float getSFMLObjY(T *obj)
{
    return obj->getPosition().y;
}

/// set the angle of SFML object
template <class T>
void setSFMLObjAngle(T &obj, float angle)
{
    obj.setRotation(angle);
}

/// set the x, y scale of SFML object
template <class T>
void setSFMLObjScaleX_Y(T &obj, float x, float y)
{
    obj.setScale(x, y);
}

/// set the scale of SFML object
template <class T>
void setSFMLObjScale(T &obj, float scale)
{
    obj.setScale(scale, scale);
}

/// set x position of SFML object
template <class T>
void setSFMLObjX(T &obj, float x)
{
    obj.setPosition(x, obj.getPosition().y);
}

/// set y position of SFML object
template <class T>
void setSFMLObjY(T &obj, float y)
{
    obj.setPosition(obj.getPosition().x, y);
}

/// set x, y position of SFML object
template <class T>
void setSFMLObjX_Y(T &obj, sf::Vector2f position)
{
    obj.setPosition(position.x, position.y);
}

/// set x, y position of SFML object
template <class T>
void setSFMLObjX_Y(T &obj, float x, float y)
{
    obj.setPosition(x, y);
}

/// set the alpha of SFML object
template <class T>
void setSFMLObjAlpha(T &obj, unsigned int alpha)
{
    obj.setColor(sf::Color(255, 255, 255, alpha));
}

/// set the alpha and RGB distinct color of SFML object
template <class T>
void setSFMLObjAlpha(T &obj, unsigned int alpha, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
{
    obj.setColor(sf::Color(r, g, b, alpha));
}

/// set the alpha and uniform RGB color of SFML object
template <class T>
void setSFMLObjAlpha(T &obj, unsigned int alpha, sf::Uint8 rgb)
{
    obj.setColor(sf::Color(rgb, rgb, rgb, alpha));
}

/// set the color of SFML object
template <class T>
void setSFMLObjColor(T &obj, sf::Color color)
{
    obj.setColor(color);
}

/// set the alpha and RGB distinct color of SFML Text object
void setSFMLTextAlpha(sf::Text &obj, unsigned int alpha, sf::Uint8 r = 255, sf::Uint8 g = 255, sf::Uint8 b = 255);

/// set the color of SFML Text object
void setSFMLTextColor(sf::Text &obj, sf::Color color);

/// set the outline color of SFML Text object
void setSFMLTextOutlineColor(sf::Text &obj, sf::Color color);

/// set the alpha and RGB distinct color of SFML Rectangle object
void setSFMLRecAlpha(sf::RectangleShape &obj, unsigned int alpha, sf::Uint8 r = 255, sf::Uint8 g = 255, sf::Uint8 b = 255);

/// set the color of SFML Rectangle object
void setSFMLRecColor(sf::RectangleShape &obj, sf::Color color);

/*
// test whether there are a collision between the two rectangle r1 and r2
bool isCollision(Rectangle r1, Rectangle r2);
bool isCollision(Rectangle r, Point p);
bool isCollision(Point p, Rectangle r);
bool isCollision(Rectangle r, Line l);
bool isCollision(Line l, Rectangle r);
bool isCollision(Line l1,Line l2);
*/

/// test collision between two rectangles
bool collisionTest(Rectangle const &firstBox, Rectangle const &secondBox);

/// create SFML rectangle
void createRectangle(sf::RectangleShape &rec, sf::Vector2f recSize, sf::Color color, float x = 0.f, float y = 0.f, bool center = true);

/// set SFML Text style
void textStyleConfig(sf::Text &txt, bool underLined, bool boldText, bool italicText);

/// create SFML text
void createText(sf::Font const& fnt, sf::Text &txt, std::string const &text, float x, float y, int txtSize = 20, bool underLined = false, bool boldText = false, bool italicText = false);

/// create SFML text with color and size
void createText(sf::Font const& fnt, sf::Text &txt, std::string const &text, float x, float y, sf::Color color, int txtSize = 20, bool underLined = false, bool boldText = false, bool italicText = false);

/// create SFML text outline with color and size
void createText(sf::Font const& fnt, sf::Text &txt, std::string const &text, float x, float y, sf::Color color, sf::Color outlineColor, int txtSize = 20, bool underLined = false, bool boldText = false, bool italicText = false);

/// create SFML sprites without IntRec
void createSprite(sf::Texture &tex, sf::Sprite &spr, sf::Vector2f position, sf::Vector2f origin, bool smooth = true);

/// create SFML sprites with IntRec
void createSprite(sf::Texture &tex, sf::Sprite &spr, sf::IntRect rec, sf::Vector2f position, sf::Vector2f origin, bool repeatTexture = false, bool smooth = true);

/// create SFML sprites advanced
void createSprite(sf::Texture &tex, sf::Sprite &spr, sf::IntRect rec, sf::Vector2f position, sf::Vector2f origin, sf::Vector2f scale, unsigned int alpha = 255, bool repeatTexture = false, bool smooth = true);

/// center SFML object
template <class T>
void centerSFMLObj(T &obj)
{
    obj.setOrigin(obj.getGlobalBounds().width / 2, obj.getGlobalBounds().height / 2);
}

/// test collision on SFML object (Mouse on PC - Touch on mobile)
template <class T>
bool mouseCollision(sf::RenderWindow const &app, T const &obj
                    #if defined(__ANDROID__)
                    , unsigned int finger = 0
                    #endif // defined
                    )
{
    sf::RectangleShape mouseCursor(sf::Vector2f(3.f, 3.f));
    is::centerSFMLObj(mouseCursor);

    #if defined(__ANDROID__)
    sf::Vector2i pixelPos = sf::Touch::getPosition(finger, app);
    #else
    sf::Vector2i pixelPos = sf::Mouse::getPosition(app);
    #endif // defined

    sf::Vector2f worldPos = app.mapPixelToCoords(pixelPos);
    float dx = pointDistance(app.getView().getCenter().x, app.getView().getCenter().y,
                             worldPos.x, app.getView().getCenter().y);
    float dy = pointDistance(app.getView().getCenter().x, app.getView().getCenter().y,
                             app.getView().getCenter().x, worldPos.y);

    if (worldPos.x < app.getView().getCenter().x) dx *= -1;
    if (worldPos.y < app.getView().getCenter().y) dy *= -1;

    mouseCursor.setPosition(app.getView().getCenter().x + dx, app.getView().getCenter().y + dy);
    if (obj.getGlobalBounds().intersects(mouseCursor.getGlobalBounds())) return true;
    else return false;
}

#if defined(__ANDROID__)
/// allow to use Android vibrate
int vibrate(sf::Time duration);

/// allow to deactivate / activate Android screen lock
void setScreenLock(bool disableLock);

/// open URL in Android default navigator
void openURl(std::string urlStr);

/// convert JNI String to std::string
static std::string jstring2string(JNIEnv *env, jstring jStr);

/// return Android terminal device
static std::string getDeviceId(JNIEnv *env, ANativeActivity *activity);
#endif // defined
}

#endif // GAME_FONCTION_H_INCLUDED
