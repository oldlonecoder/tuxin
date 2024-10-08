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

#include "tuxin/tools/book.h"         ///< application book logs and journal.
#include "tuxin/tools/geometry.h" ///< lus::string, colors, dimensions management.

//#include <map>
//#include <vector>
//#include <string_view>
#include <termios.h>
#include <unistd.h>
//#include <thread>
//#include <mutex>
#include <csignal>
#include "tuxin/tools/signals.h"


//#include <condition_variable>
//#include "tuxin/tui/twindc.h"

#include "tuxin/tui/globals.h"

namespace tuxin::ui
{



/**
 * @brief class terminal initilizes and handles few console/terminal io requests in the ansi-/DEC/VT-x protocoles.
 * 
 */
class TUXIN_API terminal final
{

    static ui::rectangle    _geometry_;
    static signals::action<rectangle> _winch;
public:

    //static terminal& instance();
    //terminal();
    ~terminal();
    static book::code begin();
    static book::code end();

    
    static void switch_alternate();
    static void switch_back();

    static void start_mouse();
    static void stop_mouse();

    static void clear();
    static void cursor_off();
    static void cursor_on();
    static void cursor(ui::cxy xy);
    static void mv(globals::direction::type dir=globals::direction::right, int d=1);

    enum caret_shapes: u8
    {
        def,
        bloc_blink,
        block_steady,
        under_blink,
        under_steady,
        vbar_blink,
        vbar_steady
    } _shape_{caret_shapes::def};

    enum class DECMode 
    {
        line_wrap               = 7,
        crs_shape               = 25,
        mouse_X10               = 9,
        mouse_vt200             = 1000,
        mouse_vt200_hl          = 1001,
        mouse_report_buttons    = 1002,
        mouse_report_any        = 1003, 
        mouse_utf8              = 1005,
        mouse_sgr_ext_mode      = 1006,
        mouse_urxvt_mode        = 1015,
        mouse_sgr_pixel_mode    = 1016,
        alternate_screen        = 1049
    };

    static ui::rectangle geometry() { return _geometry_;}
    static constexpr const char* CSI = "\x1b[";
    static signals::action<rectangle>& resize_signal();

private:
    friend class application;

    static book::code query_size();
    static void resize_signal(int );

};
 // class terminal


} // namespace lus::intui
