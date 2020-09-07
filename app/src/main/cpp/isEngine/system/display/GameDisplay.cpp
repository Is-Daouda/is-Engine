#include "GameDisplay.h"

namespace is
{
sf::Vector2f getMapPixelToCoords(GameDisplay const *scene, sf::Vector2i pixelPos)
{
    return scene->getRenderWindow().mapPixelToCoords(pixelPos, scene->getView());
}

GameDisplay::GameDisplay(sf::RenderWindow &window, sf::View &view, sf::RenderTexture &surface, GameSystemExtended &gameSysExt, sf::Color bgColor):
    m_isClose(false),
    m_window(window),
    m_view(view),
    m_surface(surface),
    m_gameSysExt(gameSysExt),
    m_vibrateTimeDuration(40),
    m_optionIndex(0),
    m_waitTime(0),
    m_msgWaitTime(0),
    m_sceneWidth(window.getSize().x),
    m_sceneHeight(window.getSize().y),
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
    m_windowBgColor = bgColor;

#if defined(__ANDROID__)
#if defined(IS_ENGINE_USE_ADMOB)
    m_admobManager = nullptr;
#endif // definded
#endif // defined
}

GameDisplay::~GameDisplay() {}

void GameDisplay::setOptionIndex(int optionIndexValue, bool callWhenClick, float buttonScale)
{
    if (m_waitTime == 0)
    {
        m_gameSysExt.useVibrate(m_vibrateTimeDuration);
        //////////////////////////////////////////////////////////
        #if !defined(__ANDROID__)
        GSMplaySound("change_option");
        #endif
        //////////////////////////////////////////////////////////
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

void GameDisplay::setWindowTitle(const sf::String &title)
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

void GameDisplay::updateMsgBox(float const &DELTA_TIME, sf::Color textDefaultColor, sf::Color selectedTextColor)
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

    // Avoid the long pressing button effect
    if (!m_msgBoxMouseInCollison && m_gameSysExt.isPressed(
                                                           #if !defined(__ANDROID__)
                                                           is::GameSystem::ValidationButton::MOUSE
                                                           #endif
                                                           ))
        m_gameSysExt.m_keyIsPressed = true;

    if (m_msgWaitTime == 255 && m_windowIsActive)
    {
        // If is YES / NO message box
        if (m_mbYesNo)
        {
            if (((sf::Keyboard::isKeyPressed(is::GameConfig::KEY_LEFT) &&
                  !mouseCollision(m_sprMsgBoxButton2)) ||
                  mouseCollision(m_sprMsgBoxButton1)) && m_msgAnswer == MsgAnswer::NO)
            {
                m_gameSysExt.useVibrate(m_vibrateTimeDuration);
                GSMplaySound("change_option");
                m_msgAnswer = MsgAnswer::YES; // answer = yes
            }
            else if (((sf::Keyboard::isKeyPressed(is::GameConfig::KEY_RIGHT) &&
                     !mouseCollision(m_sprMsgBoxButton1)) ||
                      mouseCollision(m_sprMsgBoxButton2)) && m_msgAnswer == MsgAnswer::YES)
            {
                m_gameSysExt.useVibrate(m_vibrateTimeDuration);
                GSMplaySound("change_option");
                m_msgAnswer = MsgAnswer::NO;  // answer = no
            }
            else if (sf::Keyboard::isKeyPressed(is::GameConfig::KEY_VALIDATION_KEYBOARD) ||
                    ((mouseCollision(m_sprMsgBoxButton1) ||
                      mouseCollision(m_sprMsgBoxButton2)) &&
                      m_gameSysExt.isPressed() && !m_gameSysExt.m_keyIsPressed))
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
        else // If is OK message box
        {
            if (mouseCollision(m_sprMsgBoxButton3) && m_msgAnswer == MsgAnswer::NO)
            {
                m_gameSysExt.useVibrate(m_vibrateTimeDuration);
                GSMplaySound("change_option");
                m_msgAnswer = MsgAnswer::YES; // answer = OK
                is::setSFMLObjFillColor(m_txtMsgBoxOK, selectedTextColor);
            }
            else if (((sf::Keyboard::isKeyPressed(is::GameConfig::KEY_VALIDATION_KEYBOARD) || m_keyBackPressed) &&
                     !mouseCollision(m_sprMsgBoxButton3)) || (mouseCollision(m_sprMsgBoxButton3) &&
                     m_gameSysExt.isPressed() && !m_gameSysExt.m_keyIsPressed)
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
                m_gameSysExt.useVibrate(m_vibrateTimeDuration);
            }
            else GSMplaySound("cancel");
        }
        else
        {
            GSMplaySound("select_option");
            m_gameSysExt.useVibrate(m_vibrateTimeDuration);
        }
    }
}

void GameDisplay::updateTimeWait(float const &DELTA_TIME)
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
        m_surface.draw(m_recMsgBox);
        m_surface.draw(m_sprMsgBox);

        if (m_mbYesNo)
        {
            m_surface.draw(m_txtMsgBoxYes);
            m_surface.draw(m_txtMsgBoxNo);
            m_surface.draw(m_sprMsgBoxButton1);
            m_surface.draw(m_sprMsgBoxButton2);
        }
        else
        {
            m_surface.draw(m_txtMsgBoxOK);
            m_surface.draw(m_sprMsgBoxButton3);
        }

        m_surface.draw(m_txtMsgBox);
    }
}

