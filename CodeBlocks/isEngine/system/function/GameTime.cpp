#include "GameTime.h"

namespace is
{
GameTime::GameTime():
    m_minute(0),
    m_second(0),
    m_mSecond(0)
{
}

GameTime::GameTime(unsigned int ms):
    m_minute(0),
    m_second(0),
    m_mSecond(0)
{
    m_mSecond  = ms;
    m_second  += m_mSecond / 60;
    m_minute += m_second / 60;

    m_mSecond %= 60;
    m_second %= 60;
}

GameTime::GameTime(unsigned int m, unsigned int s, unsigned int ms):
    m_minute(m),
    m_second(s),
    m_mSecond(ms)
{
}

GameTime::~GameTime()
{
}

void GameTime::step(float const &DELTA_TIME, float const &VALUE_CONVERSION, float const &VALUE_TIME)
{
    if (m_mSecond > 0) m_mSecond -= static_cast<int>((VALUE_CONVERSION * VALUE_TIME) * DELTA_TIME);
    else
    {
        if (m_second == 0)
        {
            if (m_minute > 0)
            {
                m_second  = 59;
                m_mSecond = 59;
                m_minute--;
            }
        }
        else
        {
            m_second--;
            m_mSecond = 59;
        }
    }
}

void GameTime::addTimeValue(int m, int s, int ms)
{
    m_minute  += m;
    m_second  += s;
    if (m_second > 59)
    {
        m_minute++;
        m_second = m_second - 59;
    }
    m_mSecond += ms;
}

void GameTime::setTimeValue(int m, int s, int ms)
{
    m_minute  = m;
    m_second  = s;
    m_mSecond = ms;
}

void GameTime::setMSecond(int ms)
{
    m_mSecond  = ms;
    m_second  += m_mSecond / 60;
    m_minute += m_second / 60;

    m_mSecond %= 60;
    m_second %= 60;
}

GameTime& GameTime::operator=(GameTime const &t)
{
    m_minute  = t.m_minute;
    m_second  = t.m_second;
    m_mSecond = t.m_mSecond;

    return *this;
}

unsigned int GameTime::getTimeValue() const
{
    return ((m_minute * 3600) + (m_second * 60) + m_mSecond);
}

unsigned int GameTime::getMinute() const
{
    return m_minute;
}

unsigned int GameTime::getSecond() const
{
    return m_second;
}

unsigned int GameTime::getMSecond() const
{
    return m_mSecond;
}

std::string GameTime::getTimeString() const
{
    std::string str;
    str = writeZero(m_minute) + ":" + writeZero(m_second) + "." + writeZero(m_mSecond);
    return str;
}

bool operator==(GameTime const &t1, GameTime const &t2)
{
    return (t1.getTimeValue() == t2.getTimeValue());
}

bool operator>(GameTime const &t1, GameTime const &t2)
{
    return (t1.getTimeValue() > t2.getTimeValue());
}

bool operator<(GameTime const &t1, GameTime const &t2)
{
    return (t1.getTimeValue() < t2.getTimeValue());
}

std::ostream& operator<<(std::ostream &flux, GameTime const &t)
{
    flux <<
    t.m_minute  << "m "  <<
    t.m_second  << "s " <<
    t.m_mSecond << "ms" <<
    std::endl;

    return flux;
}
}
