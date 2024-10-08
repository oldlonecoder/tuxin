


#include "tuxin/tui/window.h"
#include "tuxin/tui/globals.h"

namespace tuxin::ui 
{

window::window(const std::string w_id,globals::uistyle::Type u_style) : element(nullptr, w_id)
{
    _uistyle_ = u_style;
}


window::~window()
{
    book::info() << book::fn::fun;
}


book::code window::setup_ui()
{
    return book::code::notimplemented;
}

book::code window::draw()
{
    book::debug() << book::fn::fun;
    return element::draw();

    return book::code::done;
}



book::code window::redraw(){return element::redraw();}

book::code window::resize(size new_sz)
{
    return element::resize(new_sz); // do nothing for now.
}





}
