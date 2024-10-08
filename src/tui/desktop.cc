#include "tuxin/tui/desktop.h"




namespace tuxin::ui
{


desktop::desktop(const std::string &prog_id): element(nullptr, prog_id){ /*...*/ }

tuxin::ui::desktop::~desktop(){ book::debug() << book::fn::fun << book::code::notimplemented ;}



book::code tuxin::ui::desktop::setup_ui()
{
    //set_geometry({1,1},ui::size{terminal::geometry()})
    return book::code::notimplemented;
}

book::code tuxin::ui::desktop::draw()
{
    return book::code::notimplemented;
}

book::code tuxin::ui::desktop::redraw()
{
    return book::code::notimplemented;
}

book::code tuxin::ui::desktop::resize(size new_sz)
{
    return book::code::notimplemented;
}


}// namespace tuxin::ui

