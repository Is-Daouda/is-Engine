#include "GameLevel.h"

void GameLevel::step()
{
    float DELTA_TIME = getDeltaTime();
    int const OP_RESUME_GAME(0),
              OP_RESTART(1),
              OP_QUIT(2);

    // wait time when cancel option
    if (m_waitTime > 0) m_waitTime -= is::getMSecond<int>(DELTA_TIME);
    else m_waitTime = 0;

    // allow to activate key usage
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !m_keyBackPressed) m_pauseKeyPressed = false;

    // even loop
    while (m_app.pollEvent(m_event))
    {
        controlEventFocusClosing();
        if (m_event.type == sf::Event::KeyReleased)
        {
            if (m_event.key.code == sf::Keyboard::Escape)
            {
                m_keyBackPressed = true;
            }
        }
    }

    // if application hasn't focus pause the game
    if (!m_appIsActive && m_isPlaying)
    {
        m_isPlaying = false;
    }

    // update transition data
    is::setSFMLObjX_Y(m_recTransition, m_viewX, m_viewY);
    is::setSFMLRecColor(m_recTransition, sf::Color(0, 0, 0, m_alphaRec));

    // fade in transition at beginning
    if (!m_levelStart)
    {
        if (m_alphaRec > 5) m_alphaRec -= static_cast<int>((4.f * is::VALUE_CONVERSION) * DELTA_TIME);
        else
        {
            m_alphaRec = 0;
            m_levelStart = true;
        }
    }

    // if player lose stop the game
    if (m_player.getHurt())
    {
        m_launchOption = RESTART_LEVEL; // restart level
        m_levelEnd = true;
    }

    auto setButtonSelectScale = [this](float x = 1.4f)
    {
        m_sprButtonSelectScale = x;
    };

    // if level is complete
    if (!m_levelEnd)
    {
        if (m_levelCompleted)
        {
            ////////////////////////////////////////////////////////////
            m_gameSysExt.m_currentLevel++;
            bool canLaunchAd(false);

            // increase progress
            if (m_gameSysExt.m_gameProgression < m_gameSysExt.m_levelNumber)
            {
                canLaunchAd = true;
                m_gameSysExt.m_gameProgression++;
            }

            m_launchAd = canLaunchAd;
            m_gameSysExt.saveData(is::DATA_FILE); // save game
            ////////////////////////////////////////////////////////////

            m_launchOption = NEXT_LEVEL; // go to next level
            m_levelEnd = true;
        }
    }

    // fade in transition to quit game
    if (m_levelEnd)
    {
        if (m_alphaRec < 250) m_alphaRec += static_cast<int>((4.f * is::VALUE_CONVERSION) * DELTA_TIME);
        else
        {
            m_alphaRec = 255;
            m_isRunning = false; // quit scene loop
        }
    }

    if (!m_showMsg)
    {
        if (m_isPlaying)
        {
            // check collision with pause component
            if (is::mouseCollision(m_app, m_pauseBt.getSprite()))
            {
                m_pauseBt.setAlpha(255);
                m_gameSysExt.m_keyIsPressed = true;
            }

            // allow key usage
            if (!m_gameSysExt.actionKeyPressed()) m_gameSysExt.m_keyIsPressed = false;

            // launch pause menu
            if ((((sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || m_keyBackPressed) && !m_pauseKeyPressed) ||
                 (m_gameSysExt.isPressed() && m_pauseBt.isOn())) &&
                 (m_levelStart && !m_levelEnd))
            {
                m_gameSysExt.playSound(m_sndSelectOption);

                ////////////////////////////////////////////////////////////
                #if defined(__ANDROID__)
                if (!m_keyBackPressed) m_gameSysExt.useVibrate(m_vibrateTimeDuration);
                #endif
                ////////////////////////////////////////////////////////////

                m_isPlaying = false;
                m_pauseKeyPressed = true;
                m_keyBackPressed = false;
            }

            updateObjView();
            updateObjBlocList();
            updateObjPlayer(DELTA_TIME);
            updateObjGameplayController(DELTA_TIME);
            updateObjBonusList(DELTA_TIME);
        }

        ////////////////////////////////////////////////////////////
        //////////////////////// PAUSE MENU ////////////////////////
        ////////////////////////////////////////////////////////////
        else
        {
            if (m_levelStart && !m_levelEnd)
            {
                if (m_appIsActive)
                {
                    bool mouseInCollison(false);

                    // check collision with pause button
                    for (int i(0); i < 3; i++)
                    {
                        if (is::mouseCollision(m_app, m_sprButton[i])) mouseInCollison = true;
                    }

                    // allow to activate key
                    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
                        && !m_gameSysExt.isPressed())
                        m_gameSysExt.m_keyIsPressed = false;

                    auto setOptionIndex = [this, &setButtonSelectScale](short int optionIndexValue)
                    {
                        ////////////////////////////////////////////////////////////
                        #if defined(__ANDROID__)
                        m_gameSysExt.useVibrate(m_vibrateTimeDuration);
                        #else
                        m_gameSysExt.playSound(m_sndSwitch);
                        #endif
                        ////////////////////////////////////////////////////////////
                        setButtonSelectScale();
                        m_optionIndex = optionIndexValue;
                    };

                    // switch with mouse
                    if (is::mouseCollision(m_app, m_sprButton[0]) && m_optionIndex != OP_RESUME_GAME)  setOptionIndex(OP_RESUME_GAME);
                    else if (is::mouseCollision(m_app, m_sprButton[1]) && m_optionIndex != OP_RESTART) setOptionIndex(OP_RESTART);
                    else if (is::mouseCollision(m_app, m_sprButton[2]) && m_optionIndex != OP_QUIT)    setOptionIndex(OP_QUIT);

                    // switch button with keyboard. This code will work until mouse isn't on button
                    if (!mouseInCollison)
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

                    // avoid press key loop
                    if (!mouseInCollison && m_gameSysExt.isPressed()) m_gameSysExt.m_keyIsPressed = true;

                    // quit pause when ESCAPE is pressed
                    if (m_keyBackPressed && !m_pauseKeyPressed)
                    {
                        m_keyBackPressed = false;
                    }

                    // validate option
                    if (((sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !m_pauseKeyPressed) ||
                        (m_gameSysExt.isPressed() && mouseInCollison)) &&
                        m_waitTime == 0 && !m_gameSysExt.m_keyIsPressed)
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
                            case OP_RESUME_GAME: // resume game
                                playSelectSnd();
                                m_pauseKeyPressed = true;
                                m_isPlaying = true;
                            break;

                            case OP_RESTART: // restart level
                                playSelectSnd();
                                showMessageBox("Restart Game?\nThe current game will be lost.", true);
                            break;

                            case OP_QUIT: // quit game
                                playSelectSnd();
                                showMessageBox("Quit Game?\nThe current game will be lost.", true);
                            break;
                        }
                    }
                }
                if (m_optionIndex < OP_RESUME_GAME) m_optionIndex = OP_QUIT;
                if (m_optionIndex > OP_QUIT) m_optionIndex = OP_RESUME_GAME;

                // change text color in relation pause menu option
                setTextAnimation(m_txtContinue, m_sprButton[0], OP_RESUME_GAME);
                setTextAnimation(m_txtRestart, m_sprButton[1], OP_RESTART);
                setTextAnimation(m_txtQuit, m_sprButton[2], OP_QUIT);

                // animation of button
                is::scaleAnimation(DELTA_TIME, m_sprButtonSelectScale, m_sprButtonSelect, is::getSFMLObjXScale(m_sprButton[0]));

                // position of pause component
                updateObjPause(DELTA_TIME);
            }
        }
    }

    ////////////////////////////////////////////////////////////
    /////////////////////// MESSAGE BOX ////////////////////////
    ////////////////////////////////////////////////////////////
    else
    {
        updateMsgBox(DELTA_TIME);

        if (!m_showMsg)
        {
            switch (m_optionIndex)
            {
            case OP_RESTART: // restart level
                if (m_msgAnswer == MsgAnswer::YES)
                {
                    m_launchOption = GAME_RESTART;
                    m_waitTime = 10;
                    m_levelEnd = true;
                }
                else m_waitTime = 10;
                m_pauseKeyPressed = true;
            break;

            case OP_QUIT: // quit game and return to main menu
                if (m_msgAnswer == MsgAnswer::YES)
                {
                    m_launchOption = is::GameDisplay::MAIN_MENU;
                    m_levelEnd = true;
                }
                else m_waitTime = 10;
                m_pauseKeyPressed = true;
            break;
            }
        }
    }
}
