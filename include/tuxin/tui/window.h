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


#include "tuxin/tui/element.h"
#include "tuxin/tui/globals.h"


namespace tuxin::ui 
{

class TUXIN_API window : public element 
{
public:
    window():element(){}
    window(const std::string w_id,globals::uistyle::Type u_style);
    ~window() override;


    book::code setup_ui() override;
    book::code draw() override;
    book::code redraw() override;
    book::code resize(ui::size new_sz) override;


protected:
    //void      dirty(element::painter& _painter) override;


};


}
