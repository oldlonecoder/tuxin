//
// Created by oldlonecoder on 8/21/24.
//

//#ifndef BOOK_H
//#define BOOK_H
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

#include "tuxin/tools/glyphes.h"
#include "tuxin/tools/string.h"
//#include "intui/book/enums.h"
#include <source_location>

#include <functional>
#include "tuxin/tools/geometry.h"
#include <filesystem>
#include <fstream>



using tuxin::color;
using tuxin::glyph;
using tuxin::accent_fr;
using tuxin::ui::rectangle;
using tuxin::ui::cxy;
using tuxin::ui::size;

class TUXIN_API book
{
public:
    struct header_component
    {
         integers::U8 type  : 1;
         integers::U8 stamp : 1;
         integers::U8 fun  : 1;
         integers::U8 file  : 1;
         integers::U8 line  : 1;
         integers::U8 col   : 1;
       //...
    };


    enum class type : integers::U8{
        none, err, warning, fatal, except, message, output, debug, info, comment, syntax, status, test, interrupted, aborted, segfault, log
    };



    enum class code : integers::U8
    {
        ok  =0           , ///< Obviously;
        accepted         ,
        success          ,
        rejected         ,
        failed           ,
        empty            ,
        full             ,
        notempty         ,
        implemented      , ///< Like notimplemented or already implemented
        notimplemented   , ///< "Please, implement"
        untested         ,
        eof              , ///< End of file
        eos              , ///< End of stream or string or statement or Status ( machine Status )
        null_ptr         , ///< It will happen. Trust me :)
        notexist         , ///< does not exist
        exist            , ///< does already exist
        unexpected       , ///< unexpected
        expected         , ///< expected
        blocked          , ///< thread trying To lock A mutex has failed because the mutex is already locked IsIn another thread...
        locked           , ///< thread trying To lock A mutex has became the owner of the lock.
        overflow         , ///< buffer overflow
        oob              , ///< buffer overflow
        reimplement      ,
        done             ,
        complete         ,
        finish           ,
        undefined        ,
        ready            ,
        terminate        ,
        timeout          ,
        divbyzero        ,
        notvisible       ,
        cancel           ,

        //...

    };


    enum class fn : integers::U8
    {
        fun             ,
        endl             , ///< End of line Code, input format
        file             ,
        line             ,
        stamp            , ///< fully detailed timestamp
        hour             ,
        minute           ,
        seconds          ,
        weekday          ,
        dayname          ,
        month            , ///< Par defaut month name
        day              ,
        monthnum         , ///< Maintenant explicite
        year
    };

    enum class action : integers::U8
    {
        enter            , ///< enter bloc or indent
        leave            , ///< End (logger: End of entry accumulators, so do commit); End of (sel)Section, STMLAttribute ( auto- color::Reset ) and unindent
        commit           , ///< Commit...
        begin            , ///< Begin (sel)Section or augment indent level
        end              , ///< End   Loop/Action or End selection or Unindent one level
        continu          , ///< Continue Loop or continue Signals::Action iteration.
    };


    static std::string TUXIN_API to_string(book::type enum_type);
    static std::string TUXIN_API to_string(book::code enum_code);
    static std::string TUXIN_API to_string(book::fn   enum_fn);
    static std::string TUXIN_API to_string(book::action enum_action);

    static std::pair<glyph::type, color::pair> TUXIN_API type_attributes         (book::type enum_type);
    static std::pair<glyph::type, color::pair> TUXIN_API return_code_attributes  (book::code enum_code);
    static std::pair<glyph::type, color::pair> TUXIN_API function_attributes     (book::fn enum_fn);
    static std::pair<glyph::type, color::pair> TUXIN_API action_attributes       (book::action enum_action);








private:
    book::type _type_{};
    book::code _code_{};
    std::source_location location{};
    // ---------------------------------
    tuxin::string  text{};

    header_component _headercomp_{1,0,1,1,1};
public:


    struct TUXIN_API logentry
    {
        tuxin::string _text_{};
        using logs = std::vector<book::logentry>;
        logentry(book::type, std::source_location src = std::source_location::current()){};
        logentry();
        ~logentry() { _text_.clear(); }

