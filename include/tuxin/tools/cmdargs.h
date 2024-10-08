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

#include "tuxin/tools/signals.h"
#include "tuxin/tools/book.h"



namespace tuxin::cmd
{


struct TUXIN_API cmd_switch
{
    using data = std::vector<std::string_view>;
    using array = std::vector<cmd_switch*>;
    using iterator = cmd_switch::array::iterator;

// ----------  ------------------------------------------
    std::string            name;
    std::string            switch_char;
    std::string            switch_text;
    std::string            descriptions;
    int                    required { 0 };
    int                    count    { 0 };
//--------------------------------------------------------


    data                   arguments{};
    bool                   enabled{ false };
    signals::action<cmd_switch&> delegate_call_back;
    bool operator !() { return delegate_call_back.empty(); }

    template<typename T> void connect(T* Obj, book::action (T::*Fn)(cmd_switch&)){
        delegate_call_back.connect(Obj, Fn);
    }
    cmd_switch& set_descriptions(const std::string& Txt);
    cmd_switch& set_char(const std::string& Txt);
    cmd_switch& set_long_switch(const std::string& Txt);
    cmd_switch& set_required(int N);

    ~cmd_switch();
};


class TUXIN_API line
{

    cmd_switch::array arguments;
    cmd_switch defaults;

    cmd_switch::iterator A{};
public:
    line() = default;
    ~line();

    template<typename T> void set_default_callback(T* Obj, book::code (T::*Fn)(cmd_switch&))
    {
        (void)defaults.delegate_call_back.connect(Obj, Fn);
    }

    cmd_switch::iterator query(std::string_view cmd_switch);
    cmd_switch& operator<<(const cmd_switch& Arg);
    cmd_switch& operator [] (const std::string& ArgName);
    //Book::Enums::Code InputCmdLineData(int argc, char** argv);
    book::code input(const std::vector<std::string_view>& StrArray);
    cmd_switch& add_cmd(const std::string& cId);
    book::action process();
    bool empty() { return arguments.empty(); }
    std::string usage();
};

}