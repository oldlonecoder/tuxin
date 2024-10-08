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


#if defined(linux)
#   include <unistd.h>
//#   include <sys/epoll.h>
//#   include <fcntl.h>
#else
#    error "non-linux os not implemented yet"
#endif

#include "tuxin/tools/book.h"
//#include "tuxin/tui/terminal.h"
//#include "tuxin/tui/twindc.h"
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <sys/types.h>




namespace tuxin::ui
{
using namespace integers;




struct keyevent
{
        /**
     * @brief Key mnemonics.
     *
     */
    enum enums : U8
    {
        ArrowUP    ,
        ArrowDown  ,
        ArrowLeft  ,
        ArrowRight ,
        Enter      ,
        ESC        ,
        BS         ,
        Home       ,
        End        ,
        PgUp       ,
        PgDown     ,
        INS        ,
        TAB        ,
        DEL        ,
        F1         ,
        F2         ,
        F3          ,
        F4          ,
        F5          ,
        F6          ,
        F7          ,
        F8          ,
        F9          ,
        F10         ,
        F11         ,
        F12         ,
        SF2         ,
        ShiftEnd    ,
        ShiftHome    ,
        ShiftArrowUp,
        ShiftArrowDown,
        ShiftArrowLeft,
        ShiftArrowRight,
//        ShiftF1,
//        ShiftF2,
        ShiftF3,
        ShiftF4,
        ShiftF5,
        ShiftF6,
        ShiftF7,
        ShiftF8,
        ShiftF9,
        ShiftF10,
        ShiftF11,
        ShiftF12,
        ShiftCtrlArrowLeft,
        ShiftCtrlArrowRight,
        ShiftCtrlArrowUp,
        ShiftCtrlArrowDown,
        CtrlArrowLeft,
        CtrlArrowRight,
        CtrlArrowUp,
        CtrlArrowDown,
        CtrlInsert,
        CtrlHome,
        CtrlQ,
        CtrlS,
        CtrlV,
        CtrlBS,
        ShiftTab,
        ShiftEnter,
        CtrlF8,
        ShiftCtrlDel,
        ShiftCtrlHome,
        ShiftAltArrowLeft,
        ShiftAltArrowRight,
        ShiftAltArrowUp,
        ShiftAltArrowDown,
        ShiftAltEnd,
        ShiftAltHome,
        ShiftAltPgUp,
        ShiftAltPgDown,
        ShiftPageUp,
        ShiftPageDown,
        CtrlPageUp,
        CtrlPageDown,
        CtrlDelete,
        CtrlEnd,
        AltLeftArrow,
        AltRightArrow,
        AltUpArrow,
        AltDownArrow,
        CtrlAltLeftArrow,
        CtrlAltRightArrow,
        CtrlAltUpArrow,
        CtrlAltDownArrow,

        //...

        None,

    };
    U64 code{0}; ///< enough room for each BYTE ex [SHIFT+F5] bytes sequence: 0x1b,0x5b,0x31,0x35,0x3b,0x32,0x7e
                 ///< is compressed into 0x00005B31353B327E => 1b can be removed knowing it is a (ctrl)sequence.
                 ///< ...But we need to compact the bytes sequence into a u64 each time.
                 ///< so it needs to be verified if U64==U64 vs str comp is that faster so we can switch
                 ///< And maybe even enough to include data from incoming(as of sept 11,2024) support to mouse events.
    std::string_view description;
    char ansi_seq[20]; // Null-terminated chars array - We keep storing the raw sequence in string of bytes
    keyevent::enums  mnemonic{enums::None};
    using keydb = std::map<u64,keyevent>;
    using key_group = std::vector<keyevent>;
    using list      = keyevent::key_group;
    static keyevent::key_group command_keys_db;
    static keyevent::key_group shifted_command_keys_db;
    static keyevent::key_group ctrl_command_keys_db;
    static keyevent nokey;
//    std::string_view operator[](key_event::enums) const; -- disabled. It was at the beginning when there was only a single keys group...
    //static const key_event& query(key_event::key_group& k_db, const char* Seq);
    //static const key_event& query(const char* Seq);
    static const keyevent& query(U64 key_code);
    static const keyevent& query(keyevent::key_group& k_db, U64 key_code);
    std::string_view sequence();

};


struct commandevent
{

};

struct fileinputevent{};


// Special handling is required for HMTM which is not described in this document. In order to highlight terminals should support shift-mouseclick while mouse tracking is enabled for the user to copy and paste.
// xterm Mouse Tracking Flags
// Code	Effect	Note
// 0	MB1	Mouse Button 1 pressed
// 1	MB2	Mouse Button 2 pressed
// 2	MB3	Mouse Button 3 pressed
// 4	MB+S	Mouse Button + Shift
// 8	MB+A	Mouse Button + Alt
// 8	MB4	Mouse Button 4 pressed
// 10	MB5	Mouse Button 5 pressed
// 16	MB+C	Mouse Button + Ctrl
// 32	MBM	Mouse Button Motion
// 64	MWU	Mouse Wheel Up
// 65	MWD	Mouse Wheel Down
// 128	MB8	Mouse Button 8 pressed
struct mouse
{


