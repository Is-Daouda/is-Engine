#include "PauseOption.h"

PauseOption::PauseOption(is::GameDisplay *scene, sf::Texture &texIcon, sf::Texture &texPad):
    MainObject(),
    m_keyIsLocked(false),
    m_useMoveAnimation(true),
    m_mouseInCollison(false),
    m_scene(scene),
    m_sprSFXScale(1.f),
    m_sprVibrateScale(1.f)
{
    for (unsigned int i(0); i < is::arraySize(m_sprMask); i++)
    {
        is::setSFMLObjSize(m_sprMask[i], sf::Vector2f(42.f, 42.f));
        is::centerSFMLObj(m_sprMask[i]);
    }
    is::createSprite(texIcon, m_sprIcoSFX, sf::IntRect(0, 0, 48, 32), sf::Vector2f(m_x, m_y), sf::Vector2f(16.f, 16.f));
    is::createSprite(texIcon, m_sprParent, sf::IntRect(96, 0, 48, 32), sf::Vector2f(m_x, m_y), sf::Vector2f(16.f, 16.f));
    is::createSprite(texIcon, m_sprIcoVibrate, sf::IntRect(192, 0, 48, 32), sf::Vector2f(m_x, m_y), sf::Vector2f(16.f, 16.f));

    // pause menu rectangle
    is::createRectangle(m_recPauseBG, sf::Vector2f(m_scene->getViewW() + 10, m_scene->getViewH() + 10.f), sf::Color(0, 0, 0, 100));

    is::createSprite(texPad, m_sprPad1, sf::IntRect(0, 0, 160, 32), sf::Vector2f(0.f, 0.f), sf::Vector2f(80.f, 16.f));
    is::createSprite(texPad, m_sprPad2, sf::IntRect(0, 0, 160, 32), sf::Vector2f(0.f, 0.f), sf::Vector2f(80.f, 16.f));
    is::createSprite(texPad, m_sprPad3, sf::IntRect(0, 0, 160, 32), sf::Vector2f(0.f, 0.f) , sf::Vector2f(80.f, 16.f));

    is::createText(m_scene->getFontSystem(), m_txtContinue, is::lang::pad_continue_game[m_scene->getGameSystem().m_gameLanguage], 0.f, 0.f, true);
    is::createText(m_scene->getFontSystem(), m_txtQuit, is::lang::pad_quit_game[m_scene->getGameSystem().m_gameLanguage], 0.f, 0.f, true);
    is::createText(m_scene->getFontSystem(), m_txtRestart, is::lang::pad_restart_game[m_scene->getGameSystem().m_gameLanguage], 0.f, 0.f, true);

    // set pause screen object position
    is::setSFMLObjX_Y(m_sprPad1, m_scene->getViewX(), m_scene->getViewY() - 32.f);
    is::setSFMLObjX_Y(m_sprPad2, m_scene->getViewX(), m_scene->getViewY() + 32.f);
    is::setSFMLObjX_Y(m_sprPad3, m_scene->getViewX() - (70.f - m_pauseObjMove), m_scene->getViewY());
    is::setSFMLObjX_Y(m_scene->getSprButtonSelect(), is::getSFMLObjX(m_sprPad1), is::getSFMLObjY(m_sprPad1));
    is::setSFMLObjX_Y(m_txtContinue, is::getSFMLObjX(m_sprPad1), is::getSFMLObjY(m_sprPad1));
    is::setSFMLObjX_Y(m_txtQuit, is::getSFMLObjX(m_sprPad3), is::getSFMLObjY(m_sprPad3));
    is::setSFMLObjX_Y(m_recPauseBG, m_scene->getViewX(), m_scene->getViewY());
}

