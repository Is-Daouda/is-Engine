#include "GameMenu.h"

GameMenu::GameMenu(sf::RenderWindow &window, sf::View &view, sf::RenderTexture &surface, GameSystemExtended &gameSysExt):
    GameDisplay(window, view, surface, gameSysExt, sf::Color::White),
    m_cancelBt(this),
    m_gameOptionIndex(0),
    m_oscillation(0.f),
    m_xPos(38.f),
    m_yPos(210.f),
    m_bgX(0.f),
    m_bgY(0.f),
    m_sprButtonPemuteScale(1.f),
    m_timeClick(0.f),
    m_isClicked(false),
    m_padCfgClicked(false),
    m_saveFileOpen(false),
    m_closeApplication(false),
    m_pageName(PAGE_MAIN_MENU)
{
    for (unsigned int i(0); i < is::arraySize(m_txtOptionScale); i++) m_txtOptionScale[i] = 1.f;
}

GameMenu::~GameMenu()
{
}

void GameMenu::step()
{
    DELTA_TIME = getDeltaTime();

    updateTimeWait(DELTA_TIME);

    const short OP_START_GAME(0),
                OP_CONTINUE(1),
                OP_CONFIG_PAD(2);
    const short OP_MENU_SND(0),
                OP_MENU_MSC(1),
                OP_MENU_VIBRATE(2),
                OP_MENU_LANG(3);

    m_padCfgClicked = false;

    // allow to know is mouse is in collision with sprite
    bool mouseInCollisonPad(false);
    bool mouseInCollisonOption(false);

    // even loop
    while (m_window.pollEvent(m_event))
    {
        controlEventFocusClosing();

        if (m_event.type == sf::Event::KeyReleased)
        {
            if (m_event.key.code == is::GameConfig::KEY_CANCEL)
            {
                m_keyBackPressed = true;
            }
        }
    }

    // camera
    setView();

    // starting mechanism
    if (m_sceneStart)
    {
        // window has focus
        if (m_windowIsActive)
        {
            if (!m_showMsg)
            {
                // allows activated use of buttons
                if (!m_gameSysExt.keyIsPressed(is::GameConfig::KEY_UP) &&
                    !m_gameSysExt.keyIsPressed(is::GameConfig::KEY_DOWN) &&
                    !m_gameSysExt.isPressed())
                        m_gameSysExt.m_keyIsPressed = false;

                // m_isClose allow to deactivate scene object
                if (!m_isClose)
                {
                    // check with collision with sprite
                    if (mouseCollision(m_cancelBt.getSprite())) m_cancelBt.setAlpha(255);

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      MAIN MENU
//////////////////////////////////////////////////////////////////////////////////////////////////////
                    if (m_pageName != PAGE_PAD_CONFIG)
                    {
                        if (mouseCollision(m_sprPad1) || mouseCollision(m_sprPad2) ||
                            mouseCollision(m_sprPad3)) mouseInCollisonPad = true;

                        // check collision with option buttons
                        for (unsigned int i(0); i < is::arraySize(m_txtOptionValue); i++)
                        {
                            if (mouseCollision(m_txtOptionValue[i])) mouseInCollisonOption = true;
                        }

                        // change option with mouse (touch on Android)
                        if (mouseCollision(m_sprPad1) && m_optionIndex != OP_START_GAME)  setOptionIndex(OP_START_GAME, true, 1.4f);
                        if (mouseCollision(m_sprPad2) && m_optionIndex != OP_CONTINUE)    setOptionIndex(OP_CONTINUE, true, 1.4f);
                        if (mouseCollision(m_sprPad3) && m_optionIndex != OP_CONFIG_PAD)  setOptionIndex(OP_CONFIG_PAD, true, 1.4f);

                        // avoid the long pressing button effect
                        if (!mouseInCollisonPad && !mouseInCollisonOption && m_gameSysExt.isPressed(is::GameSystem::ValidationButton::MOUSE))
                            m_gameSysExt.m_keyIsPressed = true;

                        // change option with keyboard (only for PC)
                        if (!m_gameSysExt.m_keyIsPressed && !mouseInCollisonPad)
                        {
                            if (m_gameSysExt.keyIsPressed(is::GameConfig::KEY_UP)) setOptionIndex(-1, false, 1.4f);
                            else if (m_gameSysExt.keyIsPressed(is::GameConfig::KEY_DOWN)) setOptionIndex(1, false, 1.4f);
                            if (m_optionIndex < 0) m_optionIndex = OP_CONFIG_PAD;
                            if (m_optionIndex > OP_CONFIG_PAD) m_optionIndex = 0;
                        }

                        // validate menu option
                        if ((m_gameSysExt.isPressed(is::GameSystem::ValidationButton::KEYBOARD) ||
                            (m_gameSysExt.isPressed(is::GameSystem::ValidationButton::MOUSE) && mouseInCollisonPad)) &&
                            (m_waitTime == 0 && !m_gameSysExt.m_keyIsPressed))
                        {
                            auto playSelectSnd = [this]()
                            {
                                GSMplaySound("select_option"); // We play this sound
                                m_sprButtonSelectScale = 1.4f;
                                m_gameSysExt.useVibrate(m_vibrateTimeDuration);
                            };

                            switch (m_optionIndex)
                            {
                            case OP_START_GAME:
                                if (!m_gameSysExt.fileExist(is::GameConfig::GAME_DATA_FILE))
                                {
                                    playSelectSnd();
                                    m_gameSysExt.saveData(is::GameConfig::GAME_DATA_FILE);
                                    m_gameSysExt.m_launchOption = is::DisplayOption::GAME_LEVEL;
                                    GSMgetMusic("game_music")->stop();
                                    m_isClose = true;
                                }
                                else
                                {
                                    showMessageBox(is::lang::msg_erase_data[m_gameSysExt.m_gameLanguage]);
                                }
                            break;

                            // load current level saved
                            case OP_CONTINUE:
                                if (m_gameSysExt.fileExist(is::GameConfig::GAME_DATA_FILE))
                                {
                                    GSMplaySound("select_option"); // We play this sound
                                    m_gameSysExt.useVibrate(m_vibrateTimeDuration);
                                    m_gameSysExt.m_currentLevel = m_gameSysExt.m_gameProgression;
                                    m_gameSysExt.m_launchOption = is::DisplayOption::GAME_LEVEL;
                                    GSMgetMusic("game_music")->stop();
                                    m_isClose = true;
                                }
                            break;

                            // show game pad configuration option
                            case OP_CONFIG_PAD:
                                #if !defined(__ANDROID__)
                                showMessageBox(is::lang::msg_controller_opt_error[m_gameSysExt.m_gameLanguage], false);
                                #else
                                playSelectSnd();
                                m_gameSysExt.m_keyIsPressed = true;
                                m_pageName = PAGE_PAD_CONFIG;
                                #endif // defined
                            break;
                            }
                            m_keyBackPressed = false;
                        }
                        if (m_pageName != PAGE_PAD_CONFIG)
                        {
                            // Quit game
                            if (m_keyBackPressed)
                            {
                                showMessageBox(is::lang::msg_quit_game[m_gameSysExt.m_gameLanguage]);
                                m_closeApplication = true;
                                m_keyBackPressed = false;
                            }
                        }

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      GAME OPTION
//////////////////////////////////////////////////////////////////////////////////////////////////////

                        // mouse hover effect
                        auto setTxtOpionScale = [this](short int m_txtOptionIndex)
                        {
                            //////////////////////////////////////////////////////////
                            #if !defined(__ANDROID__)
                            GSMplaySound("change_option"); // We play this sound
                            #endif
                            //////////////////////////////////////////////////////////
                            m_txtOptionScale[m_txtOptionIndex] = 1.2f;
                            m_gameOptionIndex = m_txtOptionIndex;
                        };

                        if (mouseCollision(m_txtOptionValue[OP_MENU_SND]) && m_gameOptionIndex != OP_MENU_SND)
                        {
                            setTxtOpionScale(OP_MENU_SND);
                        }
                        else if (mouseCollision(m_txtOptionValue[OP_MENU_MSC]) && m_gameOptionIndex != OP_MENU_MSC)
                        {
                            setTxtOpionScale(OP_MENU_MSC);
                        }
                        else if (mouseCollision(m_txtOptionValue[OP_MENU_VIBRATE]) && m_gameOptionIndex != OP_MENU_VIBRATE)
                        {
                            setTxtOpionScale(OP_MENU_VIBRATE);
                        }
                        else if (mouseCollision(m_txtOptionValue[OP_MENU_LANG]) && m_gameOptionIndex != OP_MENU_LANG)
                        {
                            setTxtOpionScale(OP_MENU_LANG);
                        }

                        if (m_gameSysExt.isPressed() && mouseInCollisonOption && m_waitTime == 0 && !m_gameSysExt.m_keyIsPressed)
                        {
                            // validate option
                            auto setKeyToTrue = [this](short int m_txtOptionIndex)
                            {
                                m_txtOptionScale[m_txtOptionIndex] = 1.4f;
                                m_gameSysExt.m_keyIsPressed = true;
                                m_gameSysExt.saveConfig(is::GameConfig::CONFIG_FILE);
                            };

                            switch (m_gameOptionIndex)
                            {
                                // activate / deactivate sound
                                case OP_MENU_SND:
                                    if (!m_gameSysExt.m_enableSound)
                                    {
                                        m_gameSysExt.m_enableSound = true;
                                        GSMplaySound("select_option"); // We play this sound
                                    }
                                    else m_gameSysExt.m_enableSound = false;
                                    setKeyToTrue(OP_MENU_SND);
                                break;

                                // activate / deactivate music
                                case OP_MENU_MSC:
                                    if (!m_gameSysExt.m_enableMusic)
                                    {
                                        m_gameSysExt.m_enableMusic = true;
                                        GSMplaySound("select_option"); // We play this sound
                                        GSMgetMusic("game_music")->play();
                                    }
                                    else
                                    {
                                        GSMgetMusic("game_music")->pause();
                                        m_gameSysExt.m_enableMusic = false;
                                    }
                                    setKeyToTrue(OP_MENU_MSC);
                                break;

                                case OP_MENU_VIBRATE:
                                    if (!m_gameSysExt.m_enableVibrate)
                                    {
                                        m_gameSysExt.m_enableVibrate = true;
                                        GSMplaySound("select_option"); // We play this sound
                                        m_gameSysExt.useVibrate(m_vibrateTimeDuration);
                                    }
                                    else m_gameSysExt.m_enableVibrate = false;
                                    setKeyToTrue(OP_MENU_VIBRATE);
                                break;

                                // change game language
                                case OP_MENU_LANG:
                                    // With each click we change the language index
                                    m_gameSysExt.m_gameLanguage++;

                                    // Here the enumeration FRANCAIS represents the value of the index of the last language
                                    // If the variable is greater than this value we return to the first language
                                    // because there are more languages
                                    if (m_gameSysExt.m_gameLanguage > is::lang::GameLanguage::FRANCAIS) m_gameSysExt.m_gameLanguage = is::lang::GameLanguage::ENGLISH;
                                    GSMplaySound("select_option"); // We play this sound

                                    m_txtStartGame.setString(is::lang::pad_new_game[m_gameSysExt.m_gameLanguage]);
                                    m_txtContinue.setString(is::lang::pad_continue_game[m_gameSysExt.m_gameLanguage]);
                                    m_txtPadConfig.setString(is::lang::pad_controller[m_gameSysExt.m_gameLanguage]);
                                    m_txtPermuteAB.setString(is::lang::msg_permute_AB[m_gameSysExt.m_gameLanguage] + getABPlace());
                                    m_txtMovePad.setString(is::lang::msg_how_move_control[m_gameSysExt.m_gameLanguage]);
                                    is::centerSFMLObj(m_txtStartGame);
                                    is::centerSFMLObj(m_txtContinue);
                                    is::centerSFMLObj(m_txtPadConfig);
                                    is::centerSFMLObj(m_txtPermuteAB);
                                    is::centerSFMLObj(m_txtMovePad);

                                    setKeyToTrue(OP_MENU_LANG);
                                break;
                            }
                        }

                        // update game option
                        if (m_gameSysExt.m_enableSound) m_txtOptionValue[OP_MENU_SND].setString(is::lang::opt_enable_sound[m_gameSysExt.m_gameLanguage]);
                        else m_txtOptionValue[OP_MENU_SND].setString(is::lang::opt_disable_sound[m_gameSysExt.m_gameLanguage]);
                        if (m_gameSysExt.m_enableMusic) m_txtOptionValue[OP_MENU_MSC].setString(is::lang::opt_enable_music[m_gameSysExt.m_gameLanguage]);
                        else m_txtOptionValue[OP_MENU_MSC].setString(is::lang::opt_disable_music[m_gameSysExt.m_gameLanguage]);
                        if (m_gameSysExt.m_enableVibrate) m_txtOptionValue[OP_MENU_VIBRATE].setString(is::lang::opt_enable_vibrate[m_gameSysExt.m_gameLanguage]);
                        else m_txtOptionValue[OP_MENU_VIBRATE].setString(is::lang::opt_disable_vibrate[m_gameSysExt.m_gameLanguage]);
                        m_txtOptionValue[OP_MENU_LANG].setString(is::lang::opt_game_lang[m_gameSysExt.m_gameLanguage]);
                    }

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      GAME KEY CONFIG (ONLY FOR ANDROID)
//////////////////////////////////////////////////////////////////////////////////////////////////////
                    else
                    {
                        auto setKeyPos = [this](int index, float &xVar, float &yVar)
                        {
                            sf::RectangleShape rec;
                            if (mouseCollision(m_sprJoystick[index], rec) && m_gameSysExt.isPressed())
                            {
                                m_padCfgClicked = true;
                                bool haveError(false), canMove(true);
                                auto checkPadDistance = [this, &rec, &canMove](int _index)
                                {
                                    if (is::pointDistance(is::getSFMLObjX(rec), is::getSFMLObjY(rec),
                                                      is::getSFMLObjX(m_sprJoystick[_index]), is::getSFMLObjY(m_sprJoystick[_index])) < 160.f) canMove = false;
                                };
                                if (index == 0) checkPadDistance(1); else checkPadDistance(0);

                                if (canMove)
                                {
                                    float _x(((is::getSFMLObjX(rec) > m_viewX) ? 1.f : -1.f) * is::pointDistance(is::getSFMLObjX(rec),
                                             is::getSFMLObjY(rec), m_viewX, is::getSFMLObjY(rec)));
                                    float _y(((is::getSFMLObjY(rec) > m_viewY) ? 1.f : -1.f) * is::pointDistance(is::getSFMLObjX(rec),
                                             is::getSFMLObjY(rec), is::getSFMLObjX(rec), m_viewY));

                                    float _xSize(67.f), _ySize(67.f);
                                    if (index == 1)
                                    {
                                        _xSize = 72.f;
                                        _ySize = 37.f;
                                    }

                                    if (is::getSFMLObjX(rec) < _xSize)
                                    {
                                        _x = _xSize;
                                        haveError = true;
                                    }
                                    else if (is::getSFMLObjX(rec) > m_viewX + m_viewW / 2.f - _xSize)
                                    {
                                        haveError = true;
                                        _x = m_viewX + m_viewW / 2.f - _xSize;
                                    }
                                    else xVar = _x;

                                    if (is::getSFMLObjY(rec) < m_viewY + ((index == 0) ? 32.f : 4.f))
                                    {
                                        _y = _ySize + 32.f;
                                        haveError = true;
                                    }
                                    else if (is::getSFMLObjY(rec) > m_viewY + m_viewH / 2.f - _ySize)
                                    {
                                        _y = m_viewY + m_viewH / 2.f - _ySize;
                                        haveError = true;
                                    }
                                    else yVar = _y;
                                } else haveError = true;
                                is::setSFMLObjOutlineColor(m_recSelectPad, ((haveError) ? sf::Color(255, 0, 0) : sf::Color(0, 255, 0)));
                                is::setSFMLObjSize(m_recSelectPad, is::getSFMLObjWidth(m_sprJoystick[index]), is::getSFMLObjHeight(m_sprJoystick[index]));
                                is::centerSFMLObj(m_recSelectPad);
                                is::setSFMLObjX_Y(m_recSelectPad, is::getSFMLObjX(m_sprJoystick[index]), is::getSFMLObjY(m_sprJoystick[index]));
                            }
                        };

                        setKeyPos(0, m_gameSysExt.m_padDirXPos, m_gameSysExt.m_padDirYPos);
                        setKeyPos(1, m_gameSysExt.m_padActionXPos, m_gameSysExt.m_padActionYPos);
                        is::setSFMLObjX_Y(m_sprJoystick[0],
                                          m_viewX + m_gameSysExt.m_padDirXPos,
                                          m_viewY + m_gameSysExt.m_padDirYPos);
                        is::setSFMLObjX_Y(m_sprJoystick[1],
                                          m_viewX + m_gameSysExt.m_padActionXPos,
                                          m_viewY + m_gameSysExt.m_padActionYPos);

                        // This avoids the repetition of certain actions when we touch the buttons
                        if (m_timeClick > 10.f &&
                            (mouseCollision(m_sprPermuteAB) || mouseCollision(m_sprAddAlpha) || mouseCollision(m_sprReduceAlpha)) &&
                                        m_gameSysExt.isPressed())
                            m_timeClick = 15.f;
                        else is::decreaseVar(DELTA_TIME, m_timeClick, 1.f, 0.f, 0.f);

                        if (mouseCollision(m_sprAddAlpha) && m_gameSysExt.isPressed())
                        {
                            if (static_cast<int>(m_timeClick) == 0) GSMplaySound("select_option"); // We play this sound
                            m_timeClick = 15.f;
                            if (m_gameSysExt.m_padAlpha < 250) m_gameSysExt.m_padAlpha += ((is::VALUE_CONVERSION * 2.f) * DELTA_TIME);
                            is::setSFMLObjTexRec(m_sprAddAlpha, 64, 0);
                        }
                        else is::setSFMLObjTexRec(m_sprAddAlpha, 32, 0);

                        if (mouseCollision(m_sprReduceAlpha) && m_gameSysExt.isPressed())
                        {
                            if (static_cast<int>(m_timeClick) == 0) GSMplaySound("select_option"); // We play this sound
                            m_timeClick = 15.f;
                            if (m_gameSysExt.m_padAlpha > 20) m_gameSysExt.m_padAlpha -= ((is::VALUE_CONVERSION * 2.f) * DELTA_TIME);
                            is::setSFMLObjTexRec(m_sprReduceAlpha, 128, 0);
                        }
                        else is::setSFMLObjTexRec(m_sprReduceAlpha, 96, 0);

                        if (mouseCollision(m_sprPermuteAB) && m_gameSysExt.isPressed() && static_cast<int>(m_timeClick) == 0)
                        {
                            GSMplaySound("select_option"); // We play this sound
                            m_timeClick = 15.f;
                            m_gameSysExt.m_permutePadAB = !m_gameSysExt.m_permutePadAB;
                            m_sprButtonPemuteScale = 1.3f;
                            is::setSFMLObjTexRec(m_sprJoystick[1], 134, ((!m_gameSysExt.m_permutePadAB) ? 0 : 67), 144, 67);
                            m_txtPermuteAB.setString(is::lang::msg_permute_AB[m_gameSysExt.m_gameLanguage] + getABPlace());
                            is::centerSFMLObj(m_txtPermuteAB);
                        }

                        for (int i(0); i < 2; i++) is::setSFMLObjAlpha(m_sprJoystick[i], m_gameSysExt.m_padAlpha);

                        if (!mouseInCollisonOption && m_gameSysExt.isPressed()) m_gameSysExt.m_keyIsPressed = true;

                        // hide game pad configuration
                        if ((m_keyBackPressed || (m_gameSysExt.isPressed() && m_cancelBt.isOn())) &&
                            m_waitTime == 0)
                        {
                            m_gameSysExt.savePadConfig(is::GameConfig::GAME_PAD_FILE);
                            GSMplaySound("cancel"); // We play this sound
                            m_gameSysExt.useVibrate(m_vibrateTimeDuration);
                            m_pageName = PAGE_MAIN_MENU;
                            m_keyBackPressed = false;
                        }
                    }

                    // change the color of the texts according to the chosen option
                    setTextAnimation(m_txtStartGame, m_sprPad1, OP_START_GAME);
                    setTextAnimation(m_txtContinue,  m_sprPad2, OP_CONTINUE);
                    setTextAnimation(m_txtPadConfig, m_sprPad3, OP_CONFIG_PAD);

                    // update cancel button
                    m_cancelBt.step(DELTA_TIME);
                }
            }

//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      MESSAGE BOX
//////////////////////////////////////////////////////////////////////////////////////////////////////
            else
            {
                updateMsgBox(DELTA_TIME);

                // when user closes message box in update function execute this instruction
                // "m_waitTime" allow to disable clicks on objects during a moment when user closes message box
                if (!m_showMsg)
                {
                    if (m_closeApplication) // quit game
                    {
                        if (m_msgAnswer == MsgAnswer::YES)
                        {
                            m_window.close();
                            m_isRunning = false;
                        }
                        else
                        {
                            m_waitTime = 20;
                            m_closeApplication = false;
                        }
                    }
                    else if (m_pageName == PAGE_MAIN_MENU)
                    {
                        if (m_optionIndex == OP_START_GAME)
                        {
                            if (m_msgAnswer == MsgAnswer::YES)
                            {
                                m_gameSysExt.initProgress();
                                m_gameSysExt.saveData(is::GameConfig::GAME_DATA_FILE);
                                m_gameSysExt.m_launchOption = is::DisplayOption::GAME_LEVEL;
                                GSMgetMusic("game_music")->stop();
                                m_isClose = true;
                            }
                            else m_waitTime = 20;
                        }
                        else m_waitTime = 20;
                    }
                }
            }
        }
    }

    // title animation
    m_oscillation += is::radToDeg((0.08f * is::VALUE_CONVERSION) * DELTA_TIME);
    is::setSFMLObjX_Y(m_txtGameTitle, 65.f, 32.f + is::lengthDirY(5.f, m_oscillation));

    // background animation
    if (m_bgX > -32.f) m_bgX -= (0.5f * is::VALUE_CONVERSION) * DELTA_TIME; else m_bgX = 0.f;
    if (m_bgY > -32.f) m_bgY -= (0.5f * is::VALUE_CONVERSION) * DELTA_TIME; else m_bgY = 0.f;
    is::setSFMLObjX_Y(m_sprScreenBG, m_bgX, m_bgY);

    // game option texts animation
    for (unsigned int i(0); i < is::arraySize(m_txtOptionValue); i++)
    {
        setTextAnimation(m_txtOptionValue[i], m_gameOptionIndex, i);
        is::scaleAnimation(DELTA_TIME, m_txtOptionScale[i], m_txtOptionValue[i]);
    }

    // PAD animation
    is::scaleAnimation(DELTA_TIME, m_sprButtonSelectScale, m_sprButtonSelect, m_sprPad1.getScale().x);
    is::scaleAnimation(DELTA_TIME, m_sprButtonPemuteScale, m_sprPermuteAB, 1);

    if (m_isClose)
    {
        m_sceneStart = false;
        m_isRunning = false;
    }
}
