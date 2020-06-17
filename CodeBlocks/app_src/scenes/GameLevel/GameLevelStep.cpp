#include "GameLevel.h"

void GameLevel::step()
{
    DELTA_TIME = getDeltaTime();

    updateTimeWait(DELTA_TIME);

    int const OP_RESUME_GAME(0),
              OP_RESTART(1),
              OP_QUIT(2);

    // allows activated use of buttons
    if (!m_keyBackPressed) m_gameKey.m_keyPausePressed = false;

    // allows activated use of buttons
    if (!m_gameSysExt.keyIsPressed(is::GameConfig::KEY_LEFT) &&
        !m_gameSysExt.keyIsPressed(is::GameConfig::KEY_RIGHT) &&
        !m_gameSysExt.keyIsPressed(is::GameConfig::KEY_A)
        && !m_gameSysExt.isPressed())
        m_gameSysExt.m_keyIsPressed = false;

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

    // if the window is not activated suspend the game
    if (!m_windowIsActive && m_isPlaying)
    {
        stopSounds(true);
        m_isPlaying = false;
    }

    // if the player is KO we stop the level
    if (m_player.getIsKO())
    {
        m_gameSysExt.m_launchOption = is::DisplayOption::RESTART_LEVEL; // restart level
        m_levelEnd = true;
    }

    // when player finish the level
    if (!m_levelEnd)
    {
        if (m_finishObject.getStep() == 1)
        {
            //////////////////////////////////////////////////////////////////////
            m_gameSysExt.m_currentLevel++; // allow to access the next level

            // increase game progress
            if (m_gameSysExt.m_currentLevel > m_gameSysExt.m_gameProgression && m_gameSysExt.m_gameProgression < m_gameSysExt.m_levelNumber)
            {
                m_gameSysExt.m_gameProgression++;
            }

            m_gameSysExt.saveData(is::GameConfig::GAME_DATA_FILE); // save data
            //////////////////////////////////////////////////////////////////////

            m_gameSysExt.m_launchOption = is::DisplayOption::NEXT_LEVEL; // go to the next level
            m_levelEnd = true;
            m_finishObject.addStep();
        }
    }

    if (m_levelEnd) m_isRunning = false;

    if (!m_showMsg)
    {
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      IN GAME
//////////////////////////////////////////////////////////////////////////////////////////////////////
        if (m_isPlaying)
        {
            // check if mouse is in collision with sprite
            if (mouseCollision(m_cancelBt.getSprite()))
            {
                m_cancelBt.setAlpha(255);
                m_gameSysExt.m_keyIsPressed = true;
            }
            pauseGame();

            if (!m_gameDialog.showDialog())
            {
                gamePlay();
            }
            else
            {
                if (!mouseCollision(m_gameDialog.getSprite()) && m_gameSysExt.isPressed()) m_gameSysExt.m_keyIsPressed = true;
                m_gameDialog.setPosition(m_viewX, m_viewY + 32.f);
            }
            m_gameDialog.step(DELTA_TIME);
        }
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      MENU PAUSE
//////////////////////////////////////////////////////////////////////////////////////////////////////
        else
        {
            if (m_levelStart && !m_levelEnd)
            {
                if (m_windowIsActive)
                {
                    // avoid looping click for mini options
                    if (!m_gameSysExt.m_keyIsPressed) m_pauseOption->m_keyIsLocked = false;

                    // allow to check collision
                    bool mouseInCollison(false);

                    // check collision with buttons
                    if (mouseCollision(m_sprPad1) ||
                        mouseCollision(m_sprPad2) ||
                        mouseCollision(m_sprPad3))
                        mouseInCollison = true;

                    // change option when mouse (touch on Android) is in collision with sprite
                    if (mouseCollision(m_sprPad1) && m_optionIndex != OP_RESUME_GAME) setOptionIndex(OP_RESUME_GAME, true);
                    else if (mouseCollision(m_sprPad2) && m_optionIndex != OP_RESTART) setOptionIndex(OP_RESTART, true);
                    else if (mouseCollision(m_sprPad3) && m_optionIndex != OP_QUIT) setOptionIndex(OP_QUIT, true);

                    // change option with keyboard (only for PC)
                    if (!m_gameSysExt.m_keyIsPressed && !mouseInCollison)
                    {
                        if (m_gameSysExt.keyIsPressed(is::GameConfig::KEY_LEFT)) setOptionIndex(-1, false);
                        else if (m_gameSysExt.keyIsPressed(is::GameConfig::KEY_RIGHT)) setOptionIndex(1, false);
                        if (m_optionIndex < 0) m_optionIndex = OP_QUIT;
                        if (m_optionIndex > OP_QUIT) m_optionIndex = 0;
                    }

                    // avoid the long pressing button effect
                    if (!mouseInCollison && m_gameSysExt.isPressed(is::GameSystem::ValidationButton::MOUSE)) m_gameSysExt.m_keyIsPressed = true;

                    // function to resume play and replay paused sounds
                    auto continueGame = [this]()
                    {
                        stopSounds(false);
                        m_gameSysExt.playSound(m_sndCancel);
                        m_cancelBt.setAlpha(0);
                        m_isPlaying = true;
                        m_gameSysExt.m_keyIsPressed = true;
                        m_gameKey.m_keyPausePressed = true;
                    };

                    // if back key is pressed continue the game
                    if (m_keyBackPressed && !m_gameKey.m_keyPausePressed)
                    {
                        continueGame();
                        m_keyBackPressed = false;
                    }

                    // validate option
                    if (((m_gameSysExt.isPressed(is::GameSystem::ValidationButton::KEYBOARD) && !m_gameKey.m_keyPausePressed) ||
                        (m_gameSysExt.isPressed(is::GameSystem::ValidationButton::MOUSE) && mouseInCollison)) &&
                        m_waitTime == 0 && !m_gameSysExt.m_keyIsPressed && !m_levelEnd)
                    {
                        switch (m_optionIndex)
                        {
                            case OP_RESUME_GAME:
                                continueGame();
                            break;

                            case OP_RESTART:
                                showMessageBox(is::lang::msg_pause_restart[m_gameSysExt.m_gameLanguage], true);
                            break;

                            case OP_QUIT:
                                showMessageBox(is::lang::msg_pause_quit[m_gameSysExt.m_gameLanguage], true);
                            break;
                        }
                    }
                }
                if (m_optionIndex < OP_RESUME_GAME) m_optionIndex = OP_QUIT;
                if (m_optionIndex > OP_QUIT) m_optionIndex = OP_RESUME_GAME;

                // sprites animation
                setTextAnimation(m_txtContinue, m_sprPad1, OP_RESUME_GAME);
                setTextAnimation(m_txtRestart, m_sprPad2, OP_RESTART);
                setTextAnimation(m_txtQuit, m_sprPad3, OP_QUIT);

                updatePauseObj(true);

                // mini option pause
                m_pauseOption->step(DELTA_TIME);

                // PAD animation
                is::scaleAnimation(DELTA_TIME, m_sprButtonSelectScale, m_sprButtonSelect);
            }
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
            switch (m_optionIndex)
            {
            case OP_RESTART:
                if (m_msgAnswer == MsgAnswer::YES)
                {
                    m_gameSysExt.m_launchOption = is::DisplayOption::GAME_OPTION_RESTART;
                    m_waitTime = 10;
                    m_levelEnd = true;
                }
                else m_waitTime = 10;
                m_gameKey.m_keyPausePressed = true;
            break;

            case OP_QUIT:
                if (m_msgAnswer == MsgAnswer::YES)
                {
                    m_gameSysExt.m_launchOption = is::DisplayOption::MAIN_MENU;
                    m_levelEnd = true;
                }
                else m_waitTime = 10;
                m_gameKey.m_keyPausePressed = true;
            break;
            }
        }
    }
}
