#ifndef GAME_FONCTION_H_INCLUDED
#define GAME_FONCTION_H_INCLUDED

#include <cmath>
#include <ctime>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>

/// Allows to browse object container (std::vector, ...)
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
////////////////////////////////////////////////////////////
// Do not touch these variables unless you know what you are doing
static float const MAX_CLOCK_TIME(0.018f); ///< game execution timing variables
static float const VALUE_CONVERSION(65.f); ///< game execution timing variables
static float const VALUE_TIME(1.538f);     ///< game execution timing variables
////////////////////////////////////////////////////////////

static float const PI(3.14f);

/// Convert w_chart_t to string
std::string w_chart_tToStr(wchar_t const *str);

/// Convert string to wstring
std::wstring strToWStr(const std::string &str);

/// Convert number to string
template <class T>
std::string numToStr(T val)
{
    std::ostringstream s;
    s << val;
    return s.str();
}

/// Convert string to number
template <typename T>
T strToNum(const std::string &str)
{
    T val;
    std::istringstream iss(str);
    iss >> val;
    return val;
}

/// Convert number to wstring
template <class T>
std::wstring numToWStr(T val)
{
    std::wostringstream ws;
    ws << val;
    const std::wstring s(ws.str());
    return s;
}

/// Draw zero behind a number
template <class T>
std::string writeZero(T val, int zeroNumber = 1)
{
    std::string str;
    for (int i(0); i < zeroNumber; i++)
        if (val < std::pow(10, (i + 1))) str += "0";
    return (str + is::numToStr(val));
}

/// Return game execution time in millisecond
int getMSecond(float const &DELTA_TIME);

/// Show log message
void showLog(std::string str);

/// Get array size
template <size_t SIZE, class T>
inline size_t arraySize(T (&arr)[SIZE])
{
    return SIZE;
}

/// Return a random value
/// \param valNumber Number of values to test
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

/// Set variable limit
template <typename T>
void setVarLimit(T &var, T valMin, T valMax)
{
    if (var < valMin) var = valMin;
    if (var > valMax) var = valMin;
}

/// Test many values in comparison with a variable
/// \param valNumber number of values to test
bool isIn(unsigned short valNumber, int const var, int x1, int x2, int x3 = 0, int x4 = 0, int x5 = 0, int x6 = 0, int x7 = 0, int x8 = 0, int x9 = 0);

/// Return if a is in [b,c]
bool isBetween(float a, float b, float c);

/// Return if [l1,r1] intersect [l2,r2]
bool isCrossing(float l1, float r1, float l2, float r2);

/// Test if the point m is on the right side of the vector ab
/// \return -1 on the left, 1 on the right, 0 if a b c are aligned
int side(Point m, Point a,Point b);

/// Return sign of x
int sign(float x);

/// Return angle between two points (x1, y1) and (x2, y2)
template <typename T>
T pointDirection(float x1, float y1, float x2, float y2)
{
    if (static_cast<int>(x1) == static_cast<int>(x2))
    {
        if (y2 > y1) return (0.5f * PI);
        else return (1.5f * PI);
    }
    float result = std::atan((y2 - y1) / (x2 - x1));
    if (x2 < x1) result += PI;
    if (result < 0.f) result += 2.f * PI;
    result *= 180.f / PI;
    return result;
}

/// Return distance between two points (x1, y1) and (x2, y2)
float pointDistance(float x1, float y1, float x2, float y2);

/// Convert radian to grade
float radToDeg(float x);

/// Convert grade to radian
float degToRad(float x);

/// Return x component of the vector
float lengthDirX(float dir, float angle);

/// Return y component of the vector
float lengthDirY(float dir, float angle);

/// Allows to make scale animation
template <class T>
void scaleAnimation(float const &DELTA_TIME, float &var, T &obj, short varSign = 1, float scaleSize = 1.f)
{
    if (var > scaleSize) var -= ((0.05f * is::VALUE_CONVERSION) * DELTA_TIME);
    else var = scaleSize;
    obj.setScale(varSign * var, varSign * var);
}

