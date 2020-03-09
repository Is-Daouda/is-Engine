#include "GameDisplay.h"

namespace is
{
GameDisplay::GameDisplay(sf::RenderWindow &window, DisplayOption &m_launchOption, GameSystemExtended &gameSysExt, sf::Color bgColor):
    m_app(window),
    m_launchOption(m_launchOption),
    m_gameSysExt(gameSysExt),
    #if defined(__ANDROID__)
    m_vibrateTimeDuration(40),
    #endif // defined
    m_optionIndex(0),
    m_alphaRec(255),
    m_waitTime(0),
    m_msgWaitTime(0),
    VIEW_W(640.f),
    VIEW_H(480.f),
    m_viewX(VIEW_W / 2),
    m_viewY(VIEW_H / 2),
    m_sprButtonSelectScale(1.f),
    m_isRunning(true),
    m_appIsActive(true),
    m_keyBackPressed(false),
    m_showMsg(false),
    m_mbYesNo(false),
    m_msgBoxMouseInCollison(false)
{
    m_view.setSize(sf::Vector2f(VIEW_W, VIEW_H));
    m_view.setCenter(m_viewX, m_viewY);
    m_app.setView(m_view);
    m_windowBgColor = bgColor;

    // transition rectangle
    is::createRectangle(m_recTransition, sf::Vector2f(VIEW_W + 10.f, VIEW_H + 10.f), sf::Color(0, 0, 0, m_alphaRec));
}

GameDisplay::~GameDisplay() {}

void is::GameDisplay::setTextAnimation(sf::Text &txt, sf::Sprite &spr, int val)
{
    if (m_optionIndex == val)
    {
        is::setSFMLObjX_Y(m_sprButtonSelect, is::getSFMLObjX(spr), is::getSFMLObjY(spr));
        is::setSFMLTextColor(txt, sf::Color::White);
    }
    else is::setSFMLTextColor(txt, sf::Color(0, 255, 0));
}

void is::GameDisplay::setTextAnimation(sf::Text &txt, int &var, int val)
{
    if (var == val)
    {
        is::setSFMLTextColor(txt, sf::Color::White);
    }
    else is::setSFMLTextColor(txt, sf::Color(0, 255, 0));
}

void is::GameDisplay::controlEventFocusClosing()
{
    // manage the state of window
    if (m_event.type == sf::Event::GainedFocus) m_appIsActive = true;
    if (m_event.type == sf::Event::LostFocus) m_appIsActive = false;

    // closing the application
    if (m_event.type == sf::Event::Closed)
    {
        m_isRunning = false;  // quit the main render loop
        m_app.close();
    }
}

void is::GameDisplay::showMessageBox(std::string const &msgBody, bool mbYesNo)
{
    m_showMsg = true;
    m_mbYesNo = mbYesNo;
    if (m_mbYesNo) m_msgAnswer = MsgAnswer::NO;
    m_msgWaitTime = 0;
    m_msgBoxMouseInCollison = false;

    const float dim(6.f);

    is::setSFMLObjX_Y(m_recMsgBox, sf::Vector2f(m_app.getView().getCenter().x, m_app.getView().getCenter().y));
    is::setSFMLObjX_Y(m_sprMsgBox, sf::Vector2f(m_app.getView().getCenter().x, m_app.getView().getCenter().y));
    is::setSFMLObjX_Y(m_sprMsgBoxButton1, is::getSFMLObjX(m_sprMsgBox) - is::getSFMLObjOriginX(m_sprMsgBox) + is::getSFMLObjOriginX(m_sprMsgBoxButton1) + dim,
                     is::getSFMLObjY(m_sprMsgBox) + is::getSFMLObjOriginY(m_sprMsgBox) - is::getSFMLObjHeight(m_sprMsgBoxButton1) + dim);
    is::setSFMLObjX_Y(m_sprMsgBoxButton2, is::getSFMLObjX(m_sprMsgBox) + is::getSFMLObjOriginX(m_sprMsgBox) - is::getSFMLObjOriginX(m_sprMsgBoxButton2) - dim,
                     is::getSFMLObjY(m_sprMsgBox) + is::getSFMLObjOriginY(m_sprMsgBox) - is::getSFMLObjHeight(m_sprMsgBoxButton2) + dim);
    is::setSFMLObjX_Y(m_sprMsgBoxButton3, is::getSFMLObjX(m_sprMsgBox),
                     is::getSFMLObjY(m_sprMsgBox) + is::getSFMLObjOriginY(m_sprMsgBox) - is::getSFMLObjHeight(m_sprMsgBoxButton1) + dim);
    is::setSFMLObjX_Y(m_txtMsgBox, is::getSFMLObjX(m_sprMsgBox)- is::getSFMLObjOriginX(m_sprMsgBox) + 16.f,
                      is::getSFMLObjY(m_sprMsgBox) - is::getSFMLObjOriginY(m_sprMsgBox) + 8.f);
    m_txtMsgBox.setString(msgBody);

    // adjust the text on button
    is::setSFMLObjX_Y(m_txtMsgBoxYes, is::getSFMLObjX(m_sprMsgBoxButton1) - 1.f,
                      is::getSFMLObjY(m_sprMsgBoxButton1)- is::getSFMLObjOriginY(m_sprMsgBoxButton1) + dim - 1.f);
    is::setSFMLObjX_Y(m_txtMsgBoxNo, is::getSFMLObjX(m_sprMsgBoxButton2),
                      is::getSFMLObjY(m_sprMsgBoxButton2) - is::getSFMLObjOriginY(m_sprMsgBoxButton2) + dim - 1.f);
    is::setSFMLObjX_Y(m_txtMsgBoxOK, is::getSFMLObjX(m_sprMsgBoxButton3),
                      is::getSFMLObjY(m_sprMsgBoxButton3) - is::getSFMLObjOriginY(m_sprMsgBoxButton3) + dim - 1.f);

    is::setSFMLObjAlpha(m_sprMsgBoxButton1, m_msgWaitTime, 255, 255, 255);
    is::setSFMLObjAlpha(m_sprMsgBoxButton2, m_msgWaitTime, 255, 255, 255);
    is::setSFMLObjAlpha(m_sprMsgBoxButton3, m_msgWaitTime, 255, 255, 255);
    is::setSFMLObjAlpha(m_txtMsgBoxNo, m_msgWaitTime, 255, 255, 255);
    is::setSFMLObjAlpha(m_txtMsgBoxYes, m_msgWaitTime, 0, 255, 0);
    is::setSFMLObjAlpha(m_txtMsgBoxOK, m_msgWaitTime, 0, 255, 0);
    is::setSFMLObjAlpha(m_sprMsgBox, m_msgWaitTime, 255, 255, 255);
    is::setSFMLObjAlpha(m_txtMsgBox, m_msgWaitTime, 0, 0, 0);

    m_app.setView(m_view);
}

void is::GameDisplay::updateMsgBox(float const &_DELTA_TIME, sf::Color textDefaultColor, sf::Color textSelectedColor)
{
    if (m_msgWaitTime < 240) m_msgWaitTime += static_cast<int>((8.f * is::VALUE_CONVERSION) * _DELTA_TIME);
    else m_msgWaitTime = 255;
    if (!m_gameSysExt.isPressed()) m_gameSysExt.m_keyIsPressed = false;

    // check collision with all objects of message box
    if (!is::mouseCollision(m_app, m_sprMsgBoxButton1) &&
        !is::mouseCollision(m_app, m_sprMsgBoxButton2) &&
        !is::mouseCollision(m_app, m_sprMsgBoxButton3))
         m_msgBoxMouseInCollison = false;
     else m_msgBoxMouseInCollison = true;

    // avoid the long pressing button effect
    if (!m_msgBoxMouseInCollison && m_gameSysExt.isPressed()) m_gameSysExt.m_keyIsPressed = true;

    if (m_msgWaitTime == 255 && m_appIsActive)
    {
        // if is YES / NO message box
        if (m_mbYesNo)
        {
            if (((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
                  !is::mouseCollision(m_app, m_sprMsgBoxButton2)) ||
                is::mouseCollision(m_app, m_sprMsgBoxButton1)) && m_msgAnswer == MsgAnswer::NO)
            {
                ////////////////////////////////////////////////////////////
                // code for PC / Android
                #if defined(__ANDROID__)
                m_gameSysExt.useVibrate(m_vibrateTimeDuration);
                #else
                m_gameSysExt.playSound(m_sndSwitch);
                #endif
                ////////////////////////////////////////////////////////////
                m_msgAnswer = MsgAnswer::YES; // answer = yes
            }
            else if (((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
                     !is::mouseCollision(m_app, m_sprMsgBoxButton1)) ||
                     is::mouseCollision(m_app, m_sprMsgBoxButton2)) && m_msgAnswer == MsgAnswer::YES)
            {
                ////////////////////////////////////////////////////////////
                // code for PC / Android version
                #if defined(__ANDROID__)
                m_gameSysExt.useVibrate(m_vibrateTimeDuration);
                #else
                m_gameSysExt.playSound(m_sndSwitch);
                #endif
                ////////////////////////////////////////////////////////////
                m_msgAnswer = MsgAnswer::NO;  // answer = no
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) ||
                    ((is::mouseCollision(m_app, m_sprMsgBoxButton1) ||
                      is::mouseCollision(m_app, m_sprMsgBoxButton2)) &&
                      m_gameSysExt.isPressed() && !m_gameSysExt.m_keyIsPressed))
            {
                m_showMsg = false;
            }
            else if (m_keyBackPressed)
            {
                m_msgAnswer = MsgAnswer::NO; // answer = no (canceled)
                m_showMsg = false;
                m_keyBackPressed = false;
            }

            // texts animations
            if (m_msgAnswer == MsgAnswer::YES)
            {
                m_txtMsgBoxYes.setFillColor(textSelectedColor);
                m_txtMsgBoxNo.setFillColor(textDefaultColor);
            }
            else
            {
                m_txtMsgBoxNo.setFillColor(textSelectedColor);
                m_txtMsgBoxYes.setFillColor(textDefaultColor);
            }
        }
        else // if is OK message box
        {
            if (is::mouseCollision(m_app, m_sprMsgBoxButton3) && m_msgAnswer == MsgAnswer::NO)
            {
                ////////////////////////////////////////////////////////////
                // code for PC / Android version
                #if defined(__ANDROID__)
                m_gameSysExt.useVibrate(m_vibrateTimeDuration);
                #else
                m_gameSysExt.playSound(m_sndSwitch);
                #endif
                ////////////////////////////////////////////////////////////

                m_msgAnswer = MsgAnswer::YES; // answer = OK
                m_txtMsgBoxOK.setFillColor(textSelectedColor);
            }
            else if (((sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || m_keyBackPressed) &&
                     !is::mouseCollision(m_app, m_sprMsgBoxButton3)) || (is::mouseCollision(m_app, m_sprMsgBoxButton3) &&
                     m_gameSysExt.isPressed() && !m_gameSysExt.m_keyIsPressed)
                     )
            {
                m_showMsg = false;
                m_keyBackPressed = false;
            }
            else if (!is::mouseCollision(m_app, m_sprMsgBoxButton3) && m_msgAnswer == MsgAnswer::YES)
            {
                m_msgAnswer = MsgAnswer::NO; // answer = NO
                m_txtMsgBoxOK.setFillColor(textDefaultColor);
            }
        }
    }

