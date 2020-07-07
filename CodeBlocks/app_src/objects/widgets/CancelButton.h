#ifndef CANCELBUTTON_H_INCLUDED
#define CANCELBUTTON_H_INCLUDED

#include "../../../isEngine/system/display/GameDisplay.h"
#include "../../../isEngine/system/entity/MainObject.h"

class CancelButton : public is::MainObject
{
public:
    CancelButton(is::GameDisplay *scene);
    void loadResources(sf::Texture &tex);
    void step(float const &DELTA_TIME);
    void setAlpha(int val);
    void draw(sf::RenderTexture &surface);
    bool isOn() const;

private:
    is::GameDisplay *m_scene;
};

#endif // CANCELBUTTON_H_INCLUDED
