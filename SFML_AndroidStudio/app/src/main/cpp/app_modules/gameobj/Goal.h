#ifndef GOAL_H_INCLUDED
#define GOAL_H_INCLUDED

#include "../system/entity/MainObject.h"
#include "../system/entity/Visibilty.h"

class Goal : public is::MainObject, public is::Visibility
{
public:
    Goal();
    void step(const float &DELTA_TIME);
    void draw(sf::RenderWindow &app);
    void loadResources(sf::Texture &tex);

private:
    float m_scale;
    int m_alpha;
};

#endif // GOAL_H_INCLUDED