/// Allows to increment a variable while controlling the upper limit
/// \param increaseValue Will be multiplied later by @a is::VALUE_CONVERSION
template <typename T>
void increaseVar(const float &DELTA_TIME, T &var, T increaseValue, T varFinal, T varMax)
{
    if (var < varMax) var += ((increaseValue * is::VALUE_CONVERSION) * DELTA_TIME);
    else var = varFinal;
}

/// Allows to decrement a variable while controlling the lower limit
/// \param decreasingValue Will be multiplied later by @a is::VALUE_CONVERSION
template <typename T>
void decreaseVar(const float &DELTA_TIME, T &var, T decreaseValue, T varFinal = 0, T varMin = 0)
{
    if (var > varMin) var -= ((decreaseValue * is::VALUE_CONVERSION) * DELTA_TIME);
    else var = varFinal;
}

/// Return the angle of SFML object
template <class T>
float getSFMLObjAngle(T obj)
{
    return obj.getRotation();
}

/// Return the x scale size of SFML object
template <class T>
float getSFMLObjXScale(T obj)
{
    return obj.getScale().x;
}

/// Return the y scale size of SFML object
template <class T>
float getSFMLObjYScale(T obj)
{
    return obj.getScale().y;
}

/// Return the x width of SFML object
template <class T>
float getSFMLObjWidth(T obj)
{
    return obj.getGlobalBounds().width;
}

/// Return the y height of SFML object
template <class T>
float getSFMLObjHeight(T obj)
{
    return obj.getGlobalBounds().height;
}

/// Return the x origin of SFML object
template <class T>
float getSFMLObjOriginX(T obj)
{
    return obj.getOrigin().x;
}

/// Return the y origin of SFML object
template <class T>
float getSFMLObjOriginY(T obj)
{
    return obj.getOrigin().y;
}

/// Return the x position of SFML object
template <class T>
float getSFMLObjX(T obj)
{
    return obj.getPosition().x;
}

/// Return the y position of SFML object
template <class T>
float getSFMLObjY(T obj)
{
    return obj.getPosition().y;
}

/// Return the x position of SFML object (pointer object)
template <class T>
float getSFMLObjX(T *obj)
{
    return obj->getPosition().x;
}

/// Return the y position of SFML object (pointer object)
template <class T>
float getSFMLObjY(T *obj)
{
    return obj->getPosition().y;
}

/// Set the angle of SFML object
template <class T>
void setSFMLObjAngle(T &obj, float angle)
{
    obj.setRotation(angle);
}

/// Set rotation of SFML object
template <class T>
void setSFMLObjRotate(T &obj, float rotationSpeed)
{
    obj.rotate(rotationSpeed);
}

/// Set the x, y scale of SFML object
template <class T>
void setSFMLObjScaleX_Y(T &obj, float x, float y)
{
    obj.setScale(x, y);
}

/// Set the scale of SFML object
template <class T>
void setSFMLObjScale(T &obj, float scale)
{
    obj.setScale(scale, scale);
}

/// Set origin of SFML object
template <class T>
void setSFMLObjOrigin(T &obj, float x, float y)
{
    obj.setOrigin(sf::Vector2f(x, y));
}

/// Set x position of SFML object
template <class T>
void setSFMLObjX(T &obj, float x)
{
    obj.setPosition(x, obj.getPosition().y);
}

/// Set y position of SFML object
template <class T>
void setSFMLObjY(T &obj, float y)
{
    obj.setPosition(obj.getPosition().x, y);
}

/// Set x, y position of SFML object
template <class T>
void setSFMLObjX_Y(T &obj, sf::Vector2f position)
{
    obj.setPosition(position.x, position.y);
}

/// Set x, y position of SFML object
template <class T>
void setSFMLObjX_Y(T &obj, float x, float y)
{
    obj.setPosition(x, y);
}

