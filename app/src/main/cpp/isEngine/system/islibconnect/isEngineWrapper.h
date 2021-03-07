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

#ifndef ISENGINEWRAPPER_H_INCLUDED
#define ISENGINEWRAPPER_H_INCLUDED

#include <memory>
#include <algorithm>
#include <cmath>

#if defined(IS_ENGINE_HTML_5)
#include <smk/Color.hpp>
#include <exception>
#endif

#if defined(__ANDROID__)
#define IS_ENGINE_SDL_2
#endif

namespace is
{
/// Allows to close application
inline void closeApplication()
{
    std::terminate();
}

/// Return distance between two points (x1, y1) and (x2, y2)
inline float pointDistance(float x1, float y1, float x2, float y2)
{
    float X = x1 - x2;
    float Y = y1 - y2;
    return sqrt(X * X + Y * Y);
}

template <class T1, typename T2>
void setVector2(T1 &v, T2 x, T2 y)
{
    v.x = x;
    v.y = y;
};

/// Clear render
template <class T1, class T2>
void clear(T1 &render, T2 const &color)
{
    #if !defined(IS_ENGINE_HTML_5)
    render.clear(color);
    #else
    glm::vec4 smkColor;
    smkColor[0] = color.r;
    smkColor[1] = color.g;
    smkColor[2] = color.b;
    smkColor[3] = color.a;
    render.Clear(smkColor);
    #endif
}

template <class T1>
void clear(T1 &render)
{
    render.
    #if !defined(IS_ENGINE_HTML_5)
            clear();
    #else
            Clear(smk::Color::Black);
    #endif
}

#if !defined(IS_ENGINE_SDL_2)
/// Draw on render
template <class T1, class T2>
void draw(T1 &render, T2 &obj)
{
    render.
        #if !defined(IS_ENGINE_HTML_5)
        draw(obj);
        #else
        Draw(obj);
        #endif
}

template <class T1, class T2>
void draw(T1 &render, T2 *obj)
{
    render.
        #if !defined(IS_ENGINE_HTML_5)
        draw(&obj);
        #else
        Draw(&obj);
        #endif
}
#endif

/// Display Render
template <class T>
void display(T &render)
{
    render.
        #if !defined(IS_ENGINE_HTML_5)
        display
        #else
        Display
        #endif
        ();
}
}

#if defined(IS_ENGINE_HTML_5) || defined(IS_ENGINE_SDL_2)
namespace sf
{
/*
// Allows to display an error message in the console when there is not a similar function of SFML in SMK
inline void functionNotSupported(const std::string &className, const std::string &functionName, const std::string &suitableFunction = "")
{
    std::cout << "\n" + ((className != "") ? className + "::" : "") + functionName + "() is not supported on the SMK library\n";
    if (suitableFunction != "") std::cout << "Use this function instead is::" + suitableFunction + "()\n";
    is::closeApplication();
}
*/

typedef char Int8;
typedef short Int16;
typedef int Int32;
typedef long Int64;

typedef unsigned char Uint8;
typedef unsigned short Uint16;
typedef unsigned int Uint32;
typedef unsigned long Uint64;

template <typename T>
class Vector2
{
public:
    Vector2() {}
    Vector2(T X, T Y) :
        x(X),
        y(Y) {}
    T x;
    T y;
};

#include "isEngineVector2Wrapper.inl"

typedef Vector2<int>          Vector2i;
typedef Vector2<unsigned int> Vector2u;
typedef Vector2<float>        Vector2f;

class Rect
{
public:
    int left;
    int top;
    int width;
    int height;

    Rect() :
        left(0),
        top(0),
        width(0),
        height(0) {}

    Rect(int _left, int _top, int _width, int _height) :
        left(_left),
        top(_top),
        width(_width),
        height(_height) {}

    bool intersects(Rect const &rec) const;
    bool intersects(Rect const &rec1, Rect const &rec2) const;

    template<typename T>
    bool contains(T x, T y) const
    {
        T minX = static_cast<T>(left);
        T maxX = static_cast<T>(left + width);
        T minY = static_cast<T>(top);
        T maxY = static_cast<T>(top + height);
        return (x >= minX) && (x < maxX) && (y >= minY) && (y < maxY);
    }
    template<typename T>
    bool contains(const Vector2<T>& point) const
    {
        return contains(point.x, point.y);
    }
};

typedef Rect IntRect;
typedef Rect FloatRect;

//class String : public std::string {};

Rect functionGetGlobalBounds(const Vector2f &position, const Vector2f &origin, const Vector2f &size);
//Color functionGetColor(Color &color);

class Time
{
public:
    Time() : m_microseconds(0.f) {};
    float asSeconds()      const {return m_microseconds / 1000000.f;}
    Int32 asMilliseconds() const {return static_cast<Int32>(m_microseconds / 1000);}
    Int64 asMicroseconds() const {return m_microseconds;}

    static const Time Zero;
    bool operator>(const Time& time) const {return asMicroseconds() > time.asMicroseconds();}
    bool operator<(const Time& time) const {return asMicroseconds() < time.asMicroseconds();}

private:
    friend Time seconds(float);
    friend Time milliseconds(Int32);
    friend Time microseconds(Int64);
    explicit Time(Int64 microseconds) : m_microseconds(microseconds){}
    Int64 m_microseconds;
};

Time seconds(float amount);
Time milliseconds(Int32 amount);
Time microseconds(Int64 amount);

class Clock
{
public:
    Clock();
    const Time getElapsedTime();
    Time restart();

private:
    Time m_startTime;
};

class SoundSource
{
public:
    enum Status
    {
        Stopped,
        Playing,
        Paused
    };
    SoundSource() : m_status(Stopped) {}

    Status getStatus()
    {
        return m_status;
    }

protected:
    Status m_status = Stopped;
};

enum Style
{
    None,
    Titlebar,
    Resize,
    Close,
    Fullscreen,
    Default
};
}
#endif

#endif // ISENGINEWRAPPER_H_INCLUDED
