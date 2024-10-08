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

namespace tuxin::ui
{

class TUXIN_API statusbar : public element
{
public:
    statusbar();
    statusbar(element* _parent, const std::string& a_id);
    virtual book::code setup_ui();
    //virtual book::code draw();
    //virtual book::code redraw();
    //virtual book::code resize(ui::size new_sz);
    //virtual book::code parent_resized();

protected:
    //virtual void dirty(element::painter& _painter);
    //virtual book::code apply_placement();
};



} // namespace tuxin::ui


