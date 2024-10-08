//
// Created by oldlonecoder on 24-09-27.
//

//#ifndef ELEMENT_H
//#define ELEMENT_H
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

#include "tuxin/tui/twindc.h"
#include "tuxin/tui/globals.h"
#include "tuxin/tools/object.h"

namespace tuxin::ui
{

class TUXIN_API element : public object
{
    CLASSNAME(element)

protected:


    globals::wflags::Type  _uiflags_{0};
    globals::uistyle::Type _uistyle_{0};
    globals::anchor::value _anchor_{globals::anchor::fixed};

    std::string _theme_name_{};
    twindc      _windc_{};

    // --------- UI style and State----------------
    color::pair                          _colors_{};
    globals::colors::attr_db::components _style_{};
    globals::colors::attr_db::elements   _theme_elements_{};
    globals::wstate::Type                _state_{globals::wstate::Active};
    // --------------------------------------------

public:


    element();
    element(element* _parent, std::string  a_id);
    virtual ~element();

    [[nodiscard]] color::pair colors();
    book::code  set_theme(const std::string& a_theme);
    book::code set_geometry(rectangle rect);

    element& operator = (const element&);
    const rectangle& geometry() const  { return _windc_._rect_; }
    book::code set_anchor(globals::anchor::value av);

#pragma region painter

    class TUXIN_API painter  final
    {
        friend class element;
        color::pair _colors_{};
        rectangle _rect_{};
        cadre::frame_matrix _model_{2,2,2,2,0};
        element* _parent_{nullptr};
        bool valid{false};
    public:
        painter() = default;
        painter(element* _parent, rectangle _rect={});
        ~painter();
        book::code set_geometry(rectangle _area);

        painter& clear(rectangle _rect={});
        painter& home();
        painter& to(const cxy& xy);

        painter& operator << (char _c);
        painter& operator << (const char* _c);
        painter& operator << (const twindc::chr::string& _str);
        painter& operator << (const std::string& _str);
        painter& operator << (std::string_view _str);
        painter& operator << (color::pair _cp);
        painter& operator << (color::code _c);
        painter& operator << (const cxy& xy);
        painter& operator << (cadre::index fr);
        painter& operator << (book::action action);
        template<typename T> painter& operator << (const T& v)
        {
            tuxin::string str;
            str << v;
            return this->operator<<((std::string)str);
        }
        painter& set_background(color::code _c);
        painter& set_foreground(color::code _c);
        painter& draw_frame(rectangle _rect, cadre::frame_matrix _modelmtx);
        painter& draw_frame(rectangle _rect={});

        cxy top_left() { return {0,0};  }
        cxy top_right() { return _rect_.tolocal().top_right(); }
        cxy bottom_right() { return _rect_.tolocal().bottom_right(); }
        cxy bottom_left() { return _rect_.tolocal().bottom_left(); }

    private:
        twindc::chr* _c_{nullptr};
        bool is_plain(const std::string& str);

    };

#pragma endregion painter

    element::painter begin_paint(rectangle _rect={});
    void      end_paint(element::painter& _painter);

    virtual book::code setup_ui();
    virtual book::code draw();
    virtual book::code redraw();
    virtual book::code resize(ui::size new_sz);
    virtual book::code parent_resized();
    //virtual book::code move(cxy dxy);
protected:
    virtual void dirty(element::painter& _painter);
    virtual book::code apply_placement();
    virtual void draw_frame(element::painter& paint);

    virtual book::code fit_width();
    virtual book::code fit_height();
    virtual book::code fit_to_right();
    virtual book::code fit_to_left();
    virtual book::code fit_to_hcenter();
    virtual book::code fit_to_vcenter();
    virtual book::code fit_to_center();



};

} // tuxin::ui

//#endif //ELEMENT_H
