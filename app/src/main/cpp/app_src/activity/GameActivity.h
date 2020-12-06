#ifndef GAMEACTIVITY_H_INCLUDED
#define GAMEACTIVITY_H_INCLUDED

#include "../config/ExtraConfig.h"

#if (!defined(IS_ENGINE_HTML_5) && !defined(IS_ENGINE_RENDER))
#include "SwooshFiles.h"
using namespace swoosh::intent;
#endif

#include "../scenes/HelloScene/HelloScene.h"

// example
// #include "../scenes/YourScene/YourScene.h"

////////////////////////////////////////////////////////////
/// Allows to manage the different scenes of the game and
/// to interconnect the engine and the Swoosh library to make
/// transition effects
////////////////////////////////////////////////////////////
class GameActivity
// Do not touch that part of the code which is framed!
////////////////////////////////////////////////////////////
#if (!defined(IS_ENGINE_HTML_5) && !defined(IS_ENGINE_RENDER))
    : public Activity
#endif
{
private:
    std::shared_ptr<is::GameDisplay> m_gameScene;
    is::Render &m_surface;
#if (defined(IS_ENGINE_HTML_5) || defined(IS_ENGINE_RENDER))
    sf::View m_view;
#endif
public:
    bool m_changeActivity = false;
    GameActivity(
                 #if (!defined(IS_ENGINE_HTML_5) && !defined(IS_ENGINE_RENDER))
                 ActivityController& activityCtrl,
                 #endif
                 is::GameSystemExtended &gameSysExt) :
                 #if (!defined(IS_ENGINE_HTML_5) && !defined(IS_ENGINE_RENDER))
                 Activity(&activityCtrl),
                 m_surface(*(this->controller->getSurface()))
                 #else
                 m_surface(gameSysExt.m_window)
                 #endif
    {
        m_gameScene = nullptr;
////////////////////////////////////////////////////////////

        // Allows to choose the scene that will be launched
        // Each scene must have its corresponding DisplayOption enum in GameConfig.h
        // The first scene is launched according to the DisplayOption enum entered in GameConfig.h (see line 65)
        switch (gameSysExt.m_launchOption)
        {
        case is::DisplayOption::HELLO_SCENE:
           m_gameScene = std::make_shared<HelloScene>(gameSysExt.m_window, getView(), m_surface, gameSysExt);
        break;

        // example
        // case is::DisplayOption::YOUR_SCENE:
        //    m_gameScene = std::make_shared<YourScene>(activityCtrl.getWindow(), getView(), m_surface, gameSysExt);
        // break;

        default:
			is::showLog("ERROR: Scene not found !", true);
		break;
        }
        m_gameScene->loadResources();
        #if (!defined(IS_ENGINE_HTML_5) && !defined(IS_ENGINE_RENDER))
        this->setBGColor(m_gameScene->getBgColor());
        #endif
    }

    virtual void onUpdate(
                          #if (!defined(IS_ENGINE_HTML_5) && !defined(IS_ENGINE_RENDER))
                          double elapsed
                          #endif
                          )
    {
        if (m_gameScene->getIsRunning()) m_gameScene->step();
        else
        {
            if (!m_changeActivity)
            {
                #if (!defined(IS_ENGINE_HTML_5) && !defined(IS_ENGINE_RENDER))
                // This code can only be used when using the SWOOSH library
                // Allows to choose the next scene that will be launched and to make a transition effect
                switch (m_gameScene->getGameSystem().m_launchOption)
                {
                    case is::DisplayOption::HELLO_SCENE:
                        {
                            using transition = segue<VerticalSlice, sec<2>>;
                            using action = transition::to<GameActivity>;
                            getController().replace<action>(m_gameScene->getGameSystem());
                        }
                    break;

                    // example
                    // case is::DisplayOption::YOUR_SCENE:
                    //    {
                    //        using transition = segue<VerticalSlice, sec<2>>;
                    //        using action = transition::to<GameActivity>;
                    //        getController().replace<action>(m_gameScene->getGameSystem());
                    //    }
                    // break;

                    default:
                        is::showLog("ERROR: Scene not found !", true);
                    break;
                }
                #endif
                m_changeActivity = true;
            }
        }
    }

    virtual void onDraw(
                        #if (!defined(IS_ENGINE_HTML_5) && !defined(IS_ENGINE_RENDER))
                        sf::RenderTexture& surface
                        #endif
                        )
    {
        m_gameScene->drawScreen();
    }
#if (!defined(IS_ENGINE_HTML_5) && !defined(IS_ENGINE_RENDER))
    // This code can only be used when using the SWOOSH library
    virtual void onStart()  {std::cout << "GameActivity OnStart called" << std::endl;}
    virtual void onLeave()  {std::cout << "GameActivity OnLeave called" << std::endl;}
    virtual void onExit()   {std::cout << "GameActivity OnExit called" << std::endl;}
    virtual void onEnter()  {std::cout << "GameActivity OnEnter called" << std::endl;}
    virtual void onResume() {std::cout << "GameActivity OnResume called" << std::endl;}
    virtual void onEnd()    {std::cout << "GameActivity onEnd called" << std::endl;}
#else
    sf::View& getView()     {return m_view;}
#endif
    virtual ~GameActivity() {}
};

#endif // GAMEACTIVITY_H_INCLUDED
