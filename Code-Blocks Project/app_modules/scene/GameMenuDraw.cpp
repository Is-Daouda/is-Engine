#include "GameMenu.h"

void GameMenu::draw()
{
    m_app.draw(m_sprBg);
    m_app.draw(m_txtTitle);
    for (int i(0); i < TXT_OPTION_NUMBER; i++) m_app.draw(m_txtOptionValue[i]);
    for (int i(0); i < 2; i++) m_app.draw(m_sprButton[i]);
    m_app.draw(m_sprButtonSelect);
    m_app.draw(m_txtStartGame);
    m_app.draw(m_txtContinue);

    m_app.draw(m_txtVersion);

    // message box
    drawMsgBox();

    // transition rectangle
    m_app.draw(m_recTransition);
}
