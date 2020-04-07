#ifndef FINISHFLAG_H_INCLUDED
#define FINISHFLAG_H_INCLUDED

#include "../../../isEngine/system/entity/MainObject.h"
#include "../../../isEngine/system/function/GameTime.h"
#include "../../gamesystem_ext/GameSystemExtended.h"
#include "../parents/Health.h"
#include "../parents/Step.h"
#include "../../language/GameLanguage.h"
#include "Player.h"

class FinishObject : public is::MainObject, public Step
{
public:
    FinishObject(GameSystemExtended &gameSysExt);

    void loadResources(sf::Texture &tex);
    void draw(sf::RenderTexture &surface);

private:
    GameSystemExtended &m_gameSysExt;
};

#endif // FINISHFLAG_H_INCLUDED
