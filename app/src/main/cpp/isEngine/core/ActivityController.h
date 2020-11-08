#ifndef ACTIVITYCONTROLLER_H_INCLUDED
#define ACTIVITYCONTROLLER_H_INCLUDED

#include "../../app_src/activity/GameActivity.h"

#if (defined(IS_ENGINE_HTML_5) || defined(IS_ENGINE_RENDER))
class ActivityController
{
public:
    ActivityController(is::GameSystemExtended &gameSysExt):
        m_gameSysExt(gameSysExt)
    {
         m_gameActivity = std::make_shared<GameActivity>(m_gameSysExt);
    }
    void update()
    {
        m_gameActivity->onUpdate();
    }
    void draw()
    {
        m_gameActivity->onDraw();
        if (m_gameActivity->m_changeActivity)
        {
            m_gameActivity.reset();
            m_gameActivity = std::make_shared<GameActivity>(m_gameSysExt);
        }
    }
private:
    is::GameSystemExtended &m_gameSysExt;
    std::shared_ptr<GameActivity> m_gameActivity;
};
#endif

#endif // ACTIVITYCONTROLLER_H_INCLUDED
