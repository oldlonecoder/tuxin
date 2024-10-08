// Created by oldlonecoder on 8/13/24.
//

//#ifndef INTUI_GLOBALS_H
//#define INTUI_GLOBALS_H
/***************************************************************************
 *   Copyright (C) 1965/1987/2023 by Serge Lussier                         *
 *   serge.lussier@oldlonecoder.club                                       *
 *                                                                         *
 *                                                                         *
 *   Unless otherwise specified, all Code in this project is written       *
 *   by the author (Serge Lussier)                                         *
 *   and no one else then not even {copilot, chatgpt, or any other AI}     *
 *   --------------------------------------------------------------------- *
 *   Copyrights from authors other than Serge Lussier also apply here      *
 ***************************************************************************/


#pragma once


#include "tuxin/tui/window.h"
#include "utility"
#include "stack"
#include <list> // statck(or z-ordered) of toplevel elements: std::list is for more efficient deletion/insertion in the midle of sequence
                // pile (ou z-ordered) des éléments toplevel: j'utilise std::list pour une meilleur facilité à gérer les déplacements et les changements de valeur 'z'

namespace tuxin::ui
{



class TUXIN_API desktop : public element
{
    twindc _back_{};
    //std::pair<twindc&,twindc&> winbuffers{_windc_,_back_}; ///< Trying double buffering because moving widgets/windows will flash during the redraws
    std::stack<rectangle> dirties{};
    std::list<window*>   toplevels{};

public:
    desktop():element(){}
    desktop(const std::string& prog_id);

    ~desktop() override;

    book::code setup_ui() override;
    book::code draw() override;
    book::code redraw() override;
    book::code resize(ui::size new_sz) override;

protected:
    //void      dirty(element::painter& _painter) override;

};



}