/// Set SFML object size
template <class T>
void setSFMLObjSize(T &obj, float x, float y)
{
    obj.setSize(sf::Vector2f(x, y));
}

/// Set SFML object size
template <class T>
void setSFMLObjSize(T &obj, sf::Vector2f v)
{
    obj.setSize(v);
}

/// Set the alpha of SFML object
template <class T>
void setSFMLObjAlpha(T &obj, unsigned int alpha)
{
    obj.setColor(sf::Color(obj.getColor().r, obj.getColor().g, obj.getColor().b, alpha));
}

/// Set the alpha of SFML shape or text object
template <class T>
void setSFMLObjAlpha2(T &obj, unsigned int alpha)
{
    obj.setFillColor(sf::Color(obj.getFillColor().r, obj.getFillColor().g, obj.getFillColor().b, alpha));
}

/// Set the alpha and RGB distinct color of SFML object
template <class T>
void setSFMLObjAlpha(T &obj, unsigned int alpha, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
{
    obj.setColor(sf::Color(r, g, b, alpha));
}

/// Set the alpha and uniform RGB color of SFML object
template <class T>
void setSFMLObjAlpha(T &obj, unsigned int alpha, sf::Uint8 rgb)
{
    obj.setColor(sf::Color(rgb, rgb, rgb, alpha));
}

/// Set the color of SFML object
template <class T>
void setSFMLObjColor(T &obj, sf::Color color)
{
    obj.setColor(color);
}

/// Set the color of SFML shape
template <class T>
void setSFMLObjFillColor(T &obj, sf::Color color)
{
    obj.setFillColor(color);
}

/// Set the sprite frame (animation)
void setFrame(sf::Sprite &sprite, float frame, int subFrame, int frameSize = 32, int recWidth = 32, int recHeight = 32);

/// Set the outline color of SFML object
template <class T>
void setSFMLObjOutlineColor(T &obj, sf::Color color)
{
    obj.setOutlineColor(color);
}

/// Set the outline thickness and color of SFML object
template <class T>
void setSFMLObjOutlineColor(T &obj, float thickness, sf::Color color)
{
    obj.setOutlineThickness(thickness);
    obj.setOutlineColor(color);
}

/// Set Texture Rec of SFML object
template <class T>
void setSFMLObjTexRec(T &obj, int x, int y, int w = 32, int h = 32)
{
    obj.setTextureRect(sf::IntRect(x, y, w, h));
}

/// Set the graphic properties of SFML object
template <class T>
void setSFMLObjProperties(T &obj, float x, float y, float angle = 0.f, int alpha = 255, float xScale = 1.f, float yScale = 1.f)
{
    is::setSFMLObjAlpha(obj, alpha);
    is::setSFMLObjAngle(obj, angle);
    is::setSFMLObjScaleX_Y(obj, xScale, yScale);
    is::setSFMLObjX_Y(obj, x, y);
}

/// Get SFML Sound state ( @a 0 = @a Playing, @a 1 = @a Stopped, @a 2 = @a Pause)
template <class T>
bool getSFMLSndState(T &obj, int stateIndex)
{
    switch (stateIndex)
    {
        case 0:
            return (obj.getStatus() == sf::Sound::Status::Playing);
        break;
        case 1:
            return (obj.getStatus() == sf::Sound::Status::Stopped);
        break;
        case 2:
            return (obj.getStatus() == sf::Sound::Status::Paused);
        break;
    }
    return false;
}

/*
// test whether there are a collision between the two rectangle r1 and r2
bool isCollision(Rectangle r1, Rectangle r2);
bool isCollision(Rectangle r, Point p);
bool isCollision(Point p, Rectangle r);
bool isCollision(Rectangle r, Line l);
bool isCollision(Line l, Rectangle r);
bool isCollision(Line l1,Line l2);
*/

/// Test collision between SFML object
template <class A, class B>
bool collisionTestSFML(A const &objA, B const &objB)
{
    return (objB.getGlobalBounds().intersects(objA.getGlobalBounds()));
}

/// Test collision between two rectangles
bool collisionTest(Rectangle const &firstBox, Rectangle const &secondBox);

/// Create SFML rectangle
void createRectangle(sf::RectangleShape &rec, sf::Vector2f recSize, sf::Color color, float x = 0.f, float y = 0.f, bool center = true);

/// Set SFML Text style
void textStyleConfig(sf::Text &txt, bool underLined, bool boldText, bool italicText);

/// Create SFML wtext with color
void createWText(sf::Font const& fnt, sf::Text &txt, std::wstring const &text, float x, float y, sf::Color color, int txtSize = 20, bool underLined = false, bool boldText = false, bool italicText = false);

/// Create SFML text
void createText(sf::Font const& fnt, sf::Text &txt, std::string const &text, float x, float y, int txtSize = 20, bool underLined = false, bool boldText = false, bool italicText = false);

/// Create SFML text with center parameter
void createText(sf::Font const& fnt, sf::Text &txt, std::string const &text, float x, float y, bool centerText, int txtSize = 20, bool underLined = false, bool boldText = false, bool italicText = false);

/// Create SFML text with color and size
void createText(sf::Font const& fnt, sf::Text &txt, std::string const &text, float x, float y, sf::Color color, int txtSize = 20, bool underLined = false, bool boldText = false, bool italicText = false);

/// Create SFML text with color, size and center
void createText(sf::Font const& fnt, sf::Text &txt, std::string const &text, float x, float y, sf::Color color, bool centerText, int txtSize = 20, bool underLined = false, bool boldText = false, bool italicText = false);

/// Create SFML text outline with color and size
void createText(sf::Font const& fnt, sf::Text &txt, std::string const &text, float x, float y, sf::Color color, sf::Color outlineColor, int txtSize = 20, bool underLined = false, bool boldText = false, bool italicText = false);

/// Create SFML sprites without IntRec
void createSprite(sf::Texture &tex, sf::Sprite &spr, sf::Vector2f position, sf::Vector2f origin, bool smooth = true);

/// Create SFML sprites with IntRec
void createSprite(sf::Texture &tex, sf::Sprite &spr, sf::IntRect rec, sf::Vector2f position, sf::Vector2f origin, bool repeatTexture = false, bool smooth = true);

/// Create SFML sprites advanced
void createSprite(sf::Texture &tex, sf::Sprite &spr, sf::IntRect rec, sf::Vector2f position, sf::Vector2f origin, sf::Vector2f scale, unsigned int alpha = 255, bool repeatTexture = false, bool smooth = true);

/// Center SFML object
template <class T>
void centerSFMLObj(T &obj)
{
    obj.setOrigin(obj.getGlobalBounds().width / 2, obj.getGlobalBounds().height / 2);
}

/// Center SFML object X
template <class T>
void centerSFMLObjX(T &obj)
{
    obj.setOrigin(obj.getGlobalBounds().width / 2, obj.getOrigin().y);
}

/// Center SFML object Y
template <class T>
void centerSFMLObjY(T &obj)
{
    obj.setOrigin(obj.getOrigin().x, obj.getGlobalBounds().height / 2);
}

/// Allows to use Android vibrate
int vibrate(sf::Time duration);

/// Open URL in Android default navigator
/// \param urlStr represent the web url (e.g www.website.com)
void openURL(std::string urlStr);

#if defined(__ANDROID__)
/// Allows to deactivate / activate Android screen lock
void setScreenLock(bool disableLock);

/// Convert JNI String to std::string
static std::string jstring2string(JNIEnv *env, jstring jStr);

/// Return Android terminal device
static std::string getDeviceId(JNIEnv *env, ANativeActivity *activity);
#endif // defined
}

#endif // GAME_FONCTION_H_INCLUDED
