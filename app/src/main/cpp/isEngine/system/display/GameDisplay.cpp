/*
  is::Engine (Infinity Solution Engine)
  Copyright (C) 2018-2021 Is Daouda <isdaouda.n@gmail.com>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include "GameDisplay.h"

namespace is
{
sf::Vector2f getMapPixelToCoords(GameDisplay const *scene, sf::Vector2i pixelPos)
{
    return scene->getRenderWindow().mapPixelToCoords(pixelPos, scene->getView());
}

GameDisplay::GameDisplay(GameSystemExtended &gameSysExt, sf::Color bgColor):
    m_isClosed(false),
    m_window(gameSysExt.m_window),
    m_view(sf::Vector2f(is::GameConfig::VIEW_WIDTH / 2.f, is::GameConfig::VIEW_HEIGHT / 2.f), sf::Vector2f(is::GameConfig::VIEW_WIDTH, is::GameConfig::VIEW_HEIGHT)),
    m_surface(gameSysExt.m_window),
    m_gameSysExt(gameSysExt),
    m_timeVibrateDuration(40),
    m_optionIndex(0),
    m_waitTime(0),
    m_msgWaitTime(0),
    m_sceneWidth(is::GameConfig::VIEW_WIDTH),
    m_sceneHeight(is::GameConfig::VIEW_HEIGHT),
    DELTA_TIME(0.f),
    m_viewW(is::GameConfig::VIEW_WIDTH),
    m_viewH(is::GameConfig::VIEW_HEIGHT),
    m_viewX(m_viewW / 2.f),
    m_viewY(m_viewH / 2.f),
    m_sprButtonSelectScale(1.f),
    m_isRunning(true),
    m_windowIsActive(true),
    m_isPlaying(true),
    m_sceneStart(true),
    m_sceneEnd(false),
    m_keyBackPressed(false),
    m_showMsg(false),
    m_mbYesNo(false),
    m_msgBoxMouseInCollison(false)
{
    setViewSize(m_viewW, m_viewH);
    setView(m_viewX, m_viewY);
    m_windowBgColor = bgColor;
}

GameDisplay::~GameDisplay() {}

void GameDisplay::setOptionIndex(int optionIndexValue, bool callWhenClick, float buttonScale)
{
    if (m_waitTime == 0)
    {
        m_gameSysExt.useVibrate(m_timeVibrateDuration);
        GSMplaySound("change_option");
        m_sprButtonSelectScale = buttonScale;
        if (!callWhenClick)
        {
            m_optionIndex += optionIndexValue;
            m_gameSysExt.m_keyIsPressed = true;
        }
        else m_optionIndex = optionIndexValue;
    }
}

void GameDisplay::setOptionIndex(int optionIndexValue)
{
    m_optionIndex = optionIndexValue;
}

void GameDisplay::setTextAnimation(sf::Text &txt, sf::Sprite &spr, int val)
{
    if (m_optionIndex == val)
    {
        is::setSFMLObjX_Y(m_sprButtonSelect, is::getSFMLObjX(spr), is::getSFMLObjY(spr));
        is::setSFMLObjFillColor(txt, is::GameConfig::DEFAULT_SFML_SELECTED_TEXT_COLOR);
    }
    else is::setSFMLObjFillColor(txt, is::GameConfig::DEFAULT_SFML_TEXT_COLOR);
}

void GameDisplay::setTextAnimation(sf::Text &txt, int &var, int val)
{
    if (var == val) is::setSFMLObjFillColor(txt, is::GameConfig::DEFAULT_SFML_SELECTED_TEXT_COLOR);
    else is::setSFMLObjFillColor(txt, is::GameConfig::DEFAULT_SFML_TEXT_COLOR);
}

void GameDisplay::setSprButtonSelectScale(float val)
{
    m_sprButtonSelectScale = val;
}

void GameDisplay::setView(sf::Vector2f v)
{
    m_view.setCenter(v.x, v.y);
    m_surface.setView(m_view);
}

void GameDisplay::setView(float x, float y)
{
    m_view.setCenter(x, y);
    m_surface.setView(m_view);
}

void GameDisplay::setView()
{
    m_view.setCenter(m_viewX, m_viewY);
    m_surface.setView(m_view);
}

void GameDisplay::setViewVarX(float val)
{
    m_viewX = val;
}

void GameDisplay::setViewVarY(float val)
{
    m_viewY = val;
}

void GameDisplay::setViewVarXY(float x, float y)
{
    m_viewX = x;
    m_viewY = y;
}

void GameDisplay::setViewSize(sf::Vector2f v)
{
    m_view.setSize(v.x, v.y);
}

void GameDisplay::setViewSize(float x, float y)
{
    m_view.setSize(x, y);
}

void GameDisplay::setWindowSize(sf::Vector2u v, bool updateViewSize)
{
    #if defined(__ANDROID__)
    m_window.setSize(v);
    if (updateViewSize)
    {
        m_viewW = v.x;
        m_viewH = v.y;
        m_viewX = m_viewW / 2.f;
        m_viewY = m_viewH / 2.f;
        m_view.setSize(m_viewW, m_viewH);
        m_view.setCenter(m_viewX, m_viewY);
        m_window.setView(m_view);
        m_surface.setView(m_view);
    }
    #endif // defined
}

void GameDisplay::setWindowTitle(const std::string &title)
{
    m_window.setTitle(title);
}

void GameDisplay::setWindowBgColor(sf::Color color)
{
    m_windowBgColor = color;
}

void GameDisplay::controlEventFocusClosing(sf::Event &event)
{
    // Manage the state of window
    if (event.type == sf::Event::GainedFocus) m_windowIsActive = true;
    if (event.type == sf::Event::LostFocus)   m_windowIsActive = false;

    // Closing the application
    if (event.type == sf::Event::Closed)
    {
        m_isRunning = false;  // quit the main render loop
        m_window.close();
    }
}

void GameDisplay::updateMsgBox(int sliderDirection, bool rightSideValidation,
                               sf::Color textDefaultColor, sf::Color selectedTextColor)
{
    if (m_msgWaitTime < 240) m_msgWaitTime += static_cast<int>((8.f * is::VALUE_CONVERSION) * DELTA_TIME);
    else m_msgWaitTime = 255;
    if (!m_gameSysExt.isPressed()) m_gameSysExt.m_keyIsPressed = false;

    // Check collision with all objects of message box
    if (!mouseCollision(m_sprMsgBoxButton1) &&
        !mouseCollision(m_sprMsgBoxButton2) &&
        !mouseCollision(m_sprMsgBoxButton3))
         m_msgBoxMouseInCollison = false;
     else m_msgBoxMouseInCollison = true;

    /*
     * sliderDirection is the enum variable found in is::GameSlider. It was not called from the instance
     * because its use is not mandatory in a Scene. This avoids the error message which implies that the
     * instance has not been declared because here we have implemented are not used in even if it does not exist
     * These different values (represents the enum of the class)
        SLIDE_NONE = 0,
        SLIDE_UP = 1,
        SLIDE_DOWN = 2,
        SLIDE_RIGHT = 3,
        SLIDE_LEFT = 4
     */

    // Avoid the long pressing button effect
    if (!m_msgBoxMouseInCollison && sliderDirection == 0 &&
        m_gameSysExt.isPressed(
                               #if !defined(__ANDROID__)
                               is::GameSystem::ValidationButton::MOUSE
                               #endif
                               ))
        m_gameSysExt.m_keyIsPressed = true;

    if (m_msgWaitTime == 255 && m_windowIsActive)
    {
        // If it's YES / NO message box
        if (m_mbYesNo)
        {
            if (((m_gameSysExt.keyIsPressed(is::GameConfig::KEY_LEFT) &&
                  !mouseCollision(m_sprMsgBoxButton2)) || (sliderDirection == 4) ||
                  mouseCollision(m_sprMsgBoxButton1)) && m_msgAnswer == MsgAnswer::NO)
            {
                m_gameSysExt.useVibrate(m_timeVibrateDuration);
                GSMplaySound("change_option");
                m_msgAnswer = MsgAnswer::YES; // answer = yes
            }
            else if (((m_gameSysExt.keyIsPressed(is::GameConfig::KEY_RIGHT) &&
                     !mouseCollision(m_sprMsgBoxButton1)) || (sliderDirection == 3) ||
                      mouseCollision(m_sprMsgBoxButton2)) && m_msgAnswer == MsgAnswer::YES)
            {
                m_gameSysExt.useVibrate(m_timeVibrateDuration);
                GSMplaySound("change_option");
                m_msgAnswer = MsgAnswer::NO;  // answer = no
            }
            else if (m_gameSysExt.keyIsPressed(is::GameConfig::KEY_VALIDATION_KEYBOARD) ||
                     (rightSideValidation) ||
                    ((mouseCollision(m_sprMsgBoxButton1) ||
                      mouseCollision(m_sprMsgBoxButton2)) &&
                      m_gameSysExt.isPressed(is::GameSystem::MOUSE) && !m_gameSysExt.m_keyIsPressed))
            {
                m_showMsg = false;
                m_gameSysExt.m_keyIsPressed = true;
            }
            else if (m_keyBackPressed)
            {
                m_msgAnswer = MsgAnswer::NO; // answer = no (canceled)
                m_showMsg = false;
                m_keyBackPressed = false;
            }

            // Texts animations
            if (m_msgAnswer == MsgAnswer::YES)
            {
                is::setSFMLObjFillColor(m_txtMsgBoxYes, selectedTextColor);
                is::setSFMLObjFillColor(m_txtMsgBoxNo, textDefaultColor);
            }
            else
            {
                is::setSFMLObjFillColor(m_txtMsgBoxNo, selectedTextColor);
                is::setSFMLObjFillColor(m_txtMsgBoxYes, textDefaultColor);
            }
        }
        else // If it's OK message box
        {
            if (mouseCollision(m_sprMsgBoxButton3) && m_msgAnswer == MsgAnswer::NO)
            {
                m_gameSysExt.useVibrate(m_timeVibrateDuration);
                GSMplaySound("change_option");
                m_msgAnswer = MsgAnswer::YES; // answer = OK
                is::setSFMLObjFillColor(m_txtMsgBoxOK, selectedTextColor);
            }
            else if (((m_gameSysExt.keyIsPressed(is::GameConfig::KEY_VALIDATION_KEYBOARD) || m_keyBackPressed) &&
                     !mouseCollision(m_sprMsgBoxButton3)) || (rightSideValidation)|| (mouseCollision(m_sprMsgBoxButton3) &&
                     m_gameSysExt.isPressed(is::GameSystem::MOUSE) && !m_gameSysExt.m_keyIsPressed)
                     )
            {
                m_showMsg = false;
                m_keyBackPressed = false;
                m_gameSysExt.m_keyIsPressed = true;
            }
            else if (!mouseCollision(m_sprMsgBoxButton3) && m_msgAnswer == MsgAnswer::YES)
            {
                m_msgAnswer = MsgAnswer::NO; // answer = NO
                is::setSFMLObjFillColor(m_txtMsgBoxOK, textDefaultColor);
            }
        }
    }

    if (m_msgWaitTime != 255)
    {
        if (m_mbYesNo)
        {
            is::setSFMLObjColor(m_sprMsgBoxButton1, sf::Color(255, 255, 255, m_msgWaitTime));
            is::setSFMLObjColor(m_sprMsgBoxButton2, sf::Color(255, 255, 255, m_msgWaitTime));
            is::setSFMLObjFillColor(m_txtMsgBoxNo, sf::Color(selectedTextColor.r, selectedTextColor.g, selectedTextColor.b, m_msgWaitTime));
            is::setSFMLObjFillColor(m_txtMsgBoxYes, sf::Color(textDefaultColor.r, textDefaultColor.g, textDefaultColor.b, m_msgWaitTime));
        }
        else
        {
            is::setSFMLObjColor(m_sprMsgBoxButton3, sf::Color(255, 255, 255, m_msgWaitTime));
            is::setSFMLObjFillColor(m_txtMsgBoxOK, sf::Color(textDefaultColor.r, textDefaultColor.g, textDefaultColor.b, m_msgWaitTime));
        }
    }
    is::setSFMLObjColor(m_sprMsgBox, sf::Color(255, 255, 255, m_msgWaitTime));
    is::setSFMLObjFillColor(m_txtMsgBox, sf::Color(textDefaultColor.r, textDefaultColor.g, textDefaultColor.b, m_msgWaitTime));

    if (!m_showMsg)
    {
        if (m_msgAnswer == MsgAnswer::NO)
        {
            // If is OK message box the answer is automatically YES
            if (!m_mbYesNo)
            {
                m_msgAnswer = MsgAnswer::YES;
                GSMplaySound("select_option");
                m_gameSysExt.useVibrate(m_timeVibrateDuration);
            }
            else GSMplaySound("cancel");
        }
        else
        {
            GSMplaySound("select_option");
            m_gameSysExt.useVibrate(m_timeVibrateDuration);
        }
    }
}

