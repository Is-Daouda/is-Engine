#ifndef GAME_FONCTION_H_INCLUDED
#define GAME_FONCTION_H_INCLUDED

#include <cmath>
#include <ctime>
#include <sstream>
#include <string>
#include <iostream>

#include "../isEngineWrapper.h"
#include "../entity/Form.h"
#include "../../../app_src/config/GameConfig.h"

#if defined(IS_ENGINE_HTML_5)
/// auto generate font container
static std::vector<std::shared_ptr<sf::Font>> AUTO_GENERATE_FONT;

/// auto generate music container
static std::vector<std::shared_ptr<sf::SoundBuffer>> AUTO_GENERATE_SOUND_BUFFER;
#endif // defined

/// Allows to browse object container (std::vector, ...)
#define WITH(_SIZE) for(unsigned int _I = 0; _I < _SIZE; ++_I)

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
static float const SECOND(59.f);           ///< represent third value in second
static float const VALUE_TIME(1.538f);     ///< game execution timing variables
////////////////////////////////////////////////////////////

static float const PI(3.14159f);

////////////////////////////////////////////////////////////
/// \brief SFML Sound or Music state
///
////////////////////////////////////////////////////////////
enum SFMLSndStatus
{
    Playing,
    Stopped,
    Paused
};

/// Convert wchart_t to string
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
void showLog(std::string str, bool stopApplication = false);

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