void PauseOption::step(float const &DELTA_TIME)
{
    setPosition(m_scene->getViewX() - 10.f, (m_scene->getViewY() - 175.f) - m_pauseObjMove);

    // avoid looping click for mini options
    if (!m_scene->getGameSystem().m_keyIsPressed) m_keyIsLocked = false;

    //////////////////////////////////////////////////////
    // pause menu icon manager
    //////////////////////////////////////////////////////
    if (m_scene->getGameSystem().isPressed() && !m_keyIsLocked)
    {
        bool collision(false);
        auto setVariable = [this](PauseOptionType value)
        {
            if (m_answer != value) m_answer = value;
        };
        if (m_scene->mouseCollision(m_sprMask[0]))
        {
            setVariable(PAUSE_OPTION_SFX);
            collision = true;
        }
        else if (m_scene->mouseCollision(m_sprMask[1]))
        {
            setVariable(PAUSE_OPTION_MSC);
            collision = true;
        }
        else if (m_scene->mouseCollision(m_sprMask[2]))
        {
            setVariable(PAUSE_OPTION_VIBRATE);
            collision = true;
        }

        if (collision)
        {
            auto setObjVar = [this](bool &varIndex, float &scaleVar)
            {
                if (varIndex) varIndex = false; else varIndex = true;
                scaleVar = 1.5f;
                m_scene->GSMplaySound("select_option"); // We play this sound
            };
            if (m_answer != PAUSE_OPTION_VIBRATE) m_scene->getGameSystem().useVibrate(60);
            switch (m_answer)
            {
                case PAUSE_OPTION_SFX:
                    setObjVar(m_scene->getGameSystem().m_enableSound, m_sprSFXScale);
                break;
                case PAUSE_OPTION_MSC:
                    setObjVar(m_scene->getGameSystem().m_enableMusic, m_imageScale);
                break;
                case PAUSE_OPTION_VIBRATE:
                    setObjVar(m_scene->getGameSystem().m_enableVibrate, m_sprVibrateScale);
                    m_scene->getGameSystem().useVibrate(120);
                break;
            }
            m_scene->getGameSystem().saveConfig(is::GameConfig::CONFIG_FILE);
            m_keyIsLocked = true;
        }
    }

    if (m_scene->getGameSystem().m_enableSound) is::setSFMLObjTexRec(m_sprIcoSFX, 0, 0, 48, 32);
    else is::setSFMLObjTexRec(m_sprIcoSFX, 48, 0, 48, 32);
    if (m_scene->getGameSystem().m_enableMusic) is::setSFMLObjTexRec(m_sprParent, 96, 0, 48, 32);
    else is::setSFMLObjTexRec(m_sprParent, 144, 0, 48, 32);
    if (m_scene->getGameSystem().m_enableVibrate) is::setSFMLObjTexRec(m_sprIcoVibrate, 192, 0, 48, 32);
    else is::setSFMLObjTexRec(m_sprIcoVibrate, 240, 0, 48, 32);

    float _space(64.f);
    is::setSFMLObjX_Y(m_sprIcoSFX, m_x - _space, m_y);
    is::setSFMLObjX_Y(m_sprParent, m_x, m_y);
    is::setSFMLObjX_Y(m_sprIcoVibrate, m_x + _space, m_y);

    is::setSFMLObjX_Y(m_sprMask[0], is::getSFMLObjX(m_sprIcoSFX), is::getSFMLObjY(m_sprIcoSFX));
    is::setSFMLObjX_Y(m_sprMask[1], is::getSFMLObjX(m_sprParent), is::getSFMLObjY(m_sprParent));
    is::setSFMLObjX_Y(m_sprMask[2], is::getSFMLObjX(m_sprIcoVibrate), is::getSFMLObjY(m_sprIcoVibrate));

    is::scaleAnimation(DELTA_TIME, m_sprSFXScale, m_sprIcoSFX);
    is::scaleAnimation(DELTA_TIME, m_imageScale, m_sprParent);
    is::scaleAnimation(DELTA_TIME, m_sprVibrateScale, m_sprIcoVibrate);

    //////////////////////////////////////////////////////
    // pause menu pad (button) manager
    //////////////////////////////////////////////////////

    // allow to check collision
    m_mouseInCollison = false;

    // check collision with buttons
    if (m_scene->mouseCollision(m_sprPad1) || m_scene->mouseCollision(m_sprPad2) || m_scene->mouseCollision(m_sprPad3))
        m_mouseInCollison = true;

   // avoid the long pressing button effect
    if (!m_mouseInCollison && m_scene->getGameSystem().isPressed(is::GameSystem::ValidationButton::MOUSE))
        m_scene->getGameSystem().m_keyIsPressed = true;

    // change option when mouse (touch on Android) is in collision with sprite
    if (m_scene->mouseCollision(m_sprPad1) && m_scene->getOptionIndex() != is::DisplayOption::RESUME_GAME)
        m_scene->setOptionIndex(is::DisplayOption::RESUME_GAME, true);
    else if (m_scene->mouseCollision(m_sprPad2) && m_scene->getOptionIndex() != is::DisplayOption::GAME_OPTION_RESTART)
        m_scene->setOptionIndex(is::DisplayOption::GAME_OPTION_RESTART, true);
    else if (m_scene->mouseCollision(m_sprPad3) && m_scene->getOptionIndex() != is::DisplayOption::QUIT_GAME)
        m_scene->setOptionIndex(is::DisplayOption::QUIT_GAME, true);

    // change option with keyboard (only for PC)
    if (!m_scene->getGameSystem().m_keyIsPressed && !m_mouseInCollison)
    {
        if (m_scene->getGameSystem().keyIsPressed(is::GameConfig::KEY_LEFT)) m_scene->setOptionIndex(-1, false);
        else if (m_scene->getGameSystem().keyIsPressed(is::GameConfig::KEY_RIGHT)) m_scene->setOptionIndex(1, false);
        if (m_scene->getOptionIndex() < is::DisplayOption::RESUME_GAME) m_scene->setOptionIndex(is::DisplayOption::QUIT_GAME);
        if (m_scene->getOptionIndex() > is::DisplayOption::QUIT_GAME) m_scene->setOptionIndex(is::DisplayOption::RESUME_GAME);
    }

    if (m_useMoveAnimation)
    {
        if (m_pauseObjMove > 35.f) m_pauseObjMove -= ((30.f * is::VALUE_CONVERSION) * DELTA_TIME);
        else m_pauseObjMove = 0.f;
    }
    else m_pauseObjMove = 480.f;

    is::setSFMLObjX_Y(m_sprPad1, m_scene->getViewX() + m_pauseObjMove, m_scene->getViewY() - 64.f);
    is::setSFMLObjX_Y(m_sprPad2, m_scene->getViewX() + (160.f + m_pauseObjMove), m_scene->getViewY());
    is::setSFMLObjX_Y(m_sprPad3, m_scene->getViewX() - (160.f - m_pauseObjMove), m_scene->getViewY());
    if (!m_useMoveAnimation) is::setSFMLObjX_Y(m_scene->getSprButtonSelect(), m_scene->getViewX() + m_pauseObjMove, m_scene->getViewY());

    float const TXT_Y_POS(6.f);
    is::setSFMLObjX_Y(m_txtContinue, is::getSFMLObjX(m_sprPad1), is::getSFMLObjY(m_sprPad1) - TXT_Y_POS);
    is::setSFMLObjX_Y(m_txtRestart, is::getSFMLObjX(m_sprPad2), is::getSFMLObjY(m_sprPad2) - TXT_Y_POS);
    is::setSFMLObjX_Y(m_txtQuit, is::getSFMLObjX(m_sprPad3), is::getSFMLObjY(m_sprPad3) - TXT_Y_POS);

    is::setSFMLObjX_Y(m_recPauseBG, m_scene->getViewX(), m_scene->getViewY());

    // sprites animation
    m_scene->setTextAnimation(m_txtContinue, m_sprPad1, is::DisplayOption::RESUME_GAME);
    m_scene->setTextAnimation(m_txtRestart, m_sprPad2, is::DisplayOption::GAME_OPTION_RESTART);
    m_scene->setTextAnimation(m_txtQuit, m_sprPad3, is::DisplayOption::QUIT_GAME);

    // PAD animation
    is::scaleAnimation(m_scene->getDELTA_TIME(), m_scene->getSprButtonSelectScale(), m_scene->getSprButtonSelect());
}

void PauseOption::draw(sf::RenderTexture &surface)
{
    if (!m_scene->getIsPlaying() && m_scene->getSceneStart())
    {
        surface.draw(m_recPauseBG);
        if (m_scene->getOptionIndex() != 0) surface.draw(m_sprPad1);
        if (m_scene->getOptionIndex() != 1) surface.draw(m_sprPad2);
        if (m_scene->getOptionIndex() != 2) surface.draw(m_sprPad3);
        surface.draw(m_scene->getSprButtonSelect());
        surface.draw(m_txtContinue);
        surface.draw(m_txtRestart);
        surface.draw(m_txtQuit);

        if (m_pauseObjMove < 450.f)
        {
            surface.draw(m_sprIcoSFX);
            surface.draw(m_sprIcoVibrate);
            surface.draw(m_sprParent);
        }
    }
}
