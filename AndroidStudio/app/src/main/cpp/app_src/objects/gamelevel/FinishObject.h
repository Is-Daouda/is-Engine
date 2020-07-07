#ifndef FINISHFLAG_H_INCLUDED
#define FINISHFLAG_H_INCLUDED

#include "../../../isEngine/system/entity/MainObject.h"
#include "../../../isEngine/system/entity/parents/Health.h"
#include "../../../isEngine/system/entity/parents/Step.h"
#include "../../../isEngine/system/display/GameDisplay.h"
#include "../../language/GameLanguage.h"
#include "Player.h"

////////////////////////////////////////////////////////////
/// Represents the end of the level. If the player touches
/// this object he wins the game
////////////////////////////////////////////////////////////
class FinishObject : public is::MainObject, public is::Step
{
public:
    FinishObject(is::GameDisplay *scene);

    void loadResources(sf::Texture &tex);
    void step(float const &DELTA_TIME);
    void draw(sf::RenderTexture &surface);

private:
    is::GameDisplay *m_scene;
};

#endif // FINISHFLAG_H_INCLUDED
