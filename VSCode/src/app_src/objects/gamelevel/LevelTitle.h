#ifndef LEVELTITLE_H_INCLUDED
#define LEVELTITLE_H_INCLUDED

#include "../../../isEngine/system/entity/MainObject.h"

class LevelTitle : public is::MainObject
{
public:
    LevelTitle(sf::Font &fnt, float x, float y, std::string levelTitle);

    void step(float const &DELTA_TIME);
    void draw(sf::RenderTexture &surface);

private:
    sf::Text m_txtLevelTitle;
};

#endif // LEVELTITLE_H_INCLUDED
