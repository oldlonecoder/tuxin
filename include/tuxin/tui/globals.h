
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

#include "tuxin/tools/book.h"
#include <csignal>
#include <map>
#include <vector>
#include <string_view>


using namespace integers;

namespace tuxin::globals
{


/**
 * @brief Widget ui justification enums or'ed flags
 * @author &copy; 2008,2022,2023, Serge Lussier, lussier.serge@gmail.com ( oldlonecoder )
 */
namespace justify
{
using Type = U8;
static constexpr U8 left = 0x01;
static constexpr U8 right = 0x02;
static constexpr U8 hcenter = 0x04;
static constexpr U8 vcenter = 0x08;
static constexpr U8 center = 0x0C;
static constexpr U8 word_wrap = 0x10;
static constexpr U8 prefix = 0x20;
static constexpr U8 suffix = 0x40;
static constexpr U8 auto_stretch = 0x80;
}


/**
 * @brief Ditux::Rectangleion enums values
 * @author &copy; 2008,2022,2023, Serge Lussier, lussier.serge@gmail.com ( oldlonecoder )
 */
namespace direction
{
using type = I8;
static constexpr I8 left = -1;
static constexpr I8 right = 1;
static constexpr I8 up = 2;
static constexpr I8 down = -2;
}

/**
 * @brief Widget ui class or'ed flags enums
 * @author &copy; 2008,2022,2023, Serge Lussier, lussier.serge@gmail.com ( oldlonecoder )
 */
namespace wflags
{
using Type = U16;
static constexpr Type Unset = 0x0000;
static constexpr Type TopLevel = 0x0001;
static constexpr Type Floating = 0x0002;
static constexpr Type Child = 0x0004;
static constexpr Type Parent = 0x0008;
//...
}


namespace uistyle
{
using Type = U16;
static constexpr Type Frame     = 0x0001;
static constexpr Type Caption   = 0x0002;
static constexpr Type Input     = 0x0040;
static constexpr Type MultiLine = 0x0080;
static constexpr Type Glyph     = 0x0100;
}
/**
 * @brief Widget ui state enums or'ed flags
 * @author &copy; 2008,2022,2023, Serge Lussier, lussier.serge@gmail.com ( oldlonecoder )
 */
namespace wstate
{
using Type = U16;
static constexpr Type Normal = 0x00;
static constexpr Type Disable = 0x01;
static constexpr Type Active = 0x02;
static constexpr Type Focus = 0x04;
static constexpr Type Error = 0x08;
static constexpr Type Warning = 0x10;
static constexpr Type Illegal = 0x20;
static constexpr Type Invalid = 0x40;
static constexpr Type Visible = 0x80;
static constexpr Type Success = 0x100;
static constexpr Type Done = 0x200;
static constexpr Type Ditry = 0x400;
}


/**
 * geometry policies for stretching and positionning children widgets
 */
namespace anchor
{
using value = U16;
static constexpr anchor::value fixed        = 0x0000; ///< free fixed xy placement
static constexpr anchor::value width_fit    = 0x0001; ///< Fits the entire width size
static constexpr anchor::value height_fit   = 0x0002; ///< Fits the entire height size
static constexpr anchor::value onframe_fit  = 0x0004; ///< Overlaps if wh size > 1, or sits on the frame.
static constexpr anchor::value fit_right    = 0x0008;
static constexpr anchor::value fit_left     = 0x0010;
static constexpr anchor::value fit_top      = 0x0020;
static constexpr anchor::value fit_bottom   = 0x0040;
static constexpr anchor::value fit_center   = 0x0080; ///< Both fit_h&vcenter ...
static constexpr anchor::value fit_hcenter  = 0x0100;
static constexpr anchor::value fit_vcenter  = 0x0200;

//...
}

namespace colors
{

struct attr_db
{
    using components = std::map<wstate::Type,   color::pair>;
    using elements = std::map<std::string_view, attr_db::components>;
    using themes = std::map<std::string_view,   attr_db::elements>;
    //using theme     = std::map<std::string_view, db::dictionary>;
    static colors::attr_db::themes s_data;
    
    static attr_db::themes::iterator get_theme(std::string_view theme_name);
    static bool end(attr_db::themes::iterator it);
    //static attr_db::components& components_table(attr_db::themes::iterator i);
    static themes& theme();
};
} // namespace colors;






} // lus::intui::globals