void GameDisplay::updateTimeWait()
{
    // Waiting time before validating an option
    if (m_waitTime > 0)
    {
        m_waitTime -= is::getMSecond(DELTA_TIME);
    }
    else m_waitTime = 0;
}

void GameDisplay::drawMsgBox()
{
    if (m_showMsg)
    {
        is::draw(m_surface, m_recMsgBox);
        is::draw(m_surface, m_sprMsgBox);

        if (m_mbYesNo)
        {
            is::draw(m_surface, m_txtMsgBoxYes);
            is::draw(m_surface, m_txtMsgBoxNo);
            is::draw(m_surface, m_sprMsgBoxButton1);
            is::draw(m_surface, m_sprMsgBoxButton2);
        }
        else
        {
            is::draw(m_surface, m_txtMsgBoxOK);
            is::draw(m_surface, m_sprMsgBoxButton3);
        }
        is::draw(m_surface, m_txtMsgBox);
    }
}

void GameDisplay::drawScreen()
{
    is::clear(m_surface, m_windowBgColor);
    #if defined(__ANDROID__)
    // On Android when the window is no longer active, nothing is displayed just a black screen.
    // Its allows to optimize the application
    if (m_windowIsActive)
    {
    #endif // defined
        draw();
    #if defined(__ANDROID__)
    }
    #endif // defined
    is::display(m_window);
}

