
#include "tuxin/tui/input_track.h"



namespace tuxin::ui
{

intrack::intrack():element(){}

intrack::intrack(element* _parent, const std::string& a_id): element(_parent, a_id){}



/**
 * @brief refresh the ui with the new event data.
 *
 * @param e Reference to the event data.
 * @param _painter  -- Uses external painter instance to avoid abuse of local painter contructor-destructor calls, which floods the book's memory
 * @return book::code
 */
book::code intrack::update_event_data(const event& e)
{
    ev = e;

    if((ev.event_type == event::type::key_command) || (ev.event_type == event::type::CHARACTER))
    {
        if(ev.event_type == event::type::key_command)
        {
            _keyevent_painter_.clear() << color::yellow << std::format("{:>20s}",e.data.kev.description) << book::action::commit;
            //_keyevent_painter_ << color::yellow << std::format("{:>20s}",e.data.kev.description);
            return book::code::accepted;
        }
        else
        {
            if(ev.event_type == event::type::CHARACTER)
            {
                _keyevent_painter_.clear() << color::yellow << std::format("{:>20c}",e.data.kev.code) << book::action::commit;
                return book::code::accepted;
            }
            return book::code::undefined;
        }
    }
    if(ev.event_type != event::type::MOUSE)
    {
        book::message( ) << book::fn::fun << " triggering " << book::code::rejected << " for unhandled event data.";
        //book::out() << "seq: " << color::yellow << tuxin::string::bytes(e.)
        return book::code::rejected;
    }
    _mouseevent_painter_.clear() << color::reset << "["
    << color::orangered1 << std::format("{:>3d}", e.data.mev.xy.x)
    << color::reset << ','
    << color::orangered1 << std::format("{:<3d}",e.data.mev.xy.y)
    << color::reset << "]"
    << (e.data.mev.button.left   ? color::lightyellow3 : color::reset)  << (e.data.mev.button.left    ?'L' : 'l') << color::reset << "|"
    << (e.data.mev.button.middle ? color::lime : color::reset)   << (e.data.mev.button.middle  ?'M' : 'm') << color::reset << "|"
    << (e.data.mev.button.right  ? color::red4 : color::reset)   << (e.data.mev.button.right   ?'R' : 'r') << color::reset << "|"
    << (e.data.mev.move          ? color::yellow : color::reset) << (e.data.mev.move           ?"V" : "v")
    << color::reset << "["
    << color::orangered1 << std::format("{:>3d}",e.data.mev.dxy.x)
    << color::reset << ','
    << color::orangered1 << std::format("{:<3d}",e.data.mev.dxy.y)
    << color::reset << "]"
    << book::action::commit;

    return book::code::done;
}

book::code intrack::setup_ui()
{
    // auto positionning and dimensions.
    using namespace globals;
    set_geometry({{0,0},ui::size{46,1}});
    set_anchor(anchor::fit_right|anchor::fit_bottom);
    _keyevent_painter_ = begin_paint(_key_area_);
    _mouseevent_painter_ = begin_paint(_mouse_area_);
    apply_placement();
    return book::code::done;
}


book::code intrack::draw()
{
    auto painter = begin_paint();
    painter.clear();
    painter << color::reset << "["
    << color::orangered1 << std::format("{:>3d}",event::mouse_data.xy.x)
    << color::reset << ','
    << color::orangered1 << std::format("{:<3d}",event::mouse_data.xy.y)
    << color::reset << "]"
    << (event::mouse_data.button.left   ? color::lightskyblue4 : color::reset)  << (event::mouse_data.button.left    ?'L' : 'l') << color::reset << "|"
    << (event::mouse_data.button.middle ? color::lime : color::reset)   << (event::mouse_data.button.middle  ?'M' : 'm') << color::reset << "|"
    << (event::mouse_data.button.right  ? color::red4 : color::reset)   << (event::mouse_data.button.right   ?'R' : 'r') << color::reset << "|"
    << (event::mouse_data.move          ? color::yellow : color::reset) << (event::mouse_data.move           ?"V" : "v")
    << color::reset << "["
    << color::orangered1 << std::format("{:>3d}",event::mouse_data.dxy.x)
    << color::reset << ','
    << color::orangered1 << std::format("{:<3d}",event::mouse_data.dxy.y)
    << color::reset << "]";
    end_paint(painter);

    return book::code::done;
}
}
