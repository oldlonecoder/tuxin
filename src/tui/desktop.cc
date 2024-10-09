#include "tuxin/tui/desktop.h"




namespace tuxin::ui
{


desktop* desktop::_desk{nullptr};


desktop::desktop(const std::string &prog_id): element(nullptr, prog_id)
{
    if(desktop::_desk)
        return;
    _desk = this;
}

tuxin::ui::desktop::~desktop(){ book::debug() << book::fn::fun << book::code::notimplemented ;}



book::code tuxin::ui::desktop::setup_ui()
{
    set_geometry(terminal::geometry());
    _uistyle_ |= globals::uistyle::statusbar;
    if(_uistyle_ & globals::uistyle::statusbar)
    {
        statusbar* stb = new statusbar(this, id()+"|desktop::statusbar");
        stb->set_theme("C128");//_theme_name_);
        stb->set_anchor(globals::anchor::width_fit|globals::anchor::fit_bottom);
        stb->setup_ui();
        stb->emplace();
    }

    return book::code::done;
}

book::code tuxin::ui::desktop::draw()
{
    return element::draw();
}

book::code tuxin::ui::desktop::redraw()
{
    return element::redraw();
}

book::code tuxin::ui::desktop::resize(size new_sz)
{
    return element::resize(new_sz);
}

desktop *desktop::instance()
{
    return desktop::_desk;
}

statusbar *desktop::statusbar_element()
{
    return _status_bar_;
}


}// namespace tuxin::ui