void GameDisplay::drawScreen()
{
    #if defined(__ANDROID__)
    // On Android when the window is no longer active, nothing is displayed just a black screen.
    // Its allows to optimize the application
    if (m_windowIsActive)
    {
    #endif // defined
        m_surface.clear(m_windowBgColor);
        draw();
    #if defined(__ANDROID__)
    }
    else
    {
        m_window.clear(m_windowBgColor);
        m_window.display();
    }
    #endif // defined
}

void GameDisplay::showTempLoading(float time)
{
    float timeToQuit(0.f);
    sf::Texture texTmploading, texTmploading2;
    texTmploading.loadFromFile(is::GameConfig::GUI_DIR + "temp_loading.png");
    texTmploading2.loadFromFile(is::GameConfig::GUI_DIR + "loading_icon.png");
    sf::Sprite sprTmploading, sprTmploading2;
    is::createSprite(texTmploading, sprTmploading, sf::IntRect(0, 0, 640, 480),
                     sf::Vector2f(0.f, 0.f), sf::Vector2f(320.f, 240.f));
    is::createSprite(texTmploading2, sprTmploading2, sf::IntRect(0, 0, 32, 32),
                     sf::Vector2f(304.f, 240.f), sf::Vector2f(16.f, 16.f));
    while (timeToQuit < time)
    {
        float dTime = getDeltaTime();
        timeToQuit += is::getMSecond(dTime);
        sprTmploading2.rotate((5.f * is::VALUE_CONVERSION) * dTime);
        sf::Event ev;
        while (m_window.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed)
            {
                m_window.close();
                #if defined (__ANDROID__)
                std::terminate();
                #else
                m_isRunning = false;
                #endif // defined
            }
        }
        m_window.clear(sf::Color::Black);
        m_surface.draw(sprTmploading);
        m_surface.draw(sprTmploading2);
        m_window.display();
    }
}

void GameDisplay::loadParentResources()
{
    // Load sound
    GSMaddSound("change_option", is::GameConfig::SFX_DIR + "change_option.ogg");
    GSMaddSound("cancel", is::GameConfig::SFX_DIR + "cancel.ogg");
    GSMaddSound("select_option", is::GameConfig::SFX_DIR + "select_option.ogg");

    // Load message box sprite
    loadSFMLObjResource(m_texMsgBox, is::GameConfig::GUI_DIR + "confirm_box.png");
    loadSFMLObjResource(m_texMsgButton, is::GameConfig::GUI_DIR + "confirm_box_button.png");

    is::createSprite(m_texMsgBox, m_sprMsgBox, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f));
    is::createSprite(m_texMsgButton, m_sprMsgBoxButton1, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f));
    is::createSprite(m_texMsgButton, m_sprMsgBoxButton2, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f));
    is::createSprite(m_texMsgButton, m_sprMsgBoxButton3, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f));

    is::createRectangle(m_recMsgBox, sf::Vector2f(m_viewW + 40.f, m_viewH + 40.f), sf::Color(0, 0, 0, 200), 0.f, 0.f);

    is::centerSFMLObj(m_sprMsgBox);
    is::centerSFMLObj(m_sprMsgBoxButton1);
    is::centerSFMLObj(m_sprMsgBoxButton2);
    is::centerSFMLObj(m_sprMsgBoxButton3);

    // Load font
    loadSFMLObjResource(m_fontSystem, GameConfig::FONT_DIR + "sansation.ttf");
    loadSFMLObjResource(m_fontMsg, GameConfig::FONT_DIR + "brush_script_std_medium.ttf");

    is::createText(m_fontSystem, m_txtMsgBox, "", 0.f, 0.f, 20);
    is::createText(m_fontSystem, m_txtMsgBoxYes, is::lang::pad_answer_yes[m_gameSysExt.m_gameLanguage],
                   0.f, 0.f, true, 18);
    is::createText(m_fontSystem, m_txtMsgBoxNo, is::lang::pad_answer_no[m_gameSysExt.m_gameLanguage],
                   0.f, 0.f, true, 18);
    is::createText(m_fontSystem, m_txtMsgBoxOK, is::lang::pad_answer_ok[m_gameSysExt.m_gameLanguage],
                   0.f, 0.f, true, 18);
}

