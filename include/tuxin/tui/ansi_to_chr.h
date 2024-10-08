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

#include "tuxin/tools/string.h"
#include "tuxin/tui/twindc.h"

namespace tuxin::ui
{

class TUXIN_API ansi_to_chr
{
    tuxin::string _text_data_{};
public:
    ansi_to_chr();
    ansi_to_chr(tuxin::string data);
    ~ansi_to_chr();

    twindc render();


};

} // namespace tuxin::ui


