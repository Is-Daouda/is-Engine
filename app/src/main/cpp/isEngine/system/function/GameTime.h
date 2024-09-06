/*
  is::Engine (Infinity Solutions Engine)
  Copyright (C) 2018-2024 Is Daouda <isdaouda.n@gmail.com>

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

#ifndef GAMETIME_H_INCLUDED
#define GAMETIME_H_INCLUDED

#include <string>

namespace is
{
////////////////////////////////////////////////////////////
/// \brief Class to manage the time of the game like a stopwatch
///
/// To use it you define a time (minute, second, third) with the
/// constructor or a method then apply its step() method which
/// allows you to start the countdown until the minutes, seconds
/// and thirds reach zero (0)
////////////////////////////////////////////////////////////
class GameTime
{
public:
    GameTime();

    ////////////////////////////////////////////////////////////
    /// Constructor to initialize the time with the milliseconds
    /// which are distributed in minutes and seconds
    ////////////////////////////////////////////////////////////
    GameTime(unsigned int ms);

    ////////////////////////////////////////////////////////////
    /// Constructor to initialize the time with the minutes
    /// seconds and milliseconds
    ////////////////////////////////////////////////////////////
    GameTime(unsigned int m, unsigned int s, unsigned int ms = 0);

    ~GameTime();

    /// Start the countdown of time so that it stops at zero (0)
    void step(const float &DELTA_TIME);

    /// Add the minute, second and millisecond to the current time
    void addTimeValue(int m, int s, int ms);

    /// Set a new minute, second and millisecond to the current time
    void setTimeValue(int m, int s, int ms);

    /// Set the milliseconds which are distributed in minutes and seconds
    void setMSecond(int ms);

    /// Returns current time in the form of a string (e.g 00:00.00)
    const std::string getTimeString() const noexcept;

    /// Returns time in milliseconds
    unsigned int getTimeValue() const;

    /// Returns the minute
    unsigned int getMinute() const;

    /// Returns the second
    unsigned int getSecond() const;

    /// Returns the millisecond
    unsigned int getMSecond() const;

    /// Compare the entered time and the time of the object
    /// \return true if the time entered is greater than the time of the object false if not
    bool compareTime(unsigned int m, unsigned int s = 0, unsigned int ms = 0) const;

    /// Equality comparison operator
    GameTime& operator=(GameTime const &t);

    /// Operator to display the time with std::cout
    friend std::ostream& operator<<(std::ostream &flux, GameTime const &t);

protected:
    unsigned int m_minute, m_second, m_mSecond;
};

bool operator==(GameTime const &t1, GameTime const &t2);
bool operator>(GameTime const &t1, GameTime const &t2);
bool operator<(GameTime const &t1, GameTime const &t2);
}

#endif // GAMETIME_H_INCLUDED