    if (m_msgWaitTime != 255)
    {
        if (m_mbYesNo)
        {
            is::setSFMLObjColor(m_sprMsgBoxButton1, sf::Color(255, 255, 255, m_msgWaitTime));
            is::setSFMLObjColor(m_sprMsgBoxButton2, sf::Color(255, 255, 255, m_msgWaitTime));
            is::setSFMLTextColor(m_txtMsgBoxNo, sf::Color(textSelectedColor.r, textSelectedColor.g, textSelectedColor.b, m_msgWaitTime));
            is::setSFMLTextColor(m_txtMsgBoxYes, sf::Color(textDefaultColor.r, textDefaultColor.g, textDefaultColor.b, m_msgWaitTime));
        }
        else
        {
            is::setSFMLObjColor(m_sprMsgBoxButton3, sf::Color(255, 255, 255, m_msgWaitTime));
            is::setSFMLTextColor(m_txtMsgBoxOK, sf::Color(textDefaultColor.r, textDefaultColor.g, textDefaultColor.b, m_msgWaitTime));
        }
    }
    is::setSFMLObjColor(m_sprMsgBox, sf::Color(255, 255, 255, m_msgWaitTime));
    is::setSFMLTextColor(m_txtMsgBox, sf::Color(textDefaultColor.r, textDefaultColor.g, textDefaultColor.b, m_msgWaitTime));

