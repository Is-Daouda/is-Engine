#ifndef GAMEHELP_H_INCLUDED
#define GAMEHELP_H_INCLUDED

#include <cstring>
#if defined(IS_ENGINE_USE_SDM)
#include "../../../isEngine/system/entity/MainObject.h"
#else
#include "../../../isEngine/system/display/GameDisplay.h"
#endif // defined
#include "../../language/GameLanguage.h"

////////////////////////////////////////////////////////////
/// \brief Displays and manages game dialogs
///
////////////////////////////////////////////////////////////
class GameDialog : public is::MainObject
{
public:
    GameDialog(is::GameDisplay *scene);

    ////////////////////////////////////////////////////////////
    /// \brief Represents the different dialogs
    ///
    /// Each enum is linked to an array of string representing
    /// a dialogs found in GameLanguage.h
    ////////////////////////////////////////////////////////////
    enum DialogIndex
    {
        DIALOG_NONE = -1,
        DIALOG_PLAYER_MOVE,
        DIALOG_PLAYER_ATTACK,
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
        auto setMsg = [this](std::wstring txt)
        {
            m_strDialog = txt;
        };
        auto checkMsg =[this, &setMsg](std::wstring txt[])
        {
            if (m_msgIndex < m_msgIndexMax) setMsg(txt[m_msgIndex + m_scene->getGameSystem().m_gameLanguage]);
        };

        // each enum with its array of string
        switch (m_dialogIndex)
        {
            case DIALOG_PLAYER_MOVE:
                m_msgIndexMax = is::arraySize(is::lang::dialog_player_move);
                checkMsg(is::lang::dialog_player_move);
            break;

            case DIALOG_PLAYER_ATTACK:
                m_msgIndexMax = is::arraySize(is::lang::dialog_player_attack);
                checkMsg(is::lang::dialog_player_attack);
            break;

            default:
            break;
        }
    }

    void loadResources(sf::Texture &tex, sf::Font &fnt);
    void step(const float &DELTA_TIME);

    /// launch a dialog based on the enumeration index
    void setDialog(DialogIndex dialogIndex);
    void setMouseInCollison(bool val);
    void draw(sf::RenderTexture &surface);

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
    std::wstring m_strDialog;
    sf::Sprite m_sprNext, m_sprSkip;

    bool m_showDialog, m_mouseInCollison, m_dialogEnd, m_newLine;
    int m_msgIndex, m_msgIndexMax, m_size;
    float m_blindTime;
    DialogIndex m_dialogIndex;
};

#endif // GAMEHELP_H_INCLUDED
