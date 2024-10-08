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
#include "tuxin/tui/events.h"

namespace tuxin::ui
{


/**
 * @brief This element is used to display the keyboard and mouse events.
 * 
 */
class TUXIN_API intrack : public element 
{
    event ev{}; ///< kev max length = 21 chars. ; mouse repost : 25 chars
    
    
    rectangle _key_area_{{0,0},ui::size{21,1}};
    rectangle _mouse_area_{{21,0},ui::size{25,1}};

    element::painter _keyevent_painter_;
    element::painter _mouseevent_painter_;


public:
    intrack();
    intrack(element* _parent, const std::string& a_id);
    ~intrack() override {};
    book::code update_event_data(const event& e);
    book::code setup_ui() override;

protected:
    book::code draw() override;
    

};

}