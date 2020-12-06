#ifndef GAMELANGUAGE_H_INCLUDED
#define GAMELANGUAGE_H_INCLUDED

#include "../../isEngine/system/function/GameKeyName.h"

/*
 * This file allows you to define the languages you want to use in the game.
 * To use a language you must define a array. the first index represents the first language
 * (e.g lang_array[0] => eng) and the index following its translation (e.g lang_array[1] => fr).
 *
 * example to display several sentences in the dialog manager.
 * lang_array[] = {"eng 1", "translation fr 1", "eng 2", "translation fr 2", ...};
 * (Go to the GameDialog Class to see how we implement languages to make sentences in dialogs)
 */

namespace is
{
//////////////////////////////////////////////////////
/// \brief Access to content that allows internationalization of the game
///
//////////////////////////////////////////////////////
namespace lang
{
////////////////////////////////////////////////////////////
/// \brief Represent the index of each language
///
////////////////////////////////////////////////////////////
enum GameLanguage
{
    ENGLISH,  ///< English language index
    FRANCAIS, ///< French language index

    // example
    // YOUR_LANGUAGE ///< Your language index
};

// ------------------------ message box answer ------------------------
static std::string pad_answer_ok[]  = {"OK" , "OK"};
static std::string pad_answer_yes[] = {"YES", "OUI"};
static std::string pad_answer_no[]  = {"NO" , "NON"};

// ------------------------ message box sentences ------------------------
static std::string msg_quit_game[] = {"Quit Game", "Quitter le Jeu"};

// example
// static std::string msg_your_message[] = {"Message in English", "Message in French"};

// ------------------------ RPG dialog ------------------------
static std::string pad_dialog_skip[] = {"Skip", "Passer"};

static std::wstring dialog_hello[] = {L"Hello !",
                                          L"Salut !",
                                      L"Ready to make the future best game in the world!",
                                          L"Prêt à créer le futur meilleur jeu du monde !"};

// example
// static std::wstring dialog_your_dialog[] = {L"Represents the first message of the dialog in English",
//                                                 L"Represents the first message of the dialog in French",
//                                             L"Represents the second message of the dialog in English",
//                                                 L"Represents the second message of the dialog in French"};
}
}

#endif // GAMELANGUAGE_H_INCLUDED
