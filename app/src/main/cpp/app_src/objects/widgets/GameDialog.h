#ifndef GAMEDIALOG_H_INCLUDED
#define GAMEDIALOG_H_INCLUDED

#include <cstring>
#include "../../../isEngine/system/display/GameDisplay.h"
#include "../../language/GameLanguage.h"

////////////////////////////////////////////////////////////
/// \brief Displays and manages game dialogs
///
////////////////////////////////////////////////////////////
namespace is
{
class GameDialog : public is::MainObject
{
public:
    GameDialog(sf::Texture &tex, sf::Font &fnt, is::GameDisplay *scene);

    ////////////////////////////////////////////////////////////
    /// \brief Represents the different dialogs
    ///
    /// Each enum is linked to an array of string representing
    /// a dialogs found in GameLanguage.h
    ////////////////////////////////////////////////////////////
    enum DialogIndex
    {
        DIALOG_NONE = -1,
        DIALOG_HELLO,

        // example
        // DIALOG_YOUR_DIALOG
    };

    ////////////////////////////////////////////////////////////
    /// \brief Link enum to an array of string representing the
    /// dialog in GameLanguage.h
    ///
    /// Each time an array of string representing a dialog is added
    /// it must be linked to its enum to be able to launch it later
    /// with the setDialog() method.
    ////////////////////////////////////////////////////////////
    void linkArrayToEnum()
    {
        auto setMsg = [this](std::string txt)
        {
            m_strDialog = txt;
        };
        auto checkMsg =[this, &setMsg](std::string txt[])
        {
            if (m_msgIndex < m_msgIndexMax) setMsg(txt[m_msgIndex + m_scene->getGameSystem().m_gameLanguage]);
        };

        // each enum with its array of string
        switch (m_dialogIndex)
        {
            case DIALOG_HELLO:
                m_msgIndexMax = is::arraySize(is::lang::dialog_hello);
                checkMsg(is::lang::dialog_hello);
            break;

            // example
            // case DIALOG_YOUR_DIALOG:
            //     m_msgIndexMax = is::arraySize(is::lang::dialog_your_dialog);
            //     checkMsg(is::lang::dialog_your_dialog);
            // break;

            default:
            break;
        }
    }

    void step(const float &DELTA_TIME);

    /// launch a dialog based on the enumeration index
    void setDialog(DialogIndex dialogIndex);
    void setMouseInCollison(bool val);
    void draw(is::Render &surface);

    DialogIndex getDialogIndex() const
    {
        return m_dialogIndex;
    }

    bool getMouseInCollison() const
    {
        return m_mouseInCollison;
    }

    bool showDialog() const
    {
        return m_showDialog;
    }

private:
    is::GameDisplay *m_scene;
    sf::Text m_txtDialog, m_txtSkip;
    std::string m_strDialog;
    sf::Sprite m_sprNext, m_sprSkip;

    bool m_showDialog, m_mouseInCollison, m_dialogEnd, m_newLine;
    int m_msgIndex, m_msgIndexMax, m_size;
    float m_blindTime;
    DialogIndex m_dialogIndex;
};
}

#endif // GAMEDIALOG_H_INCLUDED