void GameDisplay::showTempLoading(float time)
{
    float timeToQuit(0.f);
    sf::Sprite sprTmploading, sprTmploading2;
    is::createSprite(GRMgetTexture("temp_loading"), sprTmploading, sf::Vector2f(m_viewX, m_viewY), sf::Vector2f(320.f, 240.f));
    is::createSprite(GRMgetTexture("loading_icon"), sprTmploading2, sf::Vector2f(m_viewX, m_viewY), sf::Vector2f(16.f, 16.f));
    while (timeToQuit < time)
    {
        float dTime = getDeltaTime();
        timeToQuit += is::getMSecond(dTime);
        sprTmploading2.rotate((5.f * is::VALUE_CONVERSION) * dTime);

        sf::Event ev;
        while (m_window.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed) is::closeApplication();
        }

        is::clear(m_window, sf::Color::Black);
        is::draw(m_surface, sprTmploading);
        is::draw(m_surface, sprTmploading2);
        is::display(m_window);
    }
}

void GameDisplay::loadParentResources()
{
    if (!m_gameSysExt.m_loadParentResources)
    {
        // Load sound
        m_gameSysExt.GSMaddSound("change_option", is::GameConfig::SFX_DIR + "change_option" + SND_FILE_EXTENSION);
        m_gameSysExt.GSMaddSound("cancel", is::GameConfig::SFX_DIR + "cancel" + SND_FILE_EXTENSION);
        m_gameSysExt.GSMaddSound("select_option", is::GameConfig::SFX_DIR + "select_option" + SND_FILE_EXTENSION);

        // Load message box sprite
        m_gameSysExt.GRMaddTexture("confirm_box", is::GameConfig::GUI_DIR + "confirm_box.png");
        m_gameSysExt.GRMaddTexture("confirm_box_button", is::GameConfig::GUI_DIR + "confirm_box_button.png");

        // Temporal loading texture
        m_gameSysExt.GRMaddTexture("temp_loading", is::GameConfig::GUI_DIR + "temp_loading.png");
        m_gameSysExt.GRMaddTexture("loading_icon", is::GameConfig::GUI_DIR + "loading_icon.png");

        // Load font
        m_gameSysExt.GRMaddFont("font_system", GameConfig::FONT_DIR + "font_system.ttf");
        m_gameSysExt.GRMaddFont("font_msg", GameConfig::FONT_DIR + "font_msg.ttf");

        m_gameSysExt.m_loadParentResources = true;
    }

    if (m_gameSysExt.m_loadParentResources)
    {
        GRMuseGameSystemFont();
        GRMuseGameSystemTexture();
        GSMuseGameSystemSound();
    }

    auto &texMsgButton = GRMgetTexture("confirm_box_button");
    is::createSprite(GRMgetTexture("confirm_box"), m_sprMsgBox, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f));
    is::createSprite(texMsgButton, m_sprMsgBoxButton1, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f));
    is::createSprite(texMsgButton, m_sprMsgBoxButton2, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f));
    is::createSprite(texMsgButton, m_sprMsgBoxButton3, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f));

    is::createRectangle(m_recMsgBox, sf::Vector2f(m_viewW + 40.f, m_viewH + 40.f), sf::Color(0, 0, 0, 200), 0.f, 0.f);

    is::centerSFMLObj(m_sprMsgBox);
    is::centerSFMLObj(m_sprMsgBoxButton1);
    is::centerSFMLObj(m_sprMsgBoxButton2);
    is::centerSFMLObj(m_sprMsgBoxButton3);

    // Load font
    auto &fontSystem = GRMgetFont("font_system");

    is::createText(fontSystem, m_txtMsgBox, "", 0.f, 0.f, 20);
    is::createText(fontSystem, m_txtMsgBoxYes, is::lang::pad_answer_yes[m_gameSysExt.m_gameLanguage],
                   0.f, 0.f, true, 18);
    is::createText(fontSystem, m_txtMsgBoxNo, is::lang::pad_answer_no[m_gameSysExt.m_gameLanguage],
                   0.f, 0.f, true, 18);
    is::createText(fontSystem, m_txtMsgBoxOK, is::lang::pad_answer_ok[m_gameSysExt.m_gameLanguage],
                   0.f, 0.f, true, 18);

    is::createSprite(GRMgetTexture("temp_loading"), m_sprLoading, sf::Vector2f(m_viewX, m_viewY), sf::Vector2f(320.f, 240.f));
}

