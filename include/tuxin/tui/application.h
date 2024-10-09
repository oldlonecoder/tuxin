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


#include "tuxin/tui/events.h"
#include "csignal"
#include <memory>
#include "tuxin/tools/cadres.h"
#include "tuxin/tui/desktop.h"

namespace tuxin::ui
{

class TUXIN_API application
{
    //OBJECT_REFLECT(application)

    static void sig_interrupted(int);
    static void sig_aborted(int);
    static void sig_crash(int);
    static void sig_winch(int);

    std::vector<std::string_view> _args_{};
    std::string _app_name_{};
    static application* _app_;

public:
    application() = delete;
    virtual ~application();
    application(const std::string& app_name, int argc, char **argv);

    virtual book::code run(){ return book::code::notimplemented;}
    virtual book::code terminate();


    static application& app();
    static desktop* screen_desktop();



protected:
    virtual book::code setup();
    virtual book::code setup_ui(){ return book::code::reimplement; }
    virtual book::code install_signals();


};



}
