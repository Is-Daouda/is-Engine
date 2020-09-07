#ifndef GAMEACTIVITY_H_INCLUDED
#define GAMEACTIVITY_H_INCLUDED

#include "SwooshFiles.h"
#include "../scenes/HelloScene/HelloScene.h"

// example
// #include "../scenes/YourScene/YourScene.h"

using namespace swoosh::intent;

////////////////////////////////////////////////////////////
/// Allows to manage the different scenes of the game and
/// to interconnect the engine and the Swoosh library to make
/// transition effects
////////////////////////////////////////////////////////////
class GameActivity : public Activity
{
private:
    std::shared_ptr<is::GameDisplay> m_gameScene;
    bool m_changeActivity;

public:
    GameActivity(ActivityController& controller, is::GameSystemExtended &gameSysExt) :
        Activity(&controller), m_changeActivity(false)
    {
        m_gameScene = nullptr;

        // Allows to choose the scene that will be launched
        switch (gameSysExt.m_launchOption)
        {
        case is::DisplayOption::HELLO_SCENE:
            m_gameScene = std::make_shared<HelloScene>(controller.getWindow(),
                                                         getView(),
                                                         *(this->controller->getSurface()),
                                                         gameSysExt);
        break;

        // example
        // case is::DisplayOption::YOUR_SCENE:
        //    m_gameScene = std::make_shared<YourScene>(controller.getWindow(),
        //                                              getView(),
        //                                              *(this->controller->getSurface()),
        //                                              gameSysExt);
        // break;

        default:
			is::showLog("ERROR: Scene not found !", true);
		break;
        }
        m_gameScene->loadResources();
        this->setBGColor(m_gameScene->getBgColor());
    }

    virtual void onStart()
    {
        std::cout << "GameActivity OnStart called" << std::endl;
    }

    virtual void onUpdate(double elapsed)
    {
        if (m_gameScene->getIsRunning()) m_gameScene->step();
        else
        {
            if (!m_changeActivity)
            {
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
                m_changeActivity = true;
            }
        }
    }

    virtual void onLeave()
    {
        std::cout << "GameActivity OnLeave called" << std::endl;
    }

    virtual void onExit()
    {
        std::cout << "GameActivity OnExit called" << std::endl;
    }

    virtual void onEnter()
    {
        std::cout << "GameActivity OnEnter called" << std::endl;
    }

    virtual void onResume()
    {
        std::cout << "GameActivity OnResume called" << std::endl;
    }

    virtual void onDraw(sf::RenderTexture& surface)
    {
        m_gameScene->drawScreen();
    }

    virtual void onEnd() {}

    ~GameActivity() {}
};

#endif // GAMEACTIVITY_H_INCLUDED
