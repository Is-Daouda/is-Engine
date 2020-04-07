#include "PauseOption.h"

PauseOption::PauseOption(is::GameDisplay *scene, sf::Texture &tex):
    MainObject(),
    m_keyIsLocked(false),
    m_scene(scene),
    m_sprSFXScale(1.f),
    m_sprVibrateScale(1.f)
{
    for (unsigned int i(0); i < is::arraySize(m_sprMask); i++)
    {
        is::setSFMLObjSize(m_sprMask[i], sf::Vector2f(42.f, 42.f));
        is::centerSFMLObj(m_sprMask[i]);
    }
    is::createSprite(tex, m_sprIcoSFX, sf::IntRect(0, 0, 48, 32), sf::Vector2f(m_x, m_y), sf::Vector2f(16.f, 16.f));
    is::createSprite(tex, m_sprParent, sf::IntRect(96, 0, 48, 32), sf::Vector2f(m_x, m_y), sf::Vector2f(16.f, 16.f));
    is::createSprite(tex, m_sprIcoVibrate, sf::IntRect(192, 0, 48, 32), sf::Vector2f(m_x, m_y), sf::Vector2f(16.f, 16.f));
}

void PauseOption::step(float const &DELTA_TIME)
{
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
                m_scene->getGameSystem().playSound(m_scene->getSndSelectOption());
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
}

void PauseOption::draw(sf::RenderTexture &surface)
{
    surface.draw(m_sprIcoSFX);
    surface.draw(m_sprIcoVibrate);
    surface.draw(m_sprParent);
}
