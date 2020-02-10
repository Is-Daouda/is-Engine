#ifndef PAUSEBUTTON_H_INCLUDED
#define PAUSEBUTTON_H_INCLUDED

#include "../system/entity/MainObject.h"

class PauseButton : public is::MainObject
{
public:
    PauseButton();
    void loadResources(sf::Texture &m_tex);
    void step(float const &DELTA_TIME);
    void setAlpha(int val);
    void draw(sf::RenderWindow &surf);

    bool isOn() const;

private:
    int alpha;
};

#endif // PAUSEBUTTON_H_INCLUDED
