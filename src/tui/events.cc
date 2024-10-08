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

#include "tuxin/tui/events.h"
#include <sys/select.h>
#include <sys/ioctl.h>


namespace tuxin::ui
{

keyevent keyevent::nokey{};
mouse event::mouse_data{};
u64 event::prev_mouse_state{event::noevent}; ///< Record previous bitmap of move event flags for the next mouse event.


// This is the permanent stdin input flags for the duration of the intui application:
//-----------------------------------------------------------------------------------




keyevent::key_group keyevent::command_keys_db =
    {
        {0x00000000001b5b41,"Arrow UP",     {},  keyevent::ArrowUP    },
        {0x00000000001b5b42,"Arrow Down",   {},  keyevent::ArrowDown  },
        {0x00000000001b5b44,"Arrow Left",   {},  keyevent::ArrowLeft  },
        {0x00000000001b5b43,"Arrow Right",  {},  keyevent::ArrowRight },
        {0x000000000000000A,"Enter",        {},  keyevent::Enter      },
        {0x000000000000001b,"ESC",          {},  keyevent::ESC        },
        {0x000000000000007F,"Back Space",   {},  keyevent::BS         },
        {0x00000000001b5b48,"HOME",         {},  keyevent::Home       },
        {0x00000000001b5b46,"End",          {},  keyevent::End        },
        {0x000000001b5b357e,"Page UP",      {},  keyevent::PgUp       },
        {0x000000001b5b367e,"Page Down",   {}, keyevent::PgDown     },
        {0x000000001b5b327e,"Insert",      {}, keyevent::INS        },
        {0x000000001b5b337e,"Delete",      {}, keyevent::DEL        },
        {0x00000000001b4f50,"F1",          {}, keyevent::F1         },
        {0x00000000001b4f51,"F2",          {}, keyevent::F2         },
        {0x00000000001b4f52,"F3",          {}, keyevent::F3         },
        {0x00000000001b4f53,"F4",          {}, keyevent::F4         },
        {0x0000001b5b31357e,"F5",          {}, keyevent::F5         },
        {0x0000001b5b31377e,"F6",          {}, keyevent::F6         },
        {0x0000001b5b31387e,"F7",          {}, keyevent::F7         },
        {0x0000001b5b31397e,"F8",          {}, keyevent::F8         },
        {0x0000001b5b32307e,"F9",          {}, keyevent::F9         },
        {0x0000001b5b32317e,"F10",         {}, keyevent::F10        },
        {0x0000001b5b32337e,"F11",         {}, keyevent::F11        },
        {0x0000001b5b32347e,"F12",         {}, keyevent::F12        },
        {0x0000000000000009,"TAB",         {}, keyevent::TAB        }
};


keyevent::key_group keyevent::shifted_command_keys_db=
    {
        {0x000000001b4f3251,"Shift+F2",              {},keyevent::SF2            },
        {0x00001b5b313b3241,"Shift+ArrowUp",         {},keyevent::ShiftArrowUp   },
        {0x00001b5b313b3242,"Shift+ArrowDown",       {},keyevent::ShiftArrowDown },
        {0x00001b5b313b3244,"Shift+ArrowLeft",       {},keyevent::ShiftArrowLeft },
        {0x00001b5b313b3243,"Shift+ArrowRight",      {},keyevent::ShiftArrowRight},
        {0x00001b5b313b3246,"Shift+End",             {},keyevent::ShiftEnd},
        {0x00001b5b313b3248,"Shift+Home",            {},keyevent::ShiftHome},
        {0x000000001b4f3252,"Shift+F3",              {},keyevent::ShiftF3},
        {0x000000001b4f3253,"Shift+F4",              {},keyevent::ShiftF4},
        {0x001b5b31353b327e,"Shift+F5",              {},keyevent::ShiftF5},
        {0x001b5b31373b327e,"Shift+F6",             {},keyevent::ShiftF6},
        {0x001b5b31383b327e,"Shift+F7",             {},keyevent::ShiftF7},
        {0x001b5b31393b327e,"Shift+F8",             {},keyevent::ShiftF8},
        {0x001b5b32303b327e,"Shift+F9",             {},keyevent::ShiftF9},
        {0x001b5b32313b327e,"Shift+F10",            {},keyevent::ShiftF10},
        {0x001b5b32333b327e,"Shift+F11",            {},keyevent::ShiftF11},
        {0x001b5b32343b327e,"Shift+F12",            {},keyevent::ShiftF12},
        {0x00000000001b5b5a,"Shift+Tab",            {},keyevent::ShiftTab},//...
        {0x00000000001b4f4d,"Shift+Enter",          {},keyevent::ShiftEnter},
        {0x00001b5b313b3644,"Shift+Ctrl+ArrowLeft", {},keyevent::ShiftCtrlArrowLeft},
        {0x00001b5b313b3643,"Shift+Ctrl+ArrowRight",{},keyevent::ShiftCtrlArrowRight},
        {0x00001b5b313b3641,"Shift+Ctrl+ArrowUp",   {},keyevent::ShiftCtrlArrowUp},
        {0x00001b5b313b3642,"Shift+Ctrl+ArrowDown", {},keyevent::ShiftCtrlArrowDown},
        {0x00001b5b313b3646,"Shift+Ctrl+Del",       {},keyevent::ShiftCtrlDel},
        {0x00001b5b313b3648,"Shift+Ctrl+Home",      {},keyevent::ShiftCtrlHome},
        {0x00001b5b313b3444,"Shift+Alt+ArrowLeft",  {},keyevent::ShiftAltArrowLeft},
        {0x00001b5b313b3443,"Shift+Alt+ArrowRight", {},keyevent::ShiftAltArrowRight},
        {0x00001b5b313b3441,"Shift+Alt+ArrowUp",    {},keyevent::ShiftAltArrowUp   },
        {0x00001b5b313b3442,"Shift+Alt+ArrowDown",  {},keyevent::ShiftAltArrowDown },
        {0x00001b5b313b3446,"Shift+Alt+End",        {},keyevent::ShiftAltEnd },
        {0x00001b5b313b3448,"Shift+Alt+Home",       {},keyevent::ShiftAltHome },
        {0x00001b5b353b347e,"Shift+Alt+PagegUp",    {},keyevent::ShiftAltPgUp },
        {0x00001b5b363b347e,"Shift+Alt+PageDown",   {},keyevent::ShiftAltPgDown },
        {0x00001b5b353b327e,"Shift+PageUp",         {},keyevent::ShiftPageUp },
        {0x00001b5b363b327e,"Shift+PageDown",       {},keyevent::ShiftPageDown },
        {0x00001b5b353b357e,"Ctrl+PageUp",          {},keyevent::CtrlPageUp },
        {0x00001b5b363b357e,"Ctrl+PageDown",        {},keyevent::CtrlPageDown },
        {0x00001b5b333b357e,"Ctrl+Delete",          {},keyevent::CtrlDelete},
        {0x00001b5b313b3546,"Ctrl+End",             {},keyevent::CtrlEnd},
        {0x00001b5b313b3344,"Alt+LeftArrow",        {},keyevent::AltLeftArrow},
        {0x00001b5b313b3343,"Alt+RightArrow",       {},keyevent::AltRightArrow},
        {0x00001b5b313b3341,"Alt+UpArrow",          {},keyevent::AltUpArrow},
        {0x00001b5b313b3342,"Alt+DownArrow",        {},keyevent::AltDownArrow},
        {0x00001b5b313b3744,"Ctrl+Alt+LeftArrow",   {},keyevent::CtrlAltLeftArrow},
        {0x00001b5b313b3743,"Ctrl+Alt+RightArrow",  {},keyevent::CtrlAltRightArrow},
        {0x00001b5b313b3741,"Ctrl+Alt+UpArrow",     {},keyevent::CtrlAltUpArrow},
        {0x00001b5b313b3742,"Ctrl+Alt+DownArrow",   {},keyevent::CtrlAltDownArrow},

        };


//0x1b,0x5b,0x31,0x3b,0x36,0x44,0x00
keyevent::key_group keyevent::ctrl_command_keys_db=
    {
        {0x00001b5b313b3544,"Ctrl+ArrowLeft",  {}, keyevent::CtrlArrowLeft},
        {0x00001b5b313b3543,"Ctrl+ArrowRight", {}, keyevent::CtrlArrowRight},
        {0x00001b5b313b3541,"Ctrl+ArrowUp"   , {}, keyevent::CtrlArrowUp},
        {0x00001b5b313b3542,"Ctrl+ArrowDown" , {}, keyevent::CtrlArrowDown},
        {0x00001b5b313b3548,"Ctrl+Home",       {}, keyevent::CtrlHome},
        {0x00001b5b323b357e,"Ctrl+Insert",     {}, keyevent::CtrlInsert},
        {0x0000000000000011,"Ctrl+Q",          {}, keyevent::CtrlQ},
        {0x0000000000000013,"Ctrl+S",          {}, keyevent::CtrlS},
        {0x0000000000000016,"Ctrl+V",          {}, keyevent::CtrlV},
        {0x0000000000000008,"Ctrl+Back-Space", {}, keyevent::CtrlBS},
        {0x001b5b31393b357e,"Ctrl+F8",        {}, keyevent::CtrlF8},
        //...
};

/*
const std::map<std::string, std::string> g_uniformize = {
    // Microsoft's terminal uses a different new line character for the return
    // key. This also happens with linux with the `bind` command:
    // See https://github.com/ArthurSonzogni/FTXUI/issues/337
    // Here, we uniformize the new line character to `\n`.
    {"\r", "\n"},

    // See: https://github.com/ArthurSonzogni/FTXUI/issues/508
    {std::string({8}), std::string({127})},

    // See: https://github.com/ArthurSonzogni/FTXUI/issues/626
    //
    // Depending on the Cursor Key Mode (DECCKM), the terminal sends different
    // escape sequences:
    //
    //   Key     Normal    Application
    //   -----   --------  -----------
    //   Up      ESC [ A   ESC O A
    //   Down    ESC [ B   ESC O B
    //   Right   ESC [ C   ESC O C
    //   Left    ESC [ D   ESC O D
    //   Home    ESC [ H   ESC O H
    //   End     ESC [ F   ESC O F
    //
    {"\x1BOA", "\x1B[A"},  // UP
    {"\x1BOB", "\x1B[B"},  // DOWN
    {"\x1BOC", "\x1B[C"},  // RIGHT
    {"\x1BOD", "\x1B[D"},  // LEFT
    {"\x1BOH", "\x1B[H"},  // HOME
    {"\x1BOF", "\x1B[F"},  // END

    // Variations around the FN keys.
    // Internally, we are using:
    // vt220, xterm-vt200, xterm-xf86-v44, xterm-new, mgt, screen
    // See: https://invisible-island.net/xterm/xterm-function-keys.html

    // For linux OS console (CTRL+ALT+FN), who do not belong to any
    // real standard.
    // See: https://github.com/ArthurSonzogni/FTXUI/issues/685
    {"\x1B[[A", "\x1BOP"},    // F1
    {"\x1B[[B", "\x1BOQ"},    // F2
    {"\x1B[[C", "\x1BOR"},    // F3
    {"\x1B[[D", "\x1BOS"},    // F4
    {"\x1B[[E", "\x1B[15~"},  // F5

    // xterm-r5, xterm-r6, rxvt
    {"\x1B[11~", "\x1BOP"},  // F1
    {"\x1B[12~", "\x1BOQ"},  // F2
    {"\x1B[13~", "\x1BOR"},  // F3
    {"\x1B[14~", "\x1BOS"},  // F4

    // vt100
    {"\x1BOt", "\x1B[15~"},  // F5
    {"\x1BOu", "\x1B[17~"},  // F6
    {"\x1BOv", "\x1B[18~"},  // F7
    {"\x1BOl", "\x1B[19~"},  // F8
    {"\x1BOw", "\x1B[20~"},  // F9
    {"\x1BOx", "\x1B[21~"},  // F10

    // scoansi
    {"\x1B[M", "\x1BOP"},    // F1
    {"\x1B[N", "\x1BOQ"},    // F2
    {"\x1B[O", "\x1BOR"},    // F3
    {"\x1B[P", "\x1BOS"},    // F4
    {"\x1B[Q", "\x1B[15~"},  // F5
    {"\x1B[R", "\x1B[17~"},  // F6
    {"\x1B[S", "\x1B[18~"},  // F7
    {"\x1B[T", "\x1B[19~"},  // F8
    {"\x1B[U", "\x1B[20~"},  // F9
    {"\x1B[V", "\x1B[21~"},  // F10
    {"\x1B[W", "\x1B[23~"},  // F11
    {"\x1B[X", "\x1B[24~"},  // F12
};

*/

const keyevent &keyevent::query(keyevent::key_group &k_db, U64 key_code)
{
    for(const auto& k : k_db)
        if(key_code == k.code) return k;

    return keyevent::nokey;
}

const keyevent& keyevent::query(U64 key_code)
{

    if(const keyevent& Ky = query(keyevent::ctrl_command_keys_db, key_code); Ky.mnemonic != keyevent::None)
        return Ky;
    if(auto const &SK = query(keyevent::shifted_command_keys_db, key_code); SK.mnemonic != keyevent::None)
        return SK;
    if(auto const& InK = query(keyevent::command_keys_db, key_code); InK.mnemonic != keyevent::None)
        return InK;

    return keyevent::nokey;
}



std::string_view keyevent::sequence()
{
    return ansi_seq;
}


event::operator bool()
{
    return event_type != type::noop;
}


// Far from being ready to multitask
// void event::shutdown_listeners()
// {
//     ;
// }





book::code event::get_stdin_event(event &_event_, timeval tv)
{
    //book::log() << book::fn::fun;

    fd_set fds;
    FD_ZERO(&fds);                                          // NOLINT
    FD_SET(STDIN_FILENO, &fds);                             // NOLINT
    select(STDIN_FILENO + 1, &fds, nullptr, nullptr, &tv);  // NOLINT

    if(auto e = FD_ISSET(STDIN_FILENO, &fds); !e)
    {
        book::out() << "TIMEOUT";
        _event_.event_type = event::type::noop;
        return book::code::timeout;
    }
    int pksize{0};
    ioctl(0,FIONREAD,&pksize);
    if(!pksize)
    {
        book::out() << color::reset << "stdin triggered with 0 bytes ( likely terminal resize event )...";
        return book::code::empty;
    }
    //book::out() << " STD INPUT EVENT  : " << color::yellow << pksize << color::reset << " bytes";
    char buffer[100];

    size_t r = ::read(STDIN_FILENO, buffer, 100);
    buffer[r] = 0;
    //book::out() << "{" << color::yellow << tuxin::string::bytes(buffer) << color::reset << "}";

    conio_parser cparser;
    _event_.event_type = cparser.parse(_event_, buffer);

    if(_event_.event_type == event::type::DROP)
        return book::code::rejected;

    //if(_event_.event_type == event::type::MOUSE)
    //    book::out() << event::mouse_data.to_string() << color::reset;

    else if(_event_.event_type == event::type::key_command)
    {
        book::out() << "KEY COMMAND: {" << color::lime << _event_.data.kev.description << color::reset << '}';
        if(_event_.data.kev.mnemonic == keyevent::ESC)
            return book::code::cancel;
    }
    return book::code::rejected;
}




/**
 * @brief Will be used when tui subproject goes to multithreads.
 *
 */
void eventshutdown_listeners(){}

/*!
 * \brief event::init
 * \return [book::code::]done when finished or throws book::exception if errors during the execution of init.
 */
book::code event::init()
{
    book::message() << book::fn::fun;
    //...

    return book::code::done;
}



bool event::conio_parser::eat()
{
    it++;
    return it < _seq_.end();
}

event::conio_parser::~conio_parser()
{

}



event::type event::conio_parser::parse(event &_ev_, const char *a_seq_)
{
    //book::log() << book::fn::fun;
    _seq_ = a_seq_; ///@todo handle MSVC craps that forbid "const char*" to be used to construct their string_view !!!
    //book::debug() << book::fn::fun << "{" << color::yellow << tuxin::string::bytes(_seq_) << color::reset << "}:";
    it = _seq_.begin();

    // L'on s'occupe des CSI (Control Sequence Introducer) avant tout:
    if((*it==27) && (_seq_.size()>1)) return parse_esc(_ev_);
    if(*it == 27)
    {
        // systematic/explicitely ESC pressed:
        _ev_.data.kev = keyevent::query(27l);
        book::out() << _ev_.data.kev.description ;
        _ev_.event_type = event::type::key_command;
        return _ev_.event_type;
    }

    //---------------------------------------------------------------
    // Not ESC seq.
    // Check CTRL hit ( *it < ascii(32) ) + ENTER,TAB, BACKSP ...
    // One Byte key. All extra keys are ignored/discarded.

    if((*it < 32) || (*it == 127))
    {

        _ev_.event_type = event::type::key_command;
        book::out() << "KEY_COMMAND: " << color::yellow << (int)*it << color::reset << "';";
        if(keyevent tmpkev = keyevent::query(*it); tmpkev.mnemonic != keyevent::None)
        {
            _ev_.data.kev=tmpkev;
            return _ev_.event_type;
        }
        _ev_.data.kev.code = *it;
        return _ev_.event_type;
    }
    // -- key input.
    book::out() << "CHARACTER:'" << color::yellow << *it << color::reset << "';";
    _ev_.data.kev = keyevent::nokey;
    _ev_.event_type = event::type::CHARACTER; // Extra bytes are all ignored.
    _ev_.data.kev.code = *it;
    return _ev_.event_type;
}


event::type event::conio_parser::parse_esc(event& evd)
{
    //book::log() << book::fn::fun;

    if (!eat()) return event::type::UNCOMPLETED;
    switch (*it)
    {
        case 'P':
            return parse_dcs();
        case '[':
            return parse_csi(evd); ///@note Le focus est ici [ clefs de commandes et autres ], mouse...
        case ']':
            return parse_osc(evd);

            // Expecting 2 characters.
        case ' ':
        case '#':
        case '%':
        case '(':
        case ')':
        case '*':
        case '+':
        case 'O':
        case 'N': {
            if (!eat()) return event::type::UNCOMPLETED;
            return parse_ss_1_2(evd);
        }
        // Expecting 1 character:
        default:
            return event::type::SPECIAL;
    }
}

event::type event::conio_parser::parse_ss_1_2(event &evd)
{
        // 8 bytes max which include the beginning of the buffer (ESC;O | [)

    // Consume the buffer. keyevent::ansi_seq is now the final location.
    //book::debug() << book::fn::fun;
    //book::out() << "copy seq into event kev ansi_seq: ";
    std::strncpy(evd.data.kev.ansi_seq, _seq_.data(), 19);

    auto& code = evd.data.kev.code;
    code = 0;
    auto ln = std::min(size_t(8),std::strlen(evd.data.kev.ansi_seq));
    //book::out() << " Check: ansi_seq to parse: {" << color::yellow << tuxin::string::bytes(evd.data.kev.ansi_seq) << color::reset << "}:";

    U8 _b_ = evd.data.kev.ansi_seq[0]; // start with ESC byte
    code = (code << 8) | _b_;
    _b_ = evd.data.kev.ansi_seq[1]; // no matter '[' or 'O' :
    code = (code << 8) | _b_;
    // Now push the rest towards ln or until  hit or miss:
    for(int x=2;x < ln; x++)
    {
        _b_ = evd.data.kev.ansi_seq[x];
        code = (code << 8) | _b_;
        book::out() << std::format("{:04x}",code);
        if(keyevent tmp_kev = keyevent::query(code); tmp_kev.mnemonic != keyevent::None)
        {
            book::out() << "Match:" << color::lime << tmp_kev.description << color::reset;
            evd.data.kev = tmp_kev;
            evd.event_type = event::type::key_command;
            return evd.event_type;
        }
    }

    return event::type::noop;
}


event::type event::conio_parser::parse_dcs()
{
    return event::type::UNCOMPLETED;
}

event::type event::conio_parser::parse_csi(event& evd)
{

    //book::debug() << book::fn::fun;

    bool altered = false;
    int argument = 0;
    std::vector<int> arguments;
    while (true) {
        if (!eat()) {
            //book::out() << " End of the sequence ";
            return event::type::UNCOMPLETED;
        }

        if (*it == '<') {
            //book::out() << " altered mode";
            altered = true; // Just bypass ...for now...
            continue;
        }

        if (*it >= '0' && *it <= '9') {
            //book::out() << "cursor on digit: '" << color::yellow << (*it-'0') << color::reset << "'";
            argument *= 10;  // NOLINT
            argument += *it - '0';
            continue;
        }

        if (*it == ';') {
            //book::out() << "arg separator: arg value: '" << color::yellow << argument << color::reset << "' ";
            arguments.push_back(argument);
            argument = 0;
            continue;
        }

        // CSI is terminated by a character in the range 0x40–0x7E
        // (ASCII @A–Z[\]^_`a–z{|}~),
        // Note: I don't remember why we exclude '<'
        // To handle F1-F4, we exclude '['.
        if (*it >= '@' && *it <= '~' && *it != '<' && *it != '[')
        {
            //book::out() << "CSI completed: last arg : '" << color::yellow << argument << color::reset << "' ";
            arguments.push_back(argument);
            argument = 0;  // NOLINT
            int c=1;
            //for(auto n : arguments) book::out() << c++ << " > " << std::format("0x{:02x}",n);
            switch (*it) {
                case 'M':
                    return parse_mouse(evd,altered, true, std::move(arguments));
                case 'm':
                    return parse_mouse(evd,altered, false, std::move(arguments));
                case 'R':
                    return parse_caret_report(std::move(arguments));
                default:
                    book::out() << " Switching to parse_ss_1_2():";
                    return parse_ss_1_2(evd);
            }
        }
        book::out() << " Unterminated CSI: switchting to parse_ss_1_2";
        return parse_ss_1_2(evd);

        // Invalid ESC in CSI.
        if (*it == '\x1B') {
            return event::type::SPECIAL;
        }
    }
}


event::type event::conio_parser::parse_osc(event& ev)
{
    tuxin::string str = tuxin::string::bytes(_seq_);
    book::debug() << book::fn::fun << "rec seq: {" << color::yellow << str << color::reset << "} - not implemented yet";
    return event::type::UNCOMPLETED;
}


/*!
   \brief event::conio_parser::parse_mouse
       Code and functionnality from the Arthur Sonzogni's FTXUI project:
       https://github.com/ArthurSonzogni/FTXUI. Adapted by me for this events build.


   \param ref to the ed event data instance
   \param altered key
   \param pressed buttons state
   \param arguments state, position
   \return event::type::MOUSE

   \note Start using old_mev bit fields for the new bit field.
 */
event::type event::conio_parser::parse_mouse(event& ed, bool /*altered - not using, not needed altered report mode... for now*/, bool /*pressed*/, std::vector<int> arguments)
{
    // pressed 'flag' ignored. Relying on the XTerm Button and meta state byte which reports buttons on the lasts two bits:
    // 0=left button pressed
    // 1=right button pressed
    // 2=middle button pressed
    // 3=no button pressed.
    // So I assign button # based on the two bits value to identify button press/release
    //book::log() << book::fn::fun;
    if (arguments.size() != 3) return parse_ss_1_2(ed);
    ed.event_type = event::type::MOUSE;

    event::mouse_data.button = {0,0,0};
    event::mouse_data.button.left   = (arguments[0] & 3) == 0 ? 1 :0;
    event::mouse_data.button.middle = (arguments[0] & 3) == 1 ? 1 :0;
    event::mouse_data.button.right  = (arguments[0] & 3) == 2 ? 1 :0;
    ///@todo Handle the other buttons...
    /// ...

    event::mouse_data.shift     = arguments[0] & 4;
    event::mouse_data.meta      = arguments[0] & 8;
    event::mouse_data.control   = arguments[0] & 0x10;
    if(event::mouse_data.meta)
        book::info() << book::fn::fun << color::pair({.fg=color::grey100, .bg=color::red4}) << "meta" << color::reset;
    event::mouse_data.xy.x = arguments[1];
    event::mouse_data.xy.y = arguments[2];
    event::mouse_data.move = event::mouse_data.oldxy != event::mouse_data.xy;

    event::mouse_data.dxy = {event::mouse_data.xy.x-event::mouse_data.oldxy.x, event::mouse_data.xy.y-event::mouse_data.oldxy.y};

    event::mouse_data.oldxy = event::mouse_data.xy;
    ed.data.mev = event::mouse_data; ///< copy mouse state to the event data.
    return ed.event_type;
}

/**
 * @brief Not used yet. Don't think I will need it.
 *
 * @param _args
 * @return event::type
 */
event::type event::conio_parser::parse_caret_report(std::vector<int> _args)
{
    return event::type::DROP;
}


/**
 * @brief Quick render to report the actual mouse state in a std::string
 *
 * @return std::string
 */
std::string mouse::to_string()
{
    tuxin::string output{};
    output | color::grey100 | "[" | color::yellow | xy | color::grey100 | "] ";
    output | color::grey100 | (button.left   ? color::render(color::lime) : color::render(color::grey66)) | "left ";
    output | color::grey100 | (button.middle ? color::render(color::lime) : color::render(color::grey66)) | "middle ";
    output | color::grey100 | (button.right  ? color::render(color::lime) : color::render(color::grey66)) | "right";
    output | color::grey100 | " move[" | color::yellow | (move ? "yes" : "no") | color::grey100 | "] ";
    output | color::grey100 | " delta[" | color::yellow | dxy | color::grey100 | "] ";
    return output;
}


/**
 * @brief

 * @note Not used or usable yet. Code and functionnality from the Arthur Sonzogni's FTXUI project:
 *       https://github.com/ArthurSonzogni/FTXUI
 *
 * @param ev
 * @return event::type
 */
event::type event::conio_parser::parse_utf8(event& ev)
{
    auto head = *it;
    unsigned char selector = 0b1000'0000;  // NOLINT

    // The non code-point part of the first byte.
    unsigned char mask = selector;

    // Find the first zero in the first byte.
    unsigned int first_zero = 8;            // NOLINT
    for (unsigned int i = 0; i < 8; ++i) {  // NOLINT
        mask |= selector;
        if (!(head & selector)) {
            first_zero = i;
            break;
        }
        selector >>= 1U;
    }

    // Accumulate the value of the first byte.
    auto value = uint32_t(head & ~mask);  // NOLINT

    // Invalid UTF8, with more than 5 bytes.
    const unsigned int max_utf8_bytes = 5;
    if (first_zero == 1 || first_zero >= max_utf8_bytes) {
        ev.event_type = event::type::DROP;
        return event::type::DROP;
    }

    // Multi byte UTF-8.
    for (unsigned int i = 2; i <= first_zero; ++i) {
        if (!eat()) {
            ev.event_type = event::type::UNCOMPLETED;
            return event::type::UNCOMPLETED;
        }

        // Invalid continuation byte.
        head = *it;
        if ((head & 0b1100'0000) != 0b1000'0000) {  // NOLINT
            ev.event_type = event::type::DROP;
            return event::type::DROP;
        }
        value <<= 6;                  // NOLINT
        value += head & 0b0011'1111;  // NOLINT
    }

    // Check for overlong UTF8 encoding.
    int extra_byte = 0;
    if (value <= 0b000'0000'0111'1111) {                 // NOLINT
        extra_byte = 0;                                    // NOLINT
    } else if (value <= 0b000'0111'1111'1111) {          // NOLINT
        extra_byte = 1;                                    // NOLINT
    } else if (value <= 0b1111'1111'1111'1111) {         // NOLINT
        extra_byte = 2;                                    // NOLINT
    } else if (value <= 0b1'0000'1111'1111'1111'1111) {  // NOLINT
        extra_byte = 3;                                    // NOLINT
    } else {
        ev.event_type = event::type::DROP;                                             // NOLINT
        return event::type::DROP;
    }

    if (extra_byte != (it - _seq_.begin())) {
        ev.event_type = event::type::DROP;
        return event::type::DROP;
    }
    ev.event_type = event::type::CHARACTER;
    return event::type::CHARACTER;
}




}// namespace tuxin::ui