void GameDisplay::setIsRunning(bool val)
{
    m_isRunning = val;
}

void GameDisplay::setIsPlaying(bool val)
{
    m_isPlaying = val;
}

void GameDisplay::quitScene(int nextScene)
{
    if (nextScene != -1)
    {
        m_gameSysExt.m_launchOption = static_cast<is::DisplayOption>(nextScene);
        m_isRunning = false;
    }
    else is::closeApplication();
}

void GameDisplay::setSceneStart(bool val)
{
    m_sceneStart = val;
}

void GameDisplay::setSceneEnd(bool val)
{
    m_sceneEnd = val;
}

void GameDisplay::setKeyBackPressed(bool val)
{
    m_keyBackPressed = val;
}

float GameDisplay::getDeltaTime()
{
    float dt = m_clock.restart().asSeconds();
    if (dt > is::MAX_CLOCK_TIME) dt = is::MAX_CLOCK_TIME;
    return dt;
}

sf::Vector2f GameDisplay::getCursor(
                                    #if defined(__ANDROID__)
                                    unsigned int finger
                                    #endif // defined
                                    ) const
{
    return is::getCursor(m_window
                       #if defined(__ANDROID__)
                       , finger
                       #endif // defined
                       );
}

bool GameDisplay::inViewRec(is::MainObject *obj, bool useTexRec)
{
    is::Rectangle testRec;
    if (useTexRec)
    {
        testRec.m_left = obj->getX();
        testRec.m_top = obj->getY();
        testRec.m_right = obj->getX() + is::getSFMLObjWidth(obj->getSprite());
        testRec.m_bottom = obj->getY() + is::getSFMLObjHeight(obj->getSprite());
    }
    else testRec = obj->getMask();

    bool isCollision = false;
    is::Rectangle viewRec;
    viewRec.m_left   = getViewX() - (getViewW() / 2) - 16;
    viewRec.m_right  = getViewX() + (getViewW() / 2) + 16;
    viewRec.m_top    = getViewY() - (getViewH() / 2);
    viewRec.m_bottom = getViewY() + (getViewH() / 2);
    if (is::collisionTest(testRec, viewRec))
    {
        isCollision = true;
    }
    return isCollision;
}