/// Return a random value
inline int random(unsigned int limit)
{
    return (rand() % limit);
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

/// Convert radian to grade
float radToDeg(float x);

/// Convert grade to radian
float degToRad(float x);

/// Return x component of the vector
float lengthDirX(float dir, float angle);

/// Return y component of the vector
float lengthDirY(float dir, float angle);

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

/// Test collision between two rectangles
bool collisionTest(Rectangle const &a, Rectangle const &b);

/// Test collision between two circles
bool collisionTest(Circle const &a, Circle const &b);

/// Test collision between rectangle and circle
bool collisionTest(Circle const &circle, Rectangle const &rec);

/// Test collision between rectangle and circle
bool collisionTest(Rectangle const &rec, Circle const &circle);

////////////////////////////////////////////////////////////
//                      WARNING !!!
// Below this comment all the functions that will be defined
// will be linked to the SFML library.
////////////////////////////////////////////////////////////

/// Return the angle of SFML object
template <class T>
float getSFMLObjAngle(T &obj)
{
    return obj.getRotation();
}

/// Return the x scale size of SFML object
template <class T>
float getSFMLObjXScale(T &obj)
{
    return obj.getScale().x;
}

/// Return the scale size of SFML object
template <class T>
float getSFMLObjYScale(T &obj)
{
    return obj.getScale().y;
}

/// Return the width of SFML object
template <class T>
float getSFMLObjWidth(T &obj)
{
    return obj.getGlobalBounds().width;
}

/// Return the y height of SFML object
template <class T>
float getSFMLObjHeight(T &obj)
{
    return obj.getGlobalBounds().height;
}

/// Return the width of SFML texture
inline int getSFMLTextureWidth(sf::Texture const &obj)
{
    return obj.getSize().x;
}

/// Return the height of SFML texture
inline int getSFMLTextureHeight(sf::Texture const &obj)
{
    return obj.getSize().y;
}

/// Return the width of SFML texture
inline int getSFMLTextureWidth(sf::Texture const *obj)
{
    return obj->getSize().x;
}

/// Return the height of SFML texture
inline int getSFMLTextureHeight(sf::Texture const *obj)
{
    return obj->getSize().y;
}

/// Return the x origin of SFML object
template <class T>
float getSFMLObjOriginX(T &obj)
{
    return obj.getOrigin().x;
}

/// Return the y origin of SFML object
template <class T>
float getSFMLObjOriginY(T &obj)
{
    return obj.getOrigin().y;
}

/// Return the x position of SFML object
template <class T>
float getSFMLObjX(T &obj)
{
    return obj.getPosition().x;
}

/// Return the y position of SFML object
template <class T>
float getSFMLObjY(T &obj)
{
    return obj.getPosition().y;
}

/// Return the x position of SFML object (pointer object)
template <class T>
float getSFMLObjX(T *obj)
{
    return getSFMLObjX(&obj);
}

/// Return the y position of SFML object (pointer object)
template <class T>
float getSFMLObjY(T *obj)
{
    return getSFMLObjY(&obj);
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
    setSFMLObjScaleX_Y(obj, scale, scale);
}

/// Set origin of SFML object
template <class T>
void setSFMLObjOrigin(T &obj, float x, float y)
{
    obj.setOrigin(x, y);
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
void setSFMLObjX_Y(T &obj, float x, float y)
{
    obj.setPosition(x, y);
}

/// Set x, y position of SFML object
template <class T>
void setSFMLObjX_Y(T &obj, sf::Vector2f position)
{
    setSFMLObjX_Y(obj, position.x, position.y);
}

/// Move SFML object on x axis
template <class T>
void moveSFMLObjX(T &obj, float speed)
{
    obj.setPosition(obj.getPosition().x + speed, obj.getPosition().y);
}

/// Move SFML object on y axis
template <class T>
void moveSFMLObjY(T &obj, float speed)
{
    obj.setPosition(obj.getPosition().x, obj.getPosition().y + speed);
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
    setSFMLObjSize(obj, v.x, v.y);
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

/// Set the alpha and uniform RGB color of SFML object
template <class T>
void setSFMLObjAlpha(T &obj, unsigned int alpha, sf::Uint8 rgb)
{
    obj.setColor(sf::Color(rgb, rgb, rgb, alpha));
}

/// Set the alpha and RGB distinct color of SFML object
template <class T>
void setSFMLObjAlpha(T &obj, unsigned int alpha, int r, int g, int b)
{
    obj.setColor(sf::Color(r, g, b, alpha));
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

/// Allows to make scale animation
template <class T>
void scaleAnimation(float const &DELTA_TIME, float &var, T &obj, short varSign = 1, float scaleSize = 1.f)
{
    if (var > scaleSize) var -= ((0.05f * is::VALUE_CONVERSION) * DELTA_TIME);
    else var = scaleSize;
    setSFMLObjScale(obj, varSign * var);
}

/// Set the sprite frame with different size (e.g 64x32)
void setFrame(sf::Sprite &sprite, float frame, int subFrame, int frameWidth, int frameHeight, int recWidth, int recHeight);

/// Set the sprite frame with the same size (e.g 64x64)
void setFrame(sf::Sprite &sprite, float frame, int subFrame, int frameSize);

#if !defined(IS_ENGINE_HTML_5)
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
#endif

/// Set Texture Rec of SFML object
template <class T>
void setSFMLObjTexRec(T &obj, int x, int y, int w, int h)
{
    obj.setTextureRect(sf::IntRect(x, y, w, h));
}

/// Set the properties of SFML Sprite
inline void setSFMLObjProperties(sf::Sprite &obj, float x, float y, float angle = 0.f, int alpha = 255, float xScale = 1.f, float yScale = 1.f)
{
    is::setSFMLObjAlpha(obj, alpha);
    is::setSFMLObjAngle(obj, angle);
    is::setSFMLObjScaleX_Y(obj, xScale, yScale);
    is::setSFMLObjX_Y(obj, x, y);
}

/// Set the properties of SFML Text
inline void setSFMLObjProperties(sf::Text &obj, float x, float y, float angle = 0.f, int alpha = 255, float xScale = 1.f, float yScale = 1.f)
{
    is::setSFMLObjAlpha2(obj, alpha);
    is::setSFMLObjAngle(obj, angle);
    is::setSFMLObjScaleX_Y(obj, xScale, yScale);
    is::setSFMLObjX_Y(obj, x, y);
}

/// Set the properties of SFML Rectangle
inline void setSFMLObjProperties(sf::RectangleShape &obj, float x, float y, float angle = 0.f, int alpha = 255, float xScale = 1.f, float yScale = 1.f)
{
    is::setSFMLObjAlpha2(obj, alpha);
    is::setSFMLObjAngle(obj, angle);
    is::setSFMLObjScaleX_Y(obj, xScale, yScale);
    is::setSFMLObjX_Y(obj, x, y);
}

/// Set the properties of SFML Circle
inline void setSFMLObjProperties(sf::CircleShape &obj, float x, float y, float angle = 0.f, int alpha = 255, float xScale = 1.f, float yScale = 1.f)
{
    is::setSFMLObjAlpha2(obj, alpha);
    is::setSFMLObjAngle(obj, angle);
    is::setSFMLObjScaleX_Y(obj, xScale, yScale);
    is::setSFMLObjX_Y(obj, x, y);
}

/// Load SFML Texture Resource
inline void loadSFMLTexture(sf::Texture &obj, std::string filePath)
{
    #if !defined(IS_ENGINE_HTML_5)
    obj.loadFromFile(filePath);
    #else
    obj = sf::Texture(filePath);
    #endif
}

/// Load SFML Font Resource
/// When you develop for the Web you must define the size that the texts will have with this font
inline void loadSFMLFont(sf::Font &obj, std::string filePath, float fontSize = is::GameConfig::DEFAULT_SFML_TEXT_SIZE)
{
    #if !defined(IS_ENGINE_HTML_5)
    obj.loadFromFile(filePath);
    #else
    obj = sf::Font(filePath, fontSize);
    #endif
}

/// Load SFML Sound Buffer Resource
inline void loadSFMLSoundBuffer(sf::SoundBuffer &obj, std::string filePath)
{
    #if !defined(IS_ENGINE_HTML_5)
    obj.loadFromFile(filePath);
    #else
    obj = sf::SoundBuffer(filePath);
    #endif
}

/// Load SFML Sound Buffer Resource and define it with the Sound
inline void loadSFMLSoundBufferWithSnd(sf::SoundBuffer &sb, sf::Sound &snd, std::string filePath)
{
    #if !defined(IS_ENGINE_HTML_5)
    if (sb.loadFromFile(filePath)) snd.setBuffer(sb);
    else showLog("ERROR: Can't load Sound Buffer : " + filePath + " with sound");
    #else
    sb = sf::SoundBuffer(filePath);
    snd = sf::Sound(sb);
    #endif
}

/// Load SFML Music Resource
inline void loadSFMLMusic(sf::Music &obj, std::string filePath)
{
    #if !defined(IS_ENGINE_HTML_5)
    obj.openFromFile(filePath);
    #else
    bool musicExists(false);
    unsigned int musicIndex(0);
    WITH (AUTO_GENERATE_SOUND_BUFFER.size())
    {
        if (AUTO_GENERATE_SOUND_BUFFER[_I]->getFileName() == filePath)
        {
            musicIndex = _I;
            musicExists = true;
            break;
        }
    }
    if (!musicExists)
    {
        AUTO_GENERATE_SOUND_BUFFER.push_back(std::make_shared<sf::SoundBuffer>(filePath));
        musicIndex = (AUTO_GENERATE_SOUND_BUFFER.size() - 1);
    }
    obj = sf::Music(*AUTO_GENERATE_SOUND_BUFFER[musicIndex]);
    #endif
}

/// Check SFML Sound state
template <class T>
bool checkSFMLSndState(T &obj, SFMLSndStatus state)
{
    switch (state)
    {
        case SFMLSndStatus::Playing:
            return (obj.getStatus() == sf::Sound::Status::Playing);
        break;
        case SFMLSndStatus::Stopped:
            return (obj.getStatus() == sf::Sound::Status::Stopped);
        break;
        case SFMLSndStatus::Paused:
            return (obj.getStatus() == sf::Sound::Status::Paused);
        break;
    }
    return false;
}

/// Check SFML Sound state
template <class T>
bool checkSFMLSndState(T *obj, SFMLSndStatus state)
{
    switch (state)
    {
        case SFMLSndStatus::Playing:
            return (obj->getStatus() == sf::Sound::Status::Playing);
        break;
        case SFMLSndStatus::Stopped:
            return (obj->getStatus() == sf::Sound::Status::Stopped);
        break;
        case SFMLSndStatus::Paused:
            return (obj->getStatus() == sf::Sound::Status::Paused);
        break;
    }
    return false;
}

/// Allows to play SFML Sound or Music
template <class T>
void playSFMLSnd(T &obj)
{
    obj.play();
}

/// Allows to play SFML Sound or Music
template <class T>
void playSFMLSnd(T *obj)
{
    obj->play();
}

/// Allows to stop SFML Sound or Music
template <class T>
void stopSFMLSnd(T &obj)
{
    obj.stop();
}

/// Allows to stop SFML Sound or Music
template <class T>
void stopSFMLSnd(T *obj)
{
    obj->stop();
}

/// Allows to pause SFML Sound or Music
template <class T>
void pauseSFMLSnd(T &obj)
{
    obj.pause();
}

/// Allows to pause SFML Sound or Music
template <class T>
void pauseSFMLSnd(T *obj)
{
    obj->pause();
}

/// Allows to set SFML Sound or Music loop
template <class T>
void loopSFMLSnd(T &obj, bool val)
{
    obj.loop(val);
}

/// Allows to set SFML Sound or Music loop
template <class T>
void loopSFMLSnd(T *obj, bool val)
{
    obj->loop(val);
}

/// Test collision between SFML object
template <class A, class B>
bool collisionTestSFML(A const &objA, B const &objB)
{
    return (objB.getGlobalBounds().intersects(objA.getGlobalBounds()));
}

/// Create SFML Render Texture
//void createRenderTexture(sf::RenderTexture &renderTexture, unsigned int width, unsigned int height);

/// Create SFML rectangle
void createRectangle(sf::RectangleShape &rec, sf::Vector2f recSize, sf::Color color, float x = 0.f, float y = 0.f, bool center = true);

/// Set SFML Text style
void textStyleConfig(sf::Text &txt, bool underLined, bool boldText, bool italicText);

#if defined(IS_ENGINE_HTML_5)
inline void setTextFont(sf::Font &fnt, sf::Text &txt, int txtSize)
{
    if (static_cast<int>(fnt.getSize()) != txtSize)
    {
        bool fontExists(false);
        unsigned int fontIndex(0);
        WITH (AUTO_GENERATE_FONT.size())
        {
            if (AUTO_GENERATE_FONT[_I]->getFileName() == fnt.getFileName() && AUTO_GENERATE_FONT[_I]->getSize() == fnt.getSize())
            {
                fontIndex = _I;
                fontExists = true;
                break;
            }
        }
        if (!fontExists)
        {
            AUTO_GENERATE_FONT.push_back(std::make_shared<sf::Font>(fnt.getFileName(), txtSize));
            fontIndex = (AUTO_GENERATE_FONT.size() - 1);
        }
        txt.setFont(*AUTO_GENERATE_FONT[fontIndex]);
    }
    else txt.setFont(fnt);
}
#endif

/// Create SFML wtext with color
void createWText(sf::Font
                 #if !defined(IS_ENGINE_HTML_5)
                 const
                 #endif
                 &fnt, sf::Text &txt, std::wstring const &text, float x, float y, sf::Color color, bool centerText, int txtSize = is::GameConfig::DEFAULT_SFML_TEXT_SIZE);

/// Create SFML text
void createText(sf::Font
                 #if !defined(IS_ENGINE_HTML_5)
                 const
                 #endif
                 &fnt, sf::Text &txt, std::string const &text, float x, float y, int txtSize = is::GameConfig::DEFAULT_SFML_TEXT_SIZE);

/// Create SFML text with center parameter
void createText(sf::Font
                 #if !defined(IS_ENGINE_HTML_5)
                 const
                 #endif
                 &fnt, sf::Text &txt, std::string const &text, float x, float y, bool centerText, int txtSize = is::GameConfig::DEFAULT_SFML_TEXT_SIZE);

/// Create SFML text with color and size
void createText(sf::Font
                 #if !defined(IS_ENGINE_HTML_5)
                 const
                 #endif
                 &fnt, sf::Text &txt, std::string const &text, float x, float y, sf::Color color, int txtSize = is::GameConfig::DEFAULT_SFML_TEXT_SIZE);

/// Create SFML text with color, size and center
void createText(sf::Font
                 #if !defined(IS_ENGINE_HTML_5)
                 const
                 #endif
                 &fnt, sf::Text &txt, std::string const &text, float x, float y, sf::Color color, bool centerText, int txtSize = is::GameConfig::DEFAULT_SFML_TEXT_SIZE);

/// Create SFML text outline with color and size
/*
void createText(sf::Font
                 #if !defined(IS_ENGINE_HTML_5)
                 const
                 #endif
                 &fnt, sf::Text &txt, std::string const &text, float x, float y, sf::Color color, sf::Color outlineColor, int txtSize = is::GameConfig::DEFAULT_SFML_TEXT_SIZE);
*/

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

//////////////////////////////////////////////////////
/// \brief Return Cursor Position
/// the mouse on PC platform / touch on mobile
///
/// \param finger Finger index (on Android)
//////////////////////////////////////////////////////
sf::Vector2f getCursor(sf::RenderWindow &window
                        #if defined(__ANDROID__)
                        , unsigned int finger = 0
                        #endif // defined
                        );

//////////////////////////////////////////////////////
/// \brief Test the collision of the SFML objects
/// with the mouse cursor on PC platform / touch on mobile
///
/// \param obj SFML object with which we want to test
/// \param finger Finger index (on Android)
//////////////////////////////////////////////////////
template <class T>
bool mouseCollision(sf::RenderWindow &window, T const &obj
                    #if defined(__ANDROID__)
                    , unsigned int finger = 0
                    #endif // defined
                    )
{
    sf::Vector2f cursorPos = is::getCursor(window
                                       #if defined(__ANDROID__)
                                       , finger
                                       #endif // defined
                                       );

    // A rectangle that will allow to test with the SFML object
    sf::RectangleShape recCursor(sf::Vector2f(6.f, 6.f));
    is::setSFMLObjX_Y(recCursor, cursorPos.x - 3.f, cursorPos.y - 3.f);
    if (obj.getGlobalBounds().intersects(recCursor.getGlobalBounds())) return true;
    return false;
}

//////////////////////////////////////////////////////
/// \brief Test the collision of the SFML objects
/// with the mouse cursor on PC platform / touch on mobile
///
/// \param obj SFML object with which we want to test
/// \param position Allows to get the position of the collision point
/// \param finger Finger index (on Android)
//////////////////////////////////////////////////////
template <class T>
bool mouseCollision(sf::RenderWindow &window, T const &obj, sf::Vector2f &position
                    #if defined(__ANDROID__)
                    , unsigned int finger = 0
                    #endif // defined
                    )
{
    sf::Vector2f cursorPos = is::getCursor(window
                                       #if defined(__ANDROID__)
                                       , finger
                                       #endif // defined
                                       );
    setVector2(position, cursorPos.x, cursorPos.y);

    // A rectangle that will allow to test with the SFML object
    sf::RectangleShape recCursor(sf::Vector2f(6.f, 6.f));
    is::setSFMLObjX_Y(recCursor, position.x - 3.f, position.y - 3.f);
    if (obj.getGlobalBounds().intersects(recCursor.getGlobalBounds())) return true;
    return false;
}

#if !defined(IS_ENGINE_HTML_5)
/// Do not touch this function it allows to manage the style of the window
inline int getWindowStyle()
{
    switch (GameConfig::WINDOW_SETTINGS)
    {
        case WindowStyle::NONE : return sf::Style::None; break;
        case WindowStyle::TITLEBAR : return sf::Style::Titlebar; break;
        case WindowStyle::RESIZE : return sf::Style::Resize; break;
        case WindowStyle::CLOSE : return sf::Style::Close; break;
        case WindowStyle::FULLSCREEN : return sf::Style::Fullscreen; break;
        default: return sf::Style::Default; break;
    }
}
#endif

/// Allows to set frame per second
template <class T>
void setFPS(T &render, float fps)
{
    render.setFramerateLimit(fps);
}

/// Allows to use Android vibrate
short vibrate(short duration);

/// Open URL in default navigator
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
