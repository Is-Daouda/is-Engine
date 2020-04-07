#ifndef GAMETIME_H_INCLUDED
#define GAMETIME_H_INCLUDED

#include "GameFunction.h"

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
    void step(float const &DELTA_TIME, float const &VALUE_CONVERSION, float const &VALUE_TIME);

    /// Add the minute, second and millisecond to the current time
    void addTimeValue(int m, int s = 0, int ms = 0);

    /// Set a new minute, second and millisecond to the current time
    void setTimeValue(int m, int s = 0, int ms = 0);

    /// Set the milliseconds which are distributed in minutes and seconds
    void setMSecond(int ms);

    /// Returns current time in the form of a string (e.g 00:00.00)
    std::string getTimeString() const;

    /// Returns time in milliseconds
    unsigned int getTimeValue() const;

    /// Returns the minute
    unsigned int getMinute() const;

    /// Returns the second
    unsigned int getSecond() const;

    /// Returns the millisecond
    unsigned int getMSecond() const;

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
