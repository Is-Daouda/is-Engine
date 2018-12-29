#include "GameMenu.h"

GameMenu::GameMenu(sf::RenderWindow &window, DisplayOption &m_launchOption, GameSystemExtended &gameSysExt):
    GameDisplay(window, m_launchOption, gameSysExt, sf::Color::Black),
    levelIndex(0),
    m_gameOptionIndex(0),
    TXT_OPTION_NUMBER(3),
    m_isStarted(false),
    m_saveFileOpen(false),
    m_isClosed(false),
    m_closeApplication(false)
{
    for(int i(0); i < TXT_OPTION_NUMBER; i++) m_txtOptionScale[i] = 0.f;

    // define return button
    keyBack = sf::Keyboard::Escape;
}

GameMenu::~GameMenu()
{
}

void GameMenu::step()
{
    // delta time
    float DELTA_TIME = getDeltaTime();

    // wait time when cancel option
    if (m_waitTime > 0) m_waitTime -= is::getMSecond<int>(DELTA_TIME);
    else m_waitTime = 0;

    const short OP_START_GAME(0),
                OP_CONTINUE(1);
    const short OP_MENU_SND(0),
                OP_MENU_MSC(1),
                OP_MENU_VIBRATE(2);

    // allow to know if mouse touch main menu components
    bool mouseInCollisonText(false);
    bool mouseInCollisonSprite(false);

    // event loop
    while (m_app.pollEvent(m_event))
    {
        controlEventFocusClosing();
        if (m_event.type == sf::Event::KeyReleased)
        {
            if (m_event.key.code == keyBack) m_keyBackPressed = true;
        }
    }

    // view
    m_view.setCenter(m_viewX, m_viewY);
    m_app.setView(m_view);

    auto setButtonSelectScale = [this]()
    {
        m_sprButtonSelectScale = 1.4f;
    };

    // launch the scene
    if (m_isStarted)
    {
        // application has focus
        if (m_appIsActive)
        {
            if (!m_showMsg)
            {
                // allow to activate button
                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
                    !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
                    !sf::Keyboard::isKeyPressed(sf::Keyboard::Return) &&
                    !m_gameSysExt.isPressed()
                    ) m_gameSysExt.m_keyIsPressed = false;

                if (!m_isClosed)
                {
                    // check collision with option component
                    for (int i(0); i < TXT_OPTION_NUMBER; i++)
                    {
                        if (is::mouseCollision(m_app, m_txtOptionValue[i])) mouseInCollisonText = true;
                    }

                    // check collision on buttons
                    for(int i(0); i < 2; i++)
                    {
                        if (is::mouseCollision(m_app, m_sprButton[i])) mouseInCollisonSprite = true;
                    }

                    // avoid press key loop
                    if (!mouseInCollisonText && !mouseInCollisonSprite && m_gameSysExt.isPressed()) m_gameSysExt.m_keyIsPressed = true;

                    auto setTxtOpionScale = [this](short int m_txtOptionIndex)
                    {
                        ////////////////////////////////////////////////////////////
                        // PC version code
                        #if !defined(__ANDROID__)
                        m_gameSysExt.playSound(m_sndSwitch);
                        #endif
                        ////////////////////////////////////////////////////////////
                        m_txtOptionScale[m_txtOptionIndex] = 1.2f;
                        m_gameOptionIndex = m_txtOptionIndex;
                    };

                    if (is::mouseCollision(m_app, m_txtOptionValue[OP_MENU_SND]) && m_gameOptionIndex != OP_MENU_SND)
                        setTxtOpionScale(OP_MENU_SND);
                    else if (is::mouseCollision(m_app, m_txtOptionValue[OP_MENU_MSC]) && m_gameOptionIndex != OP_MENU_MSC)
                        setTxtOpionScale(OP_MENU_MSC);
                    else if (is::mouseCollision(m_app, m_txtOptionValue[OP_MENU_VIBRATE]) && m_gameOptionIndex != OP_MENU_VIBRATE)
                        setTxtOpionScale(OP_MENU_VIBRATE);

                    if (((m_gameSysExt.isPressed() && mouseInCollisonText)) && m_waitTime == 0 && !m_gameSysExt.m_keyIsPressed)
                    {
                        // validate option
                        auto setKeyToTrue = [this](short int m_txtOptionIndex)
                        {
                            m_txtOptionScale[m_txtOptionIndex] = 1.4f;
                            m_gameSysExt.m_keyIsPressed = true;
                        };

                        switch (m_gameOptionIndex)
                        {
                            // activate / deactivate sound
                            case OP_MENU_SND:
                                if (!m_gameSysExt.m_enableSound)
                                {
                                    m_gameSysExt.m_enableSound = true;
                                    m_gameSysExt.playSound(m_sndSelectOption);
                                }
                                else m_gameSysExt.m_enableSound = false;
                                setKeyToTrue(OP_MENU_SND);
                            break;

                            // activate / deactivate music
                            case OP_MENU_MSC:
                                if (!m_gameSysExt.m_enableMusic)
                                {
                                    m_gameSysExt.m_enableMusic = true;
                                    m_gameSysExt.playSound(m_sndSelectOption);
                                }
                                else m_gameSysExt.m_enableMusic = false;
                                setKeyToTrue(OP_MENU_MSC);
                            break;

                            case OP_MENU_VIBRATE:
                                if (!m_gameSysExt.m_enableVibrate)
                                {
                                    m_gameSysExt.m_enableVibrate = true;
                                    m_gameSysExt.playSound(m_sndSelectOption);
                                    ////////////////////////////////////////////////////////////
                                    #if defined(__ANDROID__)
                                    m_gameSysExt.useVibrate(m_vibrateTimeDuration);
                                    #endif
                                    ////////////////////////////////////////////////////////////
                                }
                                else m_gameSysExt.m_enableVibrate = false;
                                setKeyToTrue(OP_MENU_VIBRATE);
                            break;
                        }
                        m_gameSysExt.saveConfig(is::CONFIG_FILE); // save configuration change
                    }

                    // update text when option change
                    if (m_gameSysExt.m_enableSound)   m_txtOptionValue[OP_MENU_SND].setString("Enable SOUND            : YES");
                    else                              m_txtOptionValue[OP_MENU_SND].setString("Enable SOUND            : NO");
                    if (m_gameSysExt.m_enableMusic)   m_txtOptionValue[OP_MENU_MSC].setString("Enable MUSIC             : YES");
                    else                              m_txtOptionValue[OP_MENU_MSC].setString("Enable MUSIC             : NO");
                    if (m_gameSysExt.m_enableVibrate) m_txtOptionValue[OP_MENU_VIBRATE].setString("Enable VIBRATE          : YES");
                    else                              m_txtOptionValue[OP_MENU_VIBRATE].setString("Enable VIBRATE          : NO");

                    auto setOptionIndex = [this, &setButtonSelectScale](short int m_optionIndexValue)
                    {
                        ////////////////////////////////////////////////////////////
                        // PC version code
                        #if !defined(__ANDROID__)
                        m_gameSysExt.playSound(m_sndSwitch);
                        #endif
                        ////////////////////////////////////////////////////////////
                        setButtonSelectScale();
                        m_optionIndex = m_optionIndexValue;
                    };

                    // move with mouse
                    if (is::mouseCollision(m_app, m_sprButton[0]) && m_optionIndex != OP_START_GAME)  setOptionIndex(OP_START_GAME);
                    if (is::mouseCollision(m_app, m_sprButton[1]) && m_optionIndex != OP_CONTINUE)    setOptionIndex(OP_CONTINUE);

                    // validate option
                    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || (m_gameSysExt.isPressed() && mouseInCollisonSprite)) &&
                        (m_waitTime == 0 && !m_gameSysExt.m_keyIsPressed))
                    {
                        auto playSelectSnd = [this, &setButtonSelectScale]()
                        {
                            m_gameSysExt.playSound(m_sndSelectOption);
                            setButtonSelectScale();
                            ////////////////////////////////////////////////////////////
                            //  Android version code
                            #if defined(__ANDROID__)
                            m_gameSysExt.useVibrate(m_vibrateTimeDuration);
                            #endif
                            ////////////////////////////////////////////////////////////
                        };

                        switch (m_optionIndex)
                        {
                        // new game
                        case OP_START_GAME:
                            if (!m_gameSysExt.fileExist(is::DATA_FILE))
                            {
                                playSelectSnd();
                                m_gameSysExt.saveData(is::DATA_FILE); // clear date
                                m_launchOption = is::GameDisplay::DisplayOption::GAME_LEVEL;
                                m_isClosed = true;
                            }
                            else
                            {
                                showMessageBox("Erase previous data and start\nnew game?");
                            }
                        break;

                        // continue game
                        case OP_CONTINUE:
                            if (m_gameSysExt.fileExist(is::DATA_FILE))
                            {
                                playSelectSnd();
                                m_gameSysExt.loadData(is::DATA_FILE);
                                m_launchOption = is::GameDisplay::DisplayOption::GAME_LEVEL;
                                m_isClosed = true;
                            }
                        break;
                        }
                        m_keyBackPressed = false;
                    }

                    // Quit game
                    if (m_keyBackPressed)
                    {
                        showMessageBox("Quit game?");
                        m_closeApplication = true;
                        m_keyBackPressed = false;
                    }

                    ////////////////////////////////////////////////////////////
                    // PC version code
                    #if !defined(__ANDROID__)
                    // switch button with keyboard. This code will work until mouse isn't on button
                    if (!mouseInCollisonSprite)
                    {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !m_gameSysExt.m_keyIsPressed)
                        {
                            m_optionIndex--;
                            setButtonSelectScale();
                            m_gameSysExt.playSound(m_sndSwitch);
                            m_gameSysExt.m_keyIsPressed = true;
                        }
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !m_gameSysExt.m_keyIsPressed)
                        {
                            m_optionIndex++;
                            setButtonSelectScale();
                            m_gameSysExt.playSound(m_sndSwitch);
                            m_gameSysExt.m_keyIsPressed = true;
                        }
                    }
                    #endif
                    ////////////////////////////////////////////////////////////

                    // control the limit of option
                    if (m_optionIndex < OP_START_GAME) m_optionIndex = OP_CONTINUE;
                    if (m_optionIndex > OP_CONTINUE)   m_optionIndex = OP_START_GAME;

                    // change text color animation according to button selected
                    setTextAnimation(m_txtStartGame, m_sprButton[0], OP_START_GAME);
                    setTextAnimation(m_txtContinue, m_sprButton[1], OP_CONTINUE);
                }
            }

            ////////////////////////////////////////////////////////////
            /////////////////////// MESSAGE BOX ////////////////////////
            ////////////////////////////////////////////////////////////
            else
            {
                updateMsgBox(DELTA_TIME);

                // when we close message box in 'updateMsgBox()' method, we execute this instructions
                if (!m_showMsg)
                {
                    // when we are closing the application
                    if (m_closeApplication)
                    {
                        if (m_msgAnswer == MsgAnswer::YES)
                        {
                            m_app.close();
                            #if defined (__ANDROID__)
                            std::terminate(); // force the closing of application
                            #else
                            m_isRunning = false;  // quit the main loop
                            #endif // defined
                        }
                        else
                        {
                            m_waitTime = 20;
                            m_closeApplication = false;
                        }
                    }
                    else // when we start new game advice user before clear save file
                    {
                        if (m_optionIndex == OP_START_GAME)
                        {
                            if (m_msgAnswer == MsgAnswer::YES)
                            {
                                // clear user progression
                                m_gameSysExt.initProgress();
                                m_gameSysExt.saveData(is::DATA_FILE);
                                m_launchOption = is::GameDisplay::DisplayOption::GAME_LEVEL;
                                m_isClosed = true;
                            }
                            else m_waitTime = 20;
                        }
                    }
                }
            }
        }
    }

    // animation of option text
    for (int i(0); i < TXT_OPTION_NUMBER; i++)
    {
        setTextAnimation(m_txtOptionValue[i], m_gameOptionIndex, i);
        is::scaleAnimation(DELTA_TIME, m_txtOptionScale[i], m_txtOptionValue[i]);
    }

    // animation of button
    is::scaleAnimation(DELTA_TIME, m_sprButtonSelectScale, m_sprButtonSelect, is::getSFMLObjXScale(m_sprButton[0]));

    // transition effect at beginning
    if (!m_isStarted)
    {
        if (m_alphaRec > 5) m_alphaRec -= static_cast<int>((5.f * is::VALUE_CONVERSION) * DELTA_TIME);
        else
        {
            m_alphaRec = 0;
            m_isStarted = true;
        }
        is::setSFMLRecColor(m_recTransition, sf::Color(0, 0, 0, m_alphaRec));
    }

    // transition effect at ending
    if (m_isClosed)
    {
       if (m_alphaRec < 250) m_alphaRec += static_cast<int>((5.f * is::VALUE_CONVERSION) * DELTA_TIME);
       else
       {
            m_alphaRec = 255;
            m_isRunning = false; // quit the scene main loop
       }
       is::setSFMLRecColor(m_recTransition, sf::Color(0, 0, 0, m_alphaRec));
    }
    is::setSFMLObjX_Y(m_recTransition, m_viewX, m_viewY);
}
