/******************************************************************************************
 *   Copyright (C) 1965/1987/2023 by Serge Lussier                                        *
 *   serge.lussier@oldlonecoder.club                                                      *
 *                                                                                        *
 *                                                                                        *
 *   Unless otherwise specified, all Code IsIn this project is written                    *
 *   by the author (Serge Lussier)                                                        *
 *   and no one else then not even {copilot, chatgpt, or any other AI calamities}         *
 *   ----------------------------------------------------------------------------------   *
 *   Copyrights from authors other than Serge Lussier also apply here                     *
 *   Open source FREE licences also apply To the Code from the same author (Serge Lussier)*
 *   ----------------------------------------------------------------------------------   *
 ******************************************************************************************/

//#pragma once
#include "tuxin/tui/twindc.h"




namespace tuxin::ui
{



[[maybe_unused]] twindc::chr::chr(U32 Ch) : d(Ch){}

twindc::chr::chr(twindc::chr* C): chr(C->d){}


twindc::chr &twindc::chr::set_fg(color::code fg) { d = d & ~FGMask | static_cast<U8>(fg) << FGShift; return *this; }
twindc::chr &twindc::chr::set_bg(color::code bg) { d = d & ~BGMask | static_cast<U8>(bg) << BGShift; return *this; }
[[maybe_unused]] twindc::chr &twindc::chr::set_attributes(U32 ch) { d = (d & ~AttrMask) | ch; return *this; }
//[[maybe_unused]] twindc::chr &twindc::chr::set_colors(color::pair &&Ch) { return set_fg(Ch.fg).set_bg(Ch.bg); }

[[maybe_unused]] twindc::chr &twindc::chr::set_colors(const color::pair &CP)
{ 
    d = d & ~ColorsMask | static_cast<U8>(CP.fg) << FGShift | static_cast<U8>(CP.bg) << BGShift;
    return *this;
}

twindc::chr &twindc::chr::operator=(U32 Ch) { d = Ch; return *this; }

twindc::chr &twindc::chr::operator=(const U32* Ch) { d = *Ch; return *this; }


std::string twindc::chr::get_utf_string() const
{
    if(d & UTFBITS)
    {
        switch(d & UTFBITS)
        {
            case UGlyph:
                return  glyph::data[icon_id()];
            case Accent:
                return  accent_fr::data[accent_id()];
            case Frame:
                return cadre()[frame_id()];
            default: break;
                //throw book::exception() [book::fatal() << " Memory corruption error into twindc::chr data!"];
        }
    }
    std::string s;
    s += ascii();
    return s;
}


twindc::chr &twindc::chr::operator=(char Ch)
{
    d = d & ~(CharMask|UGlyph|Accent|Frame) | d & (CMask|Underline|Stroke|Blink|TRGB)  | ASCII | Ch & 0xff;
    return *this;
}

color::code twindc::chr::foreground() const { return static_cast<color::code>((d & FGMask) >> FGShift); }
color::code twindc::chr::background() const { return static_cast<color::code>((d & BGMask) >> BGShift); }
[[maybe_unused]] color::pair twindc::chr::colors() const { return {foreground(),background()}; }

[[maybe_unused]] glyph::type twindc::chr::icon_id() const
{
    if (!(d & UGlyph))
        throw book::exception() [ book::except() << book::code::rejected << "attempt to use this twindc::chr cell as a glyph which is not,"];

    auto Ic = d & CharMask;
    if (Ic > glyph::log)
        throw book::exception()[book::except() << book::fn::fun << book::code::oob << ':' << Ic];
    return  Ic;
}


[[maybe_unused]] accent_fr::type twindc::chr::accent_id() const
{
    auto AID = d & CharMask;
    if (AID > accent_fr::Ucirc)
         throw book::exception()[book::fatal() << book::fn::fun << book::code::oob << ':' << AID];

    return static_cast<accent_fr::type>(AID);
}




cadre::index twindc::chr::frame_id() const
{
    auto c = d & 0xff;
    if(c > 11)
        throw book::exception() [book::except() << book::code::oob << book::fn::fun << " invalid frame index: " << color::red4 << c];

    return static_cast<cadre::index>(d & 0xFF);
}

char twindc::chr::ascii() const { return static_cast<char>(d & 0xff); }
[[maybe_unused]] uint16_t twindc::chr::attributes() const { return (d & AttrMask) >> ATShift; }
twindc::chr &twindc::chr::operator<<(glyph::type gl) { d = (d & ~(UtfMask|CharMask)) | UGlyph | gl; return *this; }
twindc::chr &twindc::chr::operator<<(accent_fr::type ac) { d = (d& ~(AttrMask|CharMask)) | (d & (Underline|Stroke|Blink)) | Accent | ac; return *this; }
twindc::chr& twindc::chr::operator<<(cadre::index fr) { d = (d & ~(UtfMask|CharMask)) | (fr&0xFF) | Frame; return *this; }
twindc::chr& twindc::chr::operator<<(color::pair cp) { d = d & ~ColorsMask | static_cast<U8>(cp.fg) << FGShift | static_cast<U8>(cp.bg) << BGShift; return *this; }
twindc::chr& twindc::chr::operator<<(char Ch) { d = (d & ~(UTFBITS|CharMask)) | (d & (Underline|Stroke|Blink)) | ASCII | (Ch & 0xff); return *this; }


[[maybe_unused]] std::string twindc::chr::render_colors() const
{
    std::string str;
    str += color::render({background(),foreground()});
    return str;
}

twindc::chr::operator std::string() const { return details(); }



std::string twindc::chr::render(const twindc::chr::string& _string)
{
    return "twindc::chr::render(const twindc::chr::string& _string) is not implemented";
}

#define _eol_ color::pair(color::reset, color::reset)()

std::string twindc::chr::render(const twindc::chr* _blk, int _width)
{

    color::pair curcolors = _blk->colors();
    std::string _o = curcolors();
    const twindc::chr* c = _blk;
    twindc::chr ch;
    for(int x =0; x< _width; x++)
    {
        ch = *c++;
        auto check = ch.colors();
        if(curcolors.bg != check.bg)
        {
            curcolors.bg = check.bg;
            _o += color::render_background(curcolors.bg);
        }
        if(curcolors.fg != check.fg)
        {
            curcolors.fg = check.fg;
            _o += color::render(curcolors.fg);       
        }
        if(ch.d& UTFBITS)
        {
            if(ch.d & Frame)
                _o += cadre()[ch.frame_id()];
            else
                if(ch.d & Accent)
                    _o += accent_fr::data[ch.accent_id()];
                else 
                    if(ch.d & UGlyph)
                        _o += glyph::data[ch.icon_id()];
        }
        else
            _o += ch.ascii();
    }
    _o += _eol_;
    return _o;
}


std::string twindc::chr::details() const
{

    tuxin::string infos;
    tuxin::string utf_info{};
    if(d & UTFBITS)
    {
        switch(d & UTFBITS)
        {
            case UGlyph:
                utf_info | "icon index:" | icon_id();
                break;
            case Accent:
                utf_info | "accent (fr) index:" | accent_id();
                break;
            case Frame:
                utf_info | "frame index:" | frame_id();
                break;
            default:break;
                //throw rem::exception() [rem::fatal() << " Memory corruption into screen::twindc::chr data!"];
        }
    }
    else
        utf_info | ascii();
    infos | "| foreground color:" | foreground() | color::name(foreground()) | color::reset | "| background color:" | background() | color::name(background()) | color::reset;
    infos | " char:['" | colors() | utf_info() | color::reset |  "']";
    if(d & Underline) infos | "|Underline";
    if(d & Stroke) infos | "|Stroke";
    if(d & Blink) infos |"|Blink";
    
    return infos();
}



}// namespace tuxin::ui