bool GameDisplay::inViewRec(is::MainObject &obj, bool useTexRec)
{
    return (inViewRec(&obj, useTexRec));
}

bool GameDisplay::getIsRunning() const
{
    return m_isRunning;
}

#if defined(IS_ENGINE_USE_SDM)
void GameDisplay::SDMmanageScene()
{
    DELTA_TIME = getDeltaTime();
    updateTimeWait();

    // even loop
    SDMmanageSceneEvents();

#if defined(__ANDROID__)
#if defined(IS_ENGINE_USE_ADMOB)
    if (m_gameSysExt.m_admobManager->m_relaunchAd) m_gameSysExt.m_admobManager->showBannerAd();
#endif
#endif

    // starting mechanism
    if (m_sceneStart)
    {
        // window has focus
        if (m_windowIsActive)
        {
            if (!m_showMsg)
            {
                SDMstep();
            }
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      MESSAGE BOX
//////////////////////////////////////////////////////////////////////////////////////////////////////
            else
            {
                updateMsgBox(0, false);

                // when user closes message box in update function execute this instruction
                // "m_waitTime" allow to disable clicks on objects during a moment when user closes message box
                if (!m_showMsg) SDMmanageSceneMsgAnswers();
            }
        }
    }
}

void GameDisplay::SDMcallObjectsEvents(sf::Event &event)
{
    if (m_SDMObjectsEvent)
    {
        // call objects events
        for (std::list<std::shared_ptr<MainObject>>::iterator it = m_SDMsceneObjects.begin();
            it != m_SDMsceneObjects.end(); ++it)
        {
            if (is::instanceExist(*it))
            {
                if ((*it)->m_SDMcallEvent)
                {
                    (*it)->event(event);
                }
            }
        }
    }
}

void GameDisplay::SDMstep()
{
    if (m_SDMObjectsStep)
    {
        // update scene objects
        for (std::list<std::shared_ptr<MainObject>>::iterator it = m_SDMsceneObjects.begin();
            it != m_SDMsceneObjects.end(); ++it)
        {
            if (is::instanceExist(*it))
            {
                if ((*it)->m_SDMcallStep)
                {
                    (*it)->step(DELTA_TIME);
                }
                if (*it != nullptr)
                {
                    if ((*it)->isDestroyed())
                    {
                        it->reset();
                    }
                }
            }
        }
        if (m_SDMsortArray)
        {
            is::sortObjArrayByDepth(m_SDMsceneObjects);
            m_SDMsortArray = false;
        }
    }
}

void GameDisplay::SDMdraw()
{
    if (m_SDMObjectsDraw)
    {
#if defined(IS_ENGINE_SDL_2)
        std::shared_ptr<SDMBlitSDLSprite> obj = nullptr;
#endif
        // draw scene objects
        for (std::list<std::shared_ptr<MainObject>>::iterator it = m_SDMsceneObjects.begin();
            it != m_SDMsceneObjects.end(); ++it)
        {
            if (is::instanceExist(*it))
            {
                if ((*it)->m_SDMcallDraw)
                {
                    if ((*it)->m_SDMblitSprTextureName != "")
                    {
#if defined(IS_ENGINE_SDL_2)
                        if (obj.get() != nullptr)
                        {
                            if (obj->m_strTextureName != (*it)->m_SDMblitSprTextureName)
                            {
                                for (unsigned int i(0); i < m_SDMblitSDLSprite.size(); ++i)
                                {
                                    if (m_SDMblitSDLSprite[i]->m_strTextureName == (*it)->m_SDMblitSprTextureName)
                                    {
                                        obj = m_SDMblitSDLSprite[i];
                                        break;
                                    }
                                }
                            }
                        }
                        else
                        {
                            for (unsigned int i(0); i < m_SDMblitSDLSprite.size(); ++i)
                            {
                                if (m_SDMblitSDLSprite[i]->m_strTextureName == (*it)->m_SDMblitSprTextureName)
                                {
                                    obj = m_SDMblitSDLSprite[i];
                                    break;
                                }
                            }
                        }
                        obj->m_sprBlit.setTextureRect(sf::IntRect((*it)->getSprite().getTextureRect().left,
                                                                  (*it)->getSprite().getTextureRect().top,
                                                                  (*it)->getSprite().getTextureRect().width,
                                                                  (*it)->getSprite().getTextureRect().height));
                        obj->m_sprBlit.setPosition(is::getSFMLObjX((*it)->getSprite()), is::getSFMLObjY((*it)->getSprite()));
                        obj->m_sprBlit.setOrigin(is::getSFMLObjOriginX((*it)->getSprite()), is::getSFMLObjOriginY((*it)->getSprite()));
                        obj->m_sprBlit.setScale(is::getSFMLObjXScale((*it)->getSprite()), is::getSFMLObjYScale((*it)->getSprite()));
                        obj->m_sprBlit.setColor((*it)->getSprite().getColor().r, (*it)->getSprite().getColor().g,
                                                (*it)->getSprite().getColor().b, (*it)->getSprite().getColor().a);
#endif
                        if (inViewRec(it->get(), true))
                        {
                            if ((*it)->getVisible()) m_window.draw(
                                                                  #if defined(IS_ENGINE_SDL_2)
                                                                  obj->m_sprBlit
                                                                  #else
                                                                  (*it)->getSprite()
                                                                  #endif
                                                                  );
                        }
                    }
                    else (*it)->draw(m_surface);
                }
            }
        }
    }
    drawMsgBox();
}