    if (!m_showMsg)
    {
        if (m_msgAnswer == MsgAnswer::NO)
        {
            // if is OK message box the answer is automatically YES
            if (!m_mbYesNo)
            {
                m_msgAnswer = MsgAnswer::YES;
                m_gameSysExt.playSound(m_sndSelectOption);

                ////////////////////////////////////////////////////////////
                // code for Android version
                #if defined(__ANDROID__)
                m_gameSysExt.useVibrate(m_vibrateTimeDuration);
                #endif
                ////////////////////////////////////////////////////////////
            }
            else m_gameSysExt.playSound(m_sndCancel);
        }
        else
        {
            m_gameSysExt.playSound(m_sndSelectOption);

            ////////////////////////////////////////////////////////////
            // code for Android version
            #if defined(__ANDROID__)
            m_gameSysExt.useVibrate(m_vibrateTimeDuration);
            #endif
            ////////////////////////////////////////////////////////////
        }
    }
}

void is::GameDisplay::drawMsgBox()
{
    if (m_showMsg)
    {
        m_app.draw(m_recMsgBox);
        m_app.draw(m_sprMsgBox);

        if (m_mbYesNo)
        {
            m_app.draw(m_txtMsgBoxYes);
            m_app.draw(m_txtMsgBoxNo);
            m_app.draw(m_sprMsgBoxButton1);
            m_app.draw(m_sprMsgBoxButton2);
        }
        else
        {
            m_app.draw(m_txtMsgBoxOK);
            m_app.draw(m_sprMsgBoxButton3);
        }

        m_app.draw(m_txtMsgBox);
    }
}