        book::logentry& error       (std::source_location src = std::source_location::current());
        book::logentry& warning     (std::source_location src = std::source_location::current());
        book::logentry& fatal       (std::source_location src = std::source_location::current());
        book::logentry& except      (std::source_location src = std::source_location::current());
        book::logentry& message     (std::source_location src = std::source_location::current());
        book::logentry& out         (std::source_location src = std::source_location::current());
        book::logentry& debug       (std::source_location src = std::source_location::current());
        book::logentry& info        (std::source_location src = std::source_location::current());
        book::logentry& comment     (std::source_location src = std::source_location::current());
        book::logentry& syntax      (std::source_location src = std::source_location::current());
        book::logentry& status      (std::source_location src = std::source_location::current());
        book::logentry& test        (std::source_location src = std::source_location::current());
        book::logentry& interrupted (std::source_location src = std::source_location::current());
        book::logentry& aborted     (std::source_location src = std::source_location::current());
        book::logentry& segfault    (std::source_location src = std::source_location::current());
        book::logentry& log         (std::source_location src = std::source_location::current());

        book::logentry& operator << (const std::string& txt);
        book::logentry& operator << (const char* txt);
        book::logentry& operator << (char ch);
        book::logentry& operator << (std::string_view txt);
        book::logentry& operator << (const rectangle& r);
        book::logentry& operator << (cxy pt);
        book::logentry& operator << (color::code col);
        book::logentry& operator << (color::pair fgbg);
        book::logentry& operator << (glyph::type gh);
        book::logentry& operator << (accent_fr::type ac);
        book::logentry& operator << (book::type ty);
        book::logentry& operator << (book::code cod);
        book::logentry& operator << (book::fn fn);
        book::logentry& operator << (book::action a_action);
        template<typename T> book::logentry& operator << (const T& v)
        {
            _text_ << v;
            return *this;
        }
        //...

    };

    static book& error       (std::source_location src = std::source_location::current());
    static book& warning     (std::source_location src = std::source_location::current());
    static book& fatal       (std::source_location src = std::source_location::current());
    static book& except      (std::source_location src = std::source_location::current());
    static book& message     (std::source_location src = std::source_location::current());
    static book& out         (std::source_location src = std::source_location::current());
    static book& debug       (std::source_location src = std::source_location::current());
    static book& info        (std::source_location src = std::source_location::current());
    static book& comment     (std::source_location src = std::source_location::current());
    static book& syntax      (std::source_location src = std::source_location::current());
    static book& status      (std::source_location src = std::source_location::current());
    static book& test        (std::source_location src = std::source_location::current());
    static book& interrupted (std::source_location src = std::source_location::current());
    static book& aborted     (std::source_location src = std::source_location::current());
    static book& segfault    (std::source_location src = std::source_location::current());
    static book& log         (std::source_location src = std::source_location::current());

    book& operator << (const std::string& txt);
    book& operator << (const char* txt);
    book& operator << (char ch);
    book& operator << (std::string_view txt);
    book& operator << (const rectangle& r);
    book& operator << (cxy pt);
    book& operator << (color::code col);
    book& operator << (color::pair fgbg);
    book& operator << (glyph::type gh);
    book& operator << (accent_fr::type ac);
    book& operator << (book::type ty);
    book& operator << (book::code cod);
    book& operator << (book::fn fn);
    book& operator << (book::action a_action);
    template<typename T> book& operator << (const T& v)
    {
        text << v;
        return *this;
    }

    static std::vector<book> _mem_stream_;
    void init_header();
    static void purge(const std::function<void(book &)>& f);

    struct TUXIN_API section
    {
        std::string id;   ///< Section ID which is also the base name of the output file.
        std::fstream* fout{nullptr}; ///< will see.
        std::vector<book> contents{}; ///< Actual contents. Will be transfered into the entries container when the transition is done.
        std::vector<book::logentry> entries{}; ///< in transition.

        using list = std::vector<book::section>;
        book::section& operator *(); ///< Get the reference of this instance.
        book& operator << (book&& r); // move operator, will be removed and replaced with book::logentry object.
    };


    static book::section::list sections;
    static book::section::list::iterator current_section;
public:
    static book::section& select(const std::string& section_id);
    static book::code init(std::function<book::code()> inifn = nullptr);
    static book::code append_section(const std::string& section_id);

    class TUXIN_API exception :  public std::exception
    {
    public:

        explicit exception():std::exception() { _e_ = true; }
        explicit exception(const char *txt) { _msg_ = txt; _e_ = false; }
        explicit exception(const std::string &txt) { _msg_ = txt; _e_ = false; }

        ~exception() noexcept override {
            _msg_.clear();
        }

        const char* what() const noexcept override;

        book::exception operator[](book& el);
    private:
        bool _e_;
        mutable std::string _msg_;
        book *_book_instance_{nullptr};
    };

    book() = default;
    book(book::type message, book::code code, std::source_location src);
};

 bool operator !(book::code enum_code);

//#endif //BOOK_H