void GameDisplay::createSprite(std::string const &spriteName, is::MainObject &obj, sf::IntRect rec, sf::Vector2f position, sf::Vector2f origin, sf::Vector2f scale, unsigned int alpha)
{
    auto &tex = GRMgetTexture(spriteName);
    obj.m_SDMblitSprTextureName =
#if !defined(IS_ENGINE_SDL_2)
                                spriteName;
    is::createSprite(tex, obj.getSprite(), rec, sf::Vector2f(position.x, position.y), sf::Vector2f(origin.x, origin.y), false, false);
#else
                                GRMgetTexture(spriteName).getFileName();
    bool exists = false;
    for (unsigned int i(0); i < m_SDMblitSDLSprite.size(); ++i)
    {
        if (m_SDMblitSDLSprite[i]->m_strTextureName == obj.m_SDMblitSprTextureName)
        {
            exists = true;
            break;
        }
    }
    if (!exists) m_SDMblitSDLSprite.push_back(std::make_shared<is::SDMBlitSDLSprite>(obj.m_SDMblitSprTextureName, tex));

    obj.getSprite().setTextureRect(sf::IntRect(rec.left, rec.top, rec.width, rec.height));
    obj.getSprite().setPosition(position.x, position.y);
    obj.getSprite().setOrigin(origin.x, origin.y);
    obj.getSprite().setScale(scale.x, scale.y);
    obj.getSprite().setColor(255, 255, 255, alpha);
#endif
}

#endif // defined
}
