#ifndef GAMETIME_H_INCLUDED
#define GAMETIME_H_INCLUDED

#include <sstream>

class GameTime
{
public:
    GameTime();
    GameTime(unsigned int ms);
    GameTime(unsigned int m, unsigned int s, unsigned int ms = 0);
    ~GameTime();

    void step(float const &DELTA_TIME, float valueConversion);
    void addTimeValue(int m, int s = 0, int ms = 0);
    void setValue(int m, int s = 0, int ms = 0);
    void setMSecond(int ms);

    GameTime& operator=(GameTime const &t);
    friend std::ostream& operator<<(std::ostream &flux, GameTime const &t);

    std::string getTimeString() const;
    unsigned int getTimeValue() const;
    unsigned int getMinute()    const;
    unsigned int getSecond()   const;
    unsigned int getMSecond()  const;

protected:
    unsigned int m_minute, m_second, m_mSecond;
};

std::string _writeZero(int val);
std::string _numToStr(int val);
bool operator==(GameTime const &t1, GameTime const &t2);
bool operator>(GameTime const &t1, GameTime const &t2);
bool operator<(GameTime const &t1, GameTime const &t2);


#endif // GAMETIME_H_INCLUDED