void is::GameDisplay::drawScreen()
{
    m_app.clear(m_windowBgColor);
    #if defined(__ANDROID__)
    if (m_appIsActive)
    #endif // defined
    draw();
    m_app.display();
}

bool is::GameDisplay::loadParentResources()
{
    // load sound
    if (!m_sbWitch.loadFromFile(SFX_DIR + "change_option.ogg"))             return false;
    if (!m_sbCancel.loadFromFile(SFX_DIR + "cancel.ogg"))                   return false;
    if (!m_sbSelectOption.loadFromFile(SFX_DIR + "select_option.ogg"))      return false;

    m_sndSwitch.setBuffer(m_sbWitch);
    m_sndCancel.setBuffer(m_sbCancel);
    m_sndSelectOption.setBuffer(m_sbSelectOption);

    // load message box sprite
    if (!m_texMsgBox.loadFromFile(GUI_DIR + "confirm_box.png"))           return false;
    if (!m_sprMsgButton.loadFromFile(GUI_DIR + "confirm_box_button.png")) return false;

    is::createSprite(m_texMsgBox, m_sprMsgBox, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f));
    is::createSprite(m_sprMsgButton, m_sprMsgBoxButton1, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f));
    is::createSprite(m_sprMsgButton, m_sprMsgBoxButton2, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f));
    is::createSprite(m_sprMsgButton, m_sprMsgBoxButton3, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f));

    is::createRectangle(m_recMsgBox, sf::Vector2f(VIEW_W + 40.f, VIEW_H + 40.f), sf::Color(0, 0, 0, 200), 0.f, 0.f);

    is::centerSFMLObj(m_sprMsgBox);
    is::centerSFMLObj(m_sprMsgBoxButton1);
    is::centerSFMLObj(m_sprMsgBoxButton2);
    is::centerSFMLObj(m_sprMsgBoxButton3);

    // load font
    if (!m_font1.loadFromFile(FONT_DIR + "hemi-head.ttf")) return false;
    if (!m_font2.loadFromFile(FONT_DIR + "sansation.ttf")) return false;

    is::createText(m_font1, m_txtMsgBox, "", 0.f, 0.f, 20);
    is::createText(m_font1, m_txtMsgBoxYes, "YES", 0.f, 0.f, 18);
    is::createText(m_font1, m_txtMsgBoxNo, "NO", 0.f, 0.f, 18);
    is::createText(m_font1, m_txtMsgBoxOK, "OK", 0.f, 0.f, 18);

    return true;
}

float is::GameDisplay::getDeltaTime()
{
    float dt = m_clock.restart().asSeconds();
    if (dt > is::MAX_CLOCK_TIME) dt = is::MAX_CLOCK_TIME;
    return dt;
}

bool is::GameDisplay::isRunning() const
{
    return m_isRunning;
}
}
