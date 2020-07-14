#include "GameLevel.h"

void GameLevel::step()
{
    DELTA_TIME = getDeltaTime();

    updateTimeWait(DELTA_TIME);

    // Manage game controls (keyboard & Virtual Game Pad)
    auto gameKey = static_cast<is::GameKeyData*>(SDMgetObject("GameKeyData"));
    gameKey->step(DELTA_TIME);

    // allows activated use of buttons
    if (!m_keyBackPressed) gameKey->m_keyPausePressed = false;

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
    if (auto player = static_cast<Player*>(SDMgetObject("Player")); player->getIsKO())
    {
        m_gameSysExt.m_launchOption = is::DisplayOption::RESTART_LEVEL; // restart level
        m_sceneEnd = true;
    }

    // when player finish the level
    if (!m_sceneEnd)
    {
        if (auto finishObject = static_cast<FinishObject*>(SDMgetObject("FinishObject")); finishObject->getStep() == 1)
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
            m_sceneEnd = true;
            finishObject->addStep();
        }
    }

    if (m_sceneEnd) m_isRunning = false;

    if (!m_showMsg)
    {
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      IN GAME
//////////////////////////////////////////////////////////////////////////////////////////////////////
        if (m_isPlaying)
        {
            // check if mouse is in collision with sprite
            if (auto cancelBt = static_cast<CancelButton*>(SDMgetObject("CancelButton")); mouseCollision(cancelBt->getSprite()))
            {
                cancelBt->setAlpha(255);
                m_gameSysExt.m_keyIsPressed = true;
            }
            pauseGame();

            auto gameDialog = static_cast<GameDialog*>(SDMgetObject("GameDialog"));
            if (!gameDialog->showDialog())
            {
                gamePlay();
            }
            else
            {
                if (!mouseCollision(gameDialog->getSprite()) && m_gameSysExt.isPressed()) m_gameSysExt.m_keyIsPressed = true;
                gameDialog->setPosition(m_viewX, m_viewY + 32.f);
            }
            gameDialog->step(DELTA_TIME);
        }
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      MENU PAUSE
//////////////////////////////////////////////////////////////////////////////////////////////////////
        else
        {
            if (m_sceneStart && !m_sceneEnd)
            {
                if (m_windowIsActive)
                {
                    // mini option pause
                    auto pauseOption = static_cast<PauseOption*>(SDMgetObject("PauseOption"));
                    pauseOption->step(DELTA_TIME);

                    // function to resume play and replay paused sounds
                    auto continueGame = [this, gameKey]()
                    {
                        stopSounds(false);
                        GSMplaySound("cancel"); // We play this sound
                        static_cast<CancelButton*>(SDMgetObject("CancelButton"))->setAlpha(0);
                        m_isPlaying = true;
                        m_gameSysExt.m_keyIsPressed = true;
                        gameKey->m_keyPausePressed = true;
                    };

                    // if back key is pressed continue the game
                    if (m_keyBackPressed && !gameKey->m_keyPausePressed)
                    {
                        continueGame();
                        m_keyBackPressed = false;
                    }

                    // validate option
                    if (((m_gameSysExt.isPressed(is::GameSystem::ValidationButton::KEYBOARD) && !gameKey->m_keyPausePressed) ||
                        (m_gameSysExt.isPressed(is::GameSystem::ValidationButton::MOUSE) && pauseOption->m_mouseInCollison)) &&
                        m_waitTime == 0 && !m_gameSysExt.m_keyIsPressed && !m_sceneEnd)
                    {
                        switch (m_optionIndex)
                        {
                            case is::DisplayOption::RESUME_GAME:
                                continueGame();
                            break;

                            case is::DisplayOption::GAME_OPTION_RESTART:
                                showMessageBox(is::lang::msg_pause_restart[m_gameSysExt.m_gameLanguage], true);
                            break;

                            case is::DisplayOption::QUIT_GAME:
                                showMessageBox(is::lang::msg_pause_quit[m_gameSysExt.m_gameLanguage], true);
                            break;
                        }
                    }
                }
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
            case is::DisplayOption::GAME_OPTION_RESTART:
                if (m_msgAnswer == MsgAnswer::YES)
                {
                    m_gameSysExt.m_launchOption = is::DisplayOption::GAME_OPTION_RESTART;
                    m_waitTime = 10;
                    m_sceneEnd = true;
                }
                else m_waitTime = 10;
                gameKey->m_keyPausePressed = true;
            break;

            case is::DisplayOption::QUIT_GAME:
                if (m_msgAnswer == MsgAnswer::YES)
                {
                    m_gameSysExt.m_launchOption = is::DisplayOption::MAIN_MENU;
                    m_sceneEnd = true;
                }
                else m_waitTime = 10;
                gameKey->m_keyPausePressed = true;
            break;
            }
        }
    }
}
