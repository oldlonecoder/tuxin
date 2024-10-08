#include "tuxin/tui/statusbar.h"

namespace tuxin::ui
{


statusbar::statusbar(element *_parent, const std::string &a_id): element(_parent, a_id)
{
    _anchor_ = globals::anchor::width_fit|globals::anchor::fit_bottom;
}



book::code statusbar::setup_ui()
{
    set_geometry({{0,0},ui::size{1,1}});
    apply_placement();
    book::log() << book::fn::fun << color::yellow << id() << "'s geometry: " << geometry();
    return book::code::notimplemented;
}

// book::code statusbar::draw()
// {
//     return element::draw();
//     //return book::code::notimplemented;
// }

// book::code statusbar::redraw()
// {
//     return element::redraw();
// }

// book::code statusbar::resize(size new_sz)
// {
//     return book::code::notimplemented;
// }

// book::code statusbar::parent_resized()
// {
//     return book::code::notimplemented;
// }

// void statusbar::dirty(painter &_painter)
// {

// }

// book::code statusbar::apply_placement()
// {

//     return book::code::notimplemented;
// }

} // namespace tuxin::ui
