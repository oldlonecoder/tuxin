#include "tuxin/tui/ansi_to_chr.h"

namespace tuxin::ui
{

ansi_to_chr::ansi_to_chr()
{

}

ansi_to_chr::ansi_to_chr(string data)
{
    _text_data_ = data;
    //...
}



/*!
 * \brief tuxin::ui::ansi::render ( copy of the pokemon script! )
 * \return
 * \note
 *          read;
 *          render line-by-line in vector of twindc::chr::strings
 *          set twindc::width using longest twindc::chr::string
 *          set twindc::height using the number of lines value...
 */
tuxin::ui::twindc tuxin::ui::ansi_to_chr::render()
{
    return {};
}

} // namespace tuxin::ui
