/*
  is::Engine (Infinity Solutions Engine)
  Copyright (C) 2018-2023 Is Daouda <isdaouda.n@gmail.com>

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

#include "isEngineWrapper.h"

#if defined(IS_ENGINE_SDL_2)
namespace sf
{
bool Rect::intersects(Rect const &rec) const
{
    int x1Other = rec.left;
    int x2Other = rec.left + rec.width;
    int y1Other = rec.top;
    int y2Other = rec.top + rec.height;

    int x1 = left;
    int x2 = left + width;
    int y1 = top;
    int y2 = top + height;

    if (y2 <= y1Other) return false;
    if (y1 >= y2Other) return false;
    if (x2 <= x1Other) return false;
    if (x1 >= x2Other) return false;
    return true;
}

bool Rect::intersects(Rect const &rec1, Rect const &rec2) const
{
    return rec1.intersects(rec2);
}

Rect functionGetGlobalBounds(const Vector2f &position, const Vector2f &origin, const Vector2f &size)
{
    Rect aabb;
    aabb.left   = position.x - origin.x;
    aabb.top    = position.y - origin.y;
    aabb.width  = size.x;
    aabb.height = size.y;
    return aabb;
}

Clock::Clock() : m_startTime(seconds(0.018f)) {}

const Time Clock::getElapsedTime()
{
    return m_startTime;
}

Time Clock::restart()
{
    return m_startTime;
}

////////////////////////////////////////////////////////////
//              Time Operator and Function
////////////////////////////////////////////////////////////
const Time Time::Zero;

// functions
Time seconds(float amount)
{
    // Special case: allows the SMK timer to have the same behavior as that of the SFML Pong example
    if (amount > 0.09f && amount < 0.101f)
    {
        sf::Clock dTime;
        amount = dTime.getElapsedTime().asSeconds() - 0.01f;
    }
    return Time(static_cast<Int64>(amount * 1000000));
}
Time milliseconds(Int32 amount) {return Time(static_cast<Int64>(amount) * 1000);}
Time microseconds(Int64 amount) {return Time(amount);}

// operator
inline bool operator ==(Time left, Time right) {return left.asMicroseconds() == right.asMicroseconds();}

inline bool operator !=(Time left, Time right) {return left.asMicroseconds() != right.asMicroseconds();}

inline bool operator <(Time left, Time right) {return left.asMicroseconds() < right.asMicroseconds();}

inline bool operator >(Time left, Time right) {return left.asMicroseconds() > right.asMicroseconds();}

inline bool operator <=(Time left, Time right){return left.asMicroseconds() <= right.asMicroseconds();}

inline bool operator >=(Time left, Time right){return left.asMicroseconds() >= right.asMicroseconds();}

inline Time operator -(Time right) {return microseconds(-right.asMicroseconds());}

inline Time operator +(Time left, Time right) {return microseconds(left.asMicroseconds() + right.asMicroseconds());}

inline Time& operator +=(Time& left, Time right) {return left = left + right;}

inline Time operator -(Time left, Time right) {return microseconds(left.asMicroseconds() - right.asMicroseconds());}

inline Time& operator -=(Time& left, Time right) {return left = left - right;}

inline Time operator *(Time left, float right) {return seconds(left.asSeconds() * right);}

inline Time operator *(Time left, Int64 right) {return microseconds(left.asMicroseconds() * right);}

inline Time operator *(float left, Time right) {return right * left;}

inline Time operator *(Int64 left, Time right) {return right * left;}

inline Time& operator *=(Time& left, float right) {return left = left * right;}

inline Time& operator *=(Time& left, Int64 right) {return left = left * right;}

inline Time operator /(Time left, float right) {return seconds(left.asSeconds() / right);}

inline Time operator /(Time left, Int64 right) {return microseconds(left.asMicroseconds() / right);}

inline Time& operator /=(Time& left, float right) {return left = left / right;}

inline Time& operator /=(Time& left, Int64 right) {return left = left / right;}

inline float operator /(Time left, Time right) {return left.asSeconds() / right.asSeconds();}

inline Time operator %(Time left, Time right) {return microseconds(left.asMicroseconds() % right.asMicroseconds());}

inline Time& operator %=(Time& left, Time right) {return left = left % right;}
}
#endif
