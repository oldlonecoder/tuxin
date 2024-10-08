#include "tuxin/tui/element.h"
#include "tuxin/tools/colors.h"
#include <cctype>


namespace tuxin::ui
{

#define RR color::reset

//----------------------------------------------------------------------------------------------------------------------
#pragma region painter

element::painter::painter(element* _parent, rectangle _rect): _parent_(_parent), _rect_{_rect}
{
    if(!_rect_)
        _rect_ = _parent_->_windc_._rect_.tolocal();
    else
        _rect_ =  _parent_->_windc_._rect_.tolocal() & _rect_;
    _colors_ = _parent_->_colors_;

    book::debug() << book::fn::fun << "geometry: " << _rect_;
}


element::painter::~painter()
{
    book::info() << book::fn::fun << "  -> @" << color::blueviolet << this << RR;
}


book::code element::painter::set_geometry(rectangle _area)
{
    rectangle tmp = _parent_->_windc_._rect_.tolocal() & _area;
    if(!tmp)
        return book::code::rejected;

    _rect_ = tmp;
    home();
    return book::code::accepted;
}

element::painter& element::painter::operator << (book::action action)
{
    switch ( action )
    {
        case book::action::commit:
            _parent_->end_paint(*this);
            return *this;
        default:
            return *this;
    }
}

element::painter& element::painter::home()
{
    _rect_.home();
    _c_ = _parent_->_windc_.cursor(_rect_.cursor + _rect_.a);
    //book::debug() << book::fn::fun << "@_c_=" << color::blueviolet << _c_ << RR;
    return *this;
}


/**
 * @brief clears given or the entirety of the painting area.
 *
 * @param _rect warning if _rect is out of boundaries.
 * @return element::painter&
 */
element::painter& element::painter::clear(rectangle _rect)
{
    if(!_rect)
        _rect = _rect_;
    else
        _rect = _rect_ & _rect;
    if(!_rect)
    {
        book::warning() << book::fn::fun << " clear geometry request :" << color::red4 << _rect.tostring() << color::reset << ':' << book::code::oob;
        return *this;
    }
    book::debug() << book::fn::fun << _parent_->id() << ": call parent_dc's twindc::clear(" << color::yellow << _rect << color::reset << "):";
    _parent_->_windc_.clear(_parent_->_colors_, _rect);
    home();
    return  *this;
}


element::painter& element::painter::to(const cxy& xy)
{
    if(!_rect_[_rect_.a+xy])
        throw book::exception() [ book::except() << book::fn::fun << book::code::oob << color::red4 << xy << color::reset << "."];

    _rect_.goto_xy(xy);

    _c_ = _parent_->_windc_.cursor(_rect_.cursor + _rect_.a);
    //book::debug() << book::fn::fun << "@_c_=" << color::blueviolet << _c_ << color::reset;
    return *this;
}


element::painter& element::painter::draw_frame(rectangle _rect, cadre::frame_matrix _modelmtx)
{
    cadre box;
    box = _modelmtx;
    if(!_rect)
        _rect=_rect_.tolocal();

    //book::debug() <<  book::fn::fun << "Check box[cadre::TopLeft]: '" << color::yellow << box[cadre::TopLeft] << color::reset << "'";
    to({_rect.a}) << cadre::TopLeft << top_right() << cadre::TopRight << bottom_right() << cadre::BottomRight << bottom_left() << cadre::BottomLeft;

    for(int y =1;y < *_rect.height()-1; y++)
        to(top_left() + cxy{0,y}) << cadre::Vertical << top_right() + cxy{0,y} << cadre::Vertical;
    for(int x =1;x < *_rect.width()-1; x++)
        to(top_left() + cxy{x,0}) << cadre::Horizontal << bottom_left() + cxy{x,0} << cadre::Horizontal;
    return *this;
}


element::painter& element::painter::draw_frame(rectangle _rect)
{
    return draw_frame(_rect, _model_);
}



element::painter& element::painter::operator << (cadre::index fr)
{
    if(_rect_.cursor.x >= _rect_.dwh.w)
    {
        book::warning() << book::fn::fun << "cursor is past last column...";
        return *this;
    }
    **_c_ << _colors_ << fr;
    ++_rect_; ++_c_;
    return *this;
}


element::painter& element::painter::operator << (std::string_view _str)
{
    return (*this) << (_str.data());
}

element::painter& element::painter::operator << (char _c)
{

    // if((_rect_.cursor.x >= _rect_.dwh.w) && nowrap)
    if(_rect_.cursor.x >= _rect_.dwh.w)
    {
        book::warning() << book::fn::fun << "cursor is past last column";
        book::out() << "area:" << color::yellow << _rect_;
        return *this;
    }

    _c_->set_colors(_colors_) << _c;
    ++_rect_; ++_c_;
    //_c_ = _parent_->_windc_.cursor(_rect_.cursor+_rect_.a);
    return *this;
}


element::painter& element::painter::operator << (const char* _c)
{
    auto width = std::strlen(_c);
    // if nowrap:
    //width = std::min(static_cast<size_t>(_rect_.dwh.w-_rect_.cursor.x), width);
    // else ...
    auto it = _c;
    do
    {
        _c_->set_colors(_colors_) << *it++;
        ++_rect_; ++_c_;
    }while(*it);
    //_c_ = _parent_->_windc_.cursor(_rect_.cursor+_rect_.a);
    return *this;
}


element::painter& element::painter::operator << (const twindc::chr::string& _str)
{
    auto width = _str.size();
    std::size_t w2 = _rect_.dwh.w-_rect_.cursor.x;
    book::debug() << book::fn::fun << "width from cursor :" << color::yellow << w2;
    // if nowrap:
    width = std::min(w2, width);
    // else ...
    auto it = _str.begin();
    do
    {
        (*_c_) << _colors_ << *it;
        ++_rect_; ++ _c_; it++;
    }while(it != _str.end());
    //_c_ = _parent_->_windc_.cursor(_rect_.cursor+_rect_.a);
    return *this;
}




bool element::painter::is_plain(const std::string& str)
{
    bool plain{false};
    for(auto c :str) if(!std::isprint(c)) return false;
    return plain;
}

/**
 * @brief Outputs into the bloc the given plain text.
 *
 * @param _str plain unformatted text
    @note Any non-printable char will make the method to be wrongly render the size greater then expected.
 * @return element::painter&
 */
element::painter& element::painter::operator << (const std::string& _str)
{
    return *this << _str.c_str();
}


element::painter& element::painter::operator << (color::pair _cp)
{
    if(_cp.fg == color::reset) _cp.fg = _parent_->_colors_.fg;
    if(_cp.bg == color::reset) _cp.bg = _parent_->_colors_.bg;
    _colors_ = _cp;
    **_c_ << _colors_;
    return *this;
}


element::painter& element::painter::operator << (color::code _fg)
{
    if(_fg == color::reset)
        _fg = _parent_->_colors_.fg;

    _colors_.fg = _fg;
    _c_->set_fg(_fg);
    return *this;
}

element::painter& element::painter::set_background(color::code _bg)
{
    if(_bg == color::reset)
        _bg = _parent_->_colors_.bg;

    _colors_.bg = _bg;
    _c_->set_bg(_bg);
    return *this;
}


element::painter& element::painter::set_foreground(color::code _fg)
{
    if(_fg == color::reset)
        _fg = _parent_->_colors_.bg;

    _colors_.fg = _fg;
    _c_->set_fg(_fg);
    return *this;
}



element::painter& element::painter::operator << (const cxy& xy)
{
    to(xy);
    return *this;
}


#pragma endregion painter
} // namespace tuxin::ui
