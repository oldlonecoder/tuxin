

#include "tuxin/tui/twindc.h"
#include "tuxin/tui/terminal.h"

//#include <memory>
//#include <ostream>



namespace tuxin::ui
{

twindc::twindc(twindc& _parent_win): _blk_(_parent_win._blk_), _parent_dc_(&_parent_win){}


/*!
 * @brief set this twindc geometry
 * @param _rect
 * @return
 */
book::code twindc::set_geometry(const rectangle& _rect)
{
    book::debug() << book::fn::fun << "request geometry:" << color::orangered1 << _rect.tostring() << color::reset;
    _rect_ = _rect;


    if(_parent_dc_ != nullptr && _blk_ != nullptr)
     {
        book::out() << "geometry {" << color::yellow << _rect_ << color::reset << "} is relative to '" << color::lime << _parent_dc_->geometry().tostring() << color::reset;
        return book::code::complete;
     }

    _blk_ = new chr[_rect_.dwh.area()+ *_rect_.width()];
    book::out() << "bloc chr bound to this windc.";

    return book::code::accepted;

}

 twindc::~twindc()
 {
        book::info() << book::fn::fun << color::yellow << color::reset << "  -> @" << color::blueviolet << this << color::reset;


    if(!_parent_dc_)
    {
        book::out() << color::orangered1 << " destroying owned chr bloc:" << color::reset;
        delete [] _blk_;
    }
    else
        book::out() << color::lime << " not owned chr bloc" << color::reset;

 }


book::code twindc::clear(const color::pair& _cp, rectangle _rect)
{
    if(!_rect) _rect = _rect_.tolocal();
    else
    {
        _rect = _rect_.tolocal() & _rect;
        //book::debug() << book::fn::fun << "clippped: " << color::yellow << _rect << color::reset;
        if(!_rect)
            return book::code::rejected;
    }

    //book::debug() << book::fn::fun << color::orangered1 << _rect_ << color::reset;
    //book::out() << "clear area:" << color::yellow << _rect << color::reset;
    if(_parent_dc_ == nullptr)
    {
        // Entirety of our dimensions ? :

        if(_rect == _rect_.tolocal())
        {
            //  book::out() << " Entirety of the geometry:(request rect: "
            //  << color::lime << _rect << color::reset
            //  << " <-> geometry: " << color::yellow
            //  << _rect_.tolocal() << color::reset << ")";

            auto *p = _blk_;
            for(int i = 0; i < _rect_.dwh.area(); i++)
                (*p++) << _cp << ' ';

            return book::code::accepted;
        }
    }
//    book::out() << "Sub Region" << color::yellow << _rect << color::reset;
    chr clear_cell;
    clear_cell << _cp << ' ';
    for(int y=0; y<_rect.dwh.h; y++)
    {

        cursor(_rect.a + cxy{0,y});
        for(int x = 0; x < _rect.dwh.w; x++){ *_cursor_++ = clear_cell; }
    }
    dirty(_rect);

    return book::code::complete;
}

book::code twindc::dirty(rectangle _rect)
{
    _rect = _rect_.tolocal() & _rect;
    if(!_rect)
    {
        book::warning() << book::fn::fun << "rejected dirty: out of boundaries within " << _rect_.tolocal();
        return book::code::rejected;
    }
    if(!_dirty_area_)
        _dirty_area_ = _rect;
    else
        _dirty_area_ = _dirty_area_ | _rect;
//    book::debug() << book::fn::fun << " _dirty_area_: " << color::yellow << _dirty_area_ << color::reset;
    return book::code::accepted;
}

/*!
 * @brief ...
 * @param xy local xy coordinates.
 * @return
 */
twindc::chr* twindc::cursor(const cxy& xy)
{
    //if(!_rect_[xy]) return nullptr;
    if(xy == cxy{-1,-1}) return _cursor_;

    //book::debug() << book::fn::fun << " @" << color::lime << xy << color::reset;
    if(!_rect_.tolocal()[xy])
        throw book::exception()[book::except() << book::fn::fun << " cursor(" << color::red4 << xy << color::reset <<  ")->" << color::lime << _rect_.tolocal() << book::code::oob];

    if(_parent_dc_)
        return _cursor_ = _parent_dc_->cursor(xy+_rect_.a);

    _cursor_ = _blk_ + xy.y * *width() + xy.x;
    //book::out() <<  "cursor=" << color::blueviolet << xy << color::reset;
    return _cursor_;
}


book::code twindc::update_child(const twindc& wdc)
{

    rectangle tmp = wdc._dirty_area_ + wdc._rect_.a;
    tmp  = _rect_.tolocal() &  tmp;
    if(!tmp)
        return book::code::rejected;

    if(!_dirty_area_)
        _dirty_area_ = tmp;
    else
        _dirty_area_ = _dirty_area_ | tmp;
    if(!_dirty_area_)
        return book::code::rejected;

    //book::debug() << book::fn::fun << color::orangered1 << tmp << color::reset;
    if(_parent_dc_)
        return _parent_dc_->update_child(*this);
    render();

    return book::code::complete;
}


void twindc::render()
{
    if(!_dirty_area_) return;
    book::debug() << book::fn::fun << " bloc geometry to 'commit': " << color::blueviolet << _dirty_area_ << color::reset;
    for(int y = 0; y < *_dirty_area_.height(); y++)
    {
        auto str = _blk_->render(cursor({_dirty_area_.a.x, _dirty_area_.a.y+y}), *_dirty_area_.width());
        terminal::cursor(_dirty_area_.a + cxy{0,y} + _rect_.a);
        std::cout << str;
        //book::out() << '"' << str << '"';
    }
    _dirty_area_ = {};
    fflush(stdout);
}


book::code twindc::update()
{
    if(!_dirty_area_)
        return book::code::rejected;

    if(_parent_dc_ != nullptr)
    {
        return _parent_dc_->update_child(*this);
    }

    // Ca se passe ici!
    render();

    return book::code::complete;
}

void twindc::resize(size new_geometry)
{
    _rect_.resize(new_geometry);
    book::info() << book::fn::fun << "new geometry: " << color::yellow << _rect_ << color::reset;
    if(!_parent_dc_)
    {
        delete [] _blk_;
        _blk_ = new chr[_rect_.dwh.area()+ *_rect_.width()];
        book::out() << " bloc reallocation done.";
    }
}


cxy twindc::where_is(chr* _c)
{
    return {
        static_cast<int>(_c-_blk_) % _rect_.dwh.w,
        static_cast<int>(_c-_blk_) /_rect_.dwh.w
    };
    //cxy xy;
    //xy.y = (_c-_blk_) /_rect_.dwh.w;
    //xy.x = (_c-_blk_) % _rect_.dwh.w;
    //return xy;
}


}// namespace tuxin::ui
