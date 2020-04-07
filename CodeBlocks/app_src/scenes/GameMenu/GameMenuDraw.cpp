#include "GameMenu.h"

void GameMenu::draw()
{
    const short OP_START_GAME(0),
                OP_CONTINUE(1),
                OP_CONFIG_PAD(2);

    // draw background
    m_surface.draw(m_sprScreenBG);

    // draw game title
    m_surface.draw(m_txtGameTitle);

    // draw button
    if (m_optionIndex != OP_START_GAME) m_surface.draw(m_sprPad1);
    if (m_optionIndex != OP_CONTINUE) m_surface.draw(m_sprPad2);
    if (m_optionIndex != OP_CONFIG_PAD) m_surface.draw(m_sprPad3);
    m_surface.draw(m_sprButtonSelect);
    m_surface.draw(m_txtStartGame);
    m_surface.draw(m_txtContinue);
    m_surface.draw(m_txtPadConfig);
    for (unsigned int i(0); i < is::arraySize(m_txtOptionValue); i++) m_surface.draw(m_txtOptionValue[i]);

    // show the game pad configuration page
    if (m_pageName == PAGE_PAD_CONFIG)
    {
        m_surface.draw(m_recCfgBg);
        m_surface.draw(m_txtMovePad);
        m_surface.draw(m_sprPermuteAB);
        m_surface.draw(m_txtPermuteAB);
        m_surface.draw(m_txtSetAlpha);
        m_surface.draw(m_sprAddAlpha);
        m_surface.draw(m_sprReduceAlpha);
        for (int i(0); i < 2; i++) m_surface.draw(m_sprJoystick[i]);
        if (m_padCfgClicked) m_surface.draw(m_recSelectPad);
        m_surface.draw(m_recLine);
    }

    // show cancel button
    if (m_pageName == PAGE_PAD_CONFIG) m_cancelBt.draw(m_surface);

    ///////////////////////////////////////
    // message box
    drawMsgBox();
    ///////////////////////////////////////
}
