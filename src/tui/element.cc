//
// Created by oldlonecoder on 24-09-27.
//

#include "../../include/tuxin/tui/element.h"
#include "tuxin/tui/globals.h"

//#include <memory>
#include <utility>

/******************************************************************************************
 *   Copyright (C) 1965/1987/2023 by Serge Lussier                                        *
 *   serge.lussier@oldlonecoder.club                                                      *
 *                                                                                        *
 *                                                                                        *
 *   Unless otherwise specified, all Code IsIn this project is written                    *
 *   by the author (Serge Lussier)                                                        *
 *   and no one else then not even {copilot, chatgpt, or any other AI calamities}         *
 *   ----------------------------------------------------------------------------------   *
 *   Copyrights from authors other than Serge Lussier also apply here                     *
 *   Open source FREE licences also apply To the Code from the same author (Serge Lussier)*
 *   ----------------------------------------------------------------------------------   *
 ******************************************************************************************/

//#pragma once




namespace tuxin::ui
{





element::element()
{

}

element::~element()
{
    book::info() << book::fn::fun << color::yellow
    << id() << color::reset << "  -> @" << color::blueviolet << this << color::reset;

}


element::element(element* _parent, std::string  a_id): object(_parent,a_id)
{
    if (parent<element>())
    {
        _windc_._blk_ = _parent->_windc_._blk_;
        _windc_._parent_dc_ = &_parent->_windc_;
        book::debug() << book::fn::fun << "element '" << color::yellow << id() << color::reset << " set to child of '" << _parent->id() << color::reset << "'.";
    }

}


element& element::operator = (const element&)
{
    book::warning() << book::fn::fun << "element '" << id() << "' does not implements copy assignment...yet...";
    return *this;
}

book::code element::set_anchor(globals::anchor::value av)
{
    _anchor_ = av;
    ///@todo respond to the (new) _anchor_ value...
    /// ...
    apply_placement();


    return book::code::accepted;
}


color::pair element::colors() { return  _style_[_state_]; }


book::code element::set_theme(const std::string& a_theme)
{
    _theme_name_ = a_theme;
    auto const& comp = globals::colors::attr_db::theme().find(_theme_name_);
    if (comp == globals::colors::attr_db::theme().end())
    {
        book::error() << book::fn::fun << "Theme '" << color::orangered1 <<  _theme_name_ << color::reset << "' not found" << book::fn::endl;
        return book::code::rejected;
    }

    _theme_elements_ = globals::colors::attr_db::theme()[_theme_name_];
    _style_ =  globals::colors::attr_db::theme()[_theme_name_]["Widget"];
    _colors_ = _style_[globals::wstate::Active];

    book::log() << color::yellow << id() << color::reset << " theme set to '" << _style_[_state_] << " " <<  _theme_name_ << " " << color::reset << "'.";
    return book::code::accepted;
}


/*!
 * @brief set the element's ...geometry...
 * @note Handle and apply size policies here
 * @param rect
 * @return accepted or rejected...
 */
book::code element::set_geometry(rectangle rect)
{
    book::debug() << book::fn::fun << "request geometry:" << color::orangered1 << rect.tostring() << color::reset;
    return _windc_.set_geometry(rect);
}


element::painter element::begin_paint(rectangle _rect)
{
    return {this,_rect};
}



void element::end_paint(element::painter& _painter)
{
    if(auto r = _windc_.dirty(_painter._rect_); !r) return;
    _windc_.update();
}


void element::dirty(element::painter& _painter)
{
    _windc_.dirty(_painter._rect_);
}

book::code element::apply_placement()
{
    using namespace globals;
    book::debug() << book::fn::fun << '\'' << color::yellow << id() << color::reset << "\' :";

    // need to separate and simple access to the rectangle coordinates components:
    auto par = parent<element>();
    rectangle ar;
    if(par)
        ar = parent<element>()->_windc_._rect_.tolocal();
    else
        ar = terminal::geometry();

    auto [a,b,sz] = ar.components();
    auto [_a,_b,_sz] = _windc_._rect_.components();

    if(_anchor_ & anchor::width_fit) fit_width();
    if(_anchor_ & anchor::height_fit) fit_height();
    else
    {
        if(_anchor_ & anchor::fit_center)
        {
            _windc_._rect_.moveat({(sz.w -_sz.w)/2, (sz.h -_sz.h)/2});
            return book::code::accepted;
        }
    }
    if(_anchor_ & anchor::fit_vcenter)
        _windc_._rect_.moveat({_a.x,(sz.h -_sz.h)/2});
    else
    {
        if(_anchor_ & anchor::fit_top)
        {
            if(((_uistyle_ & uistyle::Frame)&&(_anchor_ & anchor::onframe_fit)) || !(_uistyle_ & uistyle::Frame))
                _windc_._rect_.moveat(cxy{a.x,0});
            else
                _windc_._rect_.moveat(cxy{a.x,1});
        }
        else
        {
            if(_anchor_ & anchor::fit_bottom)
            {
                book::out() << color::yellow << id() << " request fit to bottom of...("<< color::chartreuse6 << ar << color::reset << "):";
                if(((_uistyle_ & uistyle::Frame)&&(_anchor_ & anchor::onframe_fit)) || !(_uistyle_ & uistyle::Frame))
                    _windc_._rect_.moveat(cxy{a.x, ar.b.y});
                else
                    _windc_._rect_.moveat(cxy{a.x, ar.b.y});
            }
        }
    }
    if(_anchor_ & anchor::fit_hcenter)
        _windc_._rect_.moveat({(sz.w - _sz.w)/2, _a.y});
    else
    {
        book::out() << color::yellow << id() << color::reset << " not centered:";
        if(_anchor_ & anchor::fit_right)
        {
            book::out() << color::yellow << id() << color::reset << " fit right:";
            if(((_uistyle_ & uistyle::Frame)&&(_anchor_ & anchor::onframe_fit)) || !(_uistyle_ & uistyle::Frame))
                _windc_._rect_.moveat(cxy{b.x - _sz.w, b.y});
            else
                _windc_._rect_.moveat(cxy{b.x -_sz.w-1, sz.h});
            book::out() << geometry();
        }
        else
            if(_anchor_ & anchor::fit_left)
            {
                if(((_uistyle_ & uistyle::Frame)&&(_anchor_ & anchor::onframe_fit)) || !(_uistyle_ & uistyle::Frame))
                    _windc_._rect_.moveat(cxy{0, _a.y});
                else
                    _windc_._rect_.moveat(cxy{1, _a.y});
            }
    }
    //...
    book::out() << "applied geometry:" << color::yellow << id() << color::lime << geometry() << color::yellow;
    return book::code::accepted;
}

void element::draw_frame(painter &paint)
{
    paint.draw_frame();
}

book::code element::fit_width()
{
    using namespace globals;
    book::debug() << book::fn::fun << color::yellow << id() << color::reset << "before resize: " << color::hotpink4 << geometry() << color::reset;
    if(element* e = parent<element>(); e)
    {
        book::out() << "Call " << color::yellow << id() << color::lightskyblue4 << "::resize():";
        resize({*e->geometry().width(), *_windc_._rect_.height()});
        book::out() << color::yellow << id() << color::reset << " new geometry" << color::lime << geometry() << " : fit width on " << color::yellow << e->id() << color::cornflowerblue << e->geometry();
    }
    else
    {
        resize({*terminal::geometry().width(),*_windc_._rect_.height()});
        book::debug() << color::yellow << id() << " fit width in (terminal)" << color::hotpink4 << terminal::geometry();
    }
    // if(!(_anchor_ & anchor::onframe_fit) && (_uistyle_ & uistyle::Frame))
    // {
    //     resize({geometry().dwh.w-2,*geometry().height()});
    //     _windc_._rect_.a.x += 1;
    // }

    book::out() << color::yellow << id() << color::blueviolet << " stretched to fit in width: final width value:" << color::hotpink4 << *geometry().width();

    return book::code::accepted;
}

book::code element::fit_height()
{
    return book::code::implemented;
}

book::code element::fit_to_right()
{
    return book::code::implemented;
}

book::code element::fit_to_left()
{
    return book::code::implemented;
}

book::code element::fit_to_hcenter()
{
    return book::code::implemented;
}

book::code element::fit_to_vcenter()
{
    return book::code::implemented;
}

book::code element::fit_to_center()
{
    return book::code::implemented;
}


book::code element::draw()
{
    book::log() << book::fn::fun << color::yellow << id() << " geometry:" << color::hotpink4 <<  geometry();
    auto p = begin_paint();
    p.clear();
    if(_uistyle_ & globals::uistyle::Frame)
        p.draw_frame();

    for(auto* child : m_children)
        if(element* e = child->as<element>(); e) e->draw(); // implement "redraw" then call redraw instead...

    end_paint(p);
    return book::code::done;
}

book::code element::setup_ui()
{
    return book::code::implemented;
}

book::code element::redraw()
{
    book::log() << book::fn::fun << color::yellow << id() << " geometry:" << color::hotpink4 <<  geometry();
    auto p = begin_paint();
    p.clear();
    if(_uistyle_ & globals::uistyle::Frame)
        p.draw_frame();
    end_paint(p);
    for(auto* child : m_children)
        if(element* e = child->as<element>(); e) e->redraw(); // implement "redraw" then call redraw instead...
    return book::code::done;
}

book::code element::resize(ui::size new_sz)
{
    _windc_.resize(new_sz);
    book::debug() << book::fn::fun << color::yellow << id() << color::reset <<"::resize(" << color::lime << new_sz.w << color::reset << "x" << color::lime << new_sz.h << color::reset << "):";

    for(auto* child : m_children)
        if(element* e = child->as<element>(); e) e->parent_resized(); // implement "redraw" then call redraw instead...
    return book::code::done;
}

book::code element::parent_resized()
{
    apply_placement();
    for(auto *o: m_children)
        if(element* e = o->as<element>(); e) e->apply_placement();
    return book::code::done;
}



} // tuxin::ui