    struct
    {   // -- buttons: 0 = release; 1 = pressed - no matter revious and motion states
        u8 left   :1;
        u8 middle :1;
        u8 right  :1;
        u8 _4     :1;
        u8 _5     :1;
        u8 _6     :1;
    }button{0};

    // Modifiers:
    bool shift = false;
    bool meta = false;
    bool control = false;

    // Coordinates:
    bool move{false}; ///< Quick check for mouse motion ( delta > {0,0} )

    ui::cxy oldxy {};///< {0,0} or last position.
    ui::cxy xy{}; ///< move,delta := |xy-oldxy|
    ui::cxy dxy{}; ///< move,delta := |xy-oldxy|
    ui::cxy delta(); ///<
    std::string to_string();
};



struct event
{

    /*
     * using queu = std::queue<event>;
     * static book::code poll()
     *
     */


    static book::code get_stdin_event(event& _event_, timeval tv={0xffffffffff,0});
    static book::code init();
    static mouse mouse_data;
    operator bool();

    enum class type : u8
    {
        key_input,
        key_command,
        mouse_move,
        mouse_button,
        UNCOMPLETED,
        DROP,
        CHARACTER,
        MOUSE,
        CURSOR_POSITION,
        CURSOR_SHAPE,
        SPECIAL,

        //...
        noop,
    }event_type{event::type::noop};

    union
    {
        keyevent        kev;
        mouse           mev;
        commandevent    cmdev;
        fileinputevent  fev;
    }data{};

    static constexpr u64 noevent                = 0x0000000000000000;
    static constexpr u64 mouse_left_down        = 0x0000000000000001;
    static constexpr u64 mouse_right_down       = 0x0000000000000002;
    static constexpr u64 mouse_middle_down      = 0x0000000000000004;
    static constexpr u64 mouse_left_release     = 0x0000000000000008;
    static constexpr u64 mouse_right_release    = 0x0000000000000010;
    static constexpr u64 mouse_middle_release   = 0x0000000000000020;
    static constexpr u64 mouse_move             = 0x0000000000000040;
    static constexpr u64 mouse_drag_enter       = 0x0000000000000080;
    static constexpr u64 mouse_drag_leave       = 0x0000000000000100;
    static constexpr u64 mouse_drag             = 0x0000000000000200;
    static constexpr u64 mouse_hover_enter      = 0x0000000000000400;
    static constexpr u64 mouse_hover_leave      = 0x0000000000000800;
    static constexpr u64 mouse_hover            = 0x0000000000001000;
    static constexpr u64 control_key            = 0x0000000000002000;
    static constexpr u64 character_key          = 0x0000000000004000;
    static constexpr u64 cancel                 = 0x0000000000008000;
    static constexpr u64 accept                 = 0x0000000000010000;
    static constexpr u64 quit                   = 0x0000000000020000;
    static constexpr u64 close                  = 0x0000000000040000;
    static constexpr u64 open                   = 0x0000000000080000;
    static constexpr u64 save                   = 0x0000000000100000;
    static constexpr u64 scroll                 = 0x0000000000200000;
    static constexpr u64 clear                  = 0x0000000000400000;

    //...
    static constexpr u64 extended_event         = 0x8000000000000000;
    u64 event_bits{event::noevent};
    static u64 prev_mouse_state;

private:


    static void shutdown_listeners();

    /*!
        \brief The conio_parser class interpret input sequence(s) from stdin.

        \author Serge Lussier / oldlonecoder (serge.lussier@oldlonecoder.club)
        \note Regarding console and screen input-output, I am using here and here little parts of code and functionnality from the Arthur Sonzogni FTXUI project
        because I am just too (intellectually) lazy to learn the low-level of linux/unix system programming.
        I found that Arthur's work is the most beautiful and easy to understand despite the fact that it is rather a functional programming (using objects) approach.
        And I am one who refuses to embrace the modern advanced c++ meta-programming. I am stuck in the early 2000-2010 era of doing object-oriented programming.
        I mean that I learned to program GUI on linux using Trolltech Qt.
        Particularly for the UTF8 parser, and the mouse report, I owe him a hug and a big thanks for sharing his work.
     */
    struct conio_parser
    {
        std::string_view _seq_;
        std::string_view::iterator it{};

        enum class type :u8 {
            // Copyright 2020 Arthur Sonzogni. All rights reserved.
            // https://github.com/ArthurSonzogni/FTXUI
            UNCOMPLETED,
            DROP,
            CHARACTER,
            MOUSE,
            CURSOR_POSITION,
            CURSOR_SHAPE,
            SPECIAL,
            // ---------------------------------------------------
        }parse_type{conio_parser::type::UNCOMPLETED};
        bool eat();
        u8 current();

        conio_parser() = default;
        ~conio_parser();
        // Inspired from https://github.com/ArthurSonzogni/FTXUI
        // [ terminal_input_parser.hpp/cpp ]
        event::type parse(event&, const char*);
        event::type parse_utf8(event&);
        event::type parse_esc(event& evd);
        event::type parse_dcs();
        event::type parse_csi(event &evd);
        event::type parse_ss_1_2(event& evd);
        event::type parse_osc(event& ev);
        event::type parse_mouse(event& _ed, bool _altered, bool _pressed, std::vector<int> _args);
        event::type parse_caret_report(std::vector<int> _args);

    };


};




}