void GameDisplay::setIsRunning(bool val)
{
    m_isRunning = val;
}

void GameDisplay::setIsPlaying(bool val)
{
    m_isPlaying = val;
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

bool GameDisplay::getIsRunning() const
{
    return m_isRunning;
}

#if defined(IS_ENGINE_USE_SDM)
void GameDisplay::SDMmanageScene()
{
    DELTA_TIME = getDeltaTime();
    updateTimeWait(DELTA_TIME);

    // even loop
    SDMmanageSceneEvents();

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
                updateMsgBox(DELTA_TIME);

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
        // draw scene objects
        for (std::list<std::shared_ptr<MainObject>>::iterator it = m_SDMsceneObjects.begin();
            it != m_SDMsceneObjects.end(); ++it)
        {
            if (is::instanceExist(*it))
            {
                if ((*it)->m_SDMcallDraw)
                {
                    (*it)->draw(m_surface);
                }
            }
        }
    }
    drawMsgBox();
}
#endif // defined

#if defined(IS_ENGINE_USE_GSM)
void GameDisplay::GSMplaySound(std::string name)
{
    bool soundExist(false);
    WITH (m_GSMsound.size())
    {
        if (m_GSMsound[_I]->getName() == name)
        {
            soundExist = true;
            if (m_GSMsound[_I]->getFileIsLoaded()) m_gameSysExt.playSound(m_GSMsound[_I]->getSound());
            else is::showLog("ERROR: Sound exists but can't play <" + name + "> sound!");
            break;
        }
    }
    if (!soundExist) is::showLog("ERROR: Can't play <" + name + "> sound because sound not exists!");
}

void GameDisplay::GSMpauseSound(std::string name)
{
    bool soundExist(false);
    WITH (m_GSMsound.size())
    {
        if (m_GSMsound[_I]->getName() == name)
        {
            soundExist = true;
            if (m_GSMsound[_I]->getFileIsLoaded())
            {
                if (m_GSMsound[_I]->getSound().getStatus() == sf::Sound::Playing) m_GSMsound[_I]->getSound().pause();
            }
            else is::showLog("ERROR: Sound exists but can't stop <" + name + "> sound!");
            break;
        }
    }
    if (!soundExist) is::showLog("ERROR: Can't pause <" + name + "> sound because sound not exists!");
}

void GameDisplay::GSMplayMusic(std::string name)
{
    bool musicExist(false);
    WITH (m_GSMmusic.size())
    {
        if (m_GSMmusic[_I]->getName() == name)
        {
            musicExist = true;
            if (m_GSMmusic[_I]->getFileIsLoaded()) m_gameSysExt.playMusic(m_GSMmusic[_I]->getMusic());
            else is::showLog("ERROR: Music exists but can't play <" + name + "> music!");
            break;
        }
    }
    if (!musicExist) is::showLog("ERROR: Can't play <" + name + "> music because music not exists!");
}

void GameDisplay::GSMpauseMusic(std::string name)
{
    bool musicExist(false);
    WITH (m_GSMmusic.size())
    {
        if (m_GSMmusic[_I]->getName() == name)
        {
            musicExist = true;
            if (m_GSMmusic[_I]->getFileIsLoaded())
            {
                if (m_GSMmusic[_I]->getMusic().getStatus() == sf::Sound::Playing) m_GSMmusic[_I]->getMusic().pause();
            }
            else is::showLog("ERROR: Music exists but can't stop <" + name + "> music!");
            break;
        }
    }
    if (!musicExist) is::showLog("ERROR: Can't pause <" + name + "> music because music not exists!");
}
#endif // defined
}
