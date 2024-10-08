//#ifndef INTUI_GLOBALS_H
//#define INTUI_GLOBALS_H
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

#include "tuxin/tools/book.h"
#include "tuxin/tools/geometry.h"
#include "tuxin/tui/terminal.h"

namespace tuxin::ui
{



/**
 * @brief The Core drawing surface of all elements.
   all ui element have a private twindc which define their own geometry, relative to their parent twindc.
   all toplevel elements have a private twindc::chr bloc which is shared with all children elements.
 * 
 */
class TUXIN_API twindc final
{
public:

    /**
     * @brief unsigned 32 bits integer of ccaui encoded charater cell informations.
     * 
     */
    struct TUXIN_API chr 
    {   
        u32 d{0x8003A020};
        using string = std::vector<chr>;
        static constexpr u32 CharMask  = 0x800000FF;
        static constexpr u32 FGMask    = 0x0000FF00;
        static constexpr u32 BGMask    = 0x00FF0000;
        static constexpr u32 CMask     = 0x00FFFF00;
        static constexpr u32 ColorsMask= 0x00FFFF00;
        static constexpr u32 AttrMask  = 0xFF000000;
        static constexpr u32 UtfMask   = 0xB10000FF;
        static constexpr u32 StyleMask = 0x0E000000;
        // ==============u===attributes==========================
        static constexpr u32 UGlyph    = 0x01000000;
        static constexpr u32 Underline = 0x02000000;
        static constexpr u32 Stroke    = 0x04000000;
        static constexpr u32 Blink     = 0x08000000;
        static constexpr u32 Accent    = 0x10000000;
        static constexpr u32 Frame     = 0x20000000;
        static constexpr u32 TRGB      = 0x40000000;
        /// This will maku use of true-color RGB command instead of the re-routed terminal GUI colors profile
        static constexpr u32 ASCII     = 0x80000000;
        static constexpr u32 UTFBITS   = Accent | Frame | UGlyph;
        // ==============Bit Shift ============================
        static constexpr int FGShift = 0x08;
        static constexpr int BGShift = 0x10;
        static constexpr int ATShift = 0x18;



        chr() = default;

        explicit chr(U32 Ch);
        explicit chr(chr* C);
        chr(chr& C){d = C.d;}
        chr(const chr& C){d = C.d;}
        ~chr() = default;

        chr& set_fg(color::code fg_);
        chr& set_bg(color::code bg_);

        chr& set_attributes(U32 Ch);
        //chr& set_colors(color::pair&&Ch);
        // chr& ResetAttributes(chr::Type bits_);

        chr& set_colors(const color::pair&CP);

        chr& operator=(U32 Ch);
        chr& operator=(const chr& Ch) = default;
        chr& operator=(const U32* Ch);
        chr& operator=(char Ch);
        chr& operator=(int Ch)
        {
            d = Ch;
            return *this;
        };

        [[nodiscard]] std::string get_utf_string() const;

        [[nodiscard]] color::code     foreground() const;
        [[nodiscard]] color::code     background() const;
        [[nodiscard]] color::pair     colors() const;
        [[nodiscard]] glyph::type     icon_id() const;
        [[nodiscard]] accent_fr::type accent_id() const;
        [[nodiscard]] cadre::index    frame_id() const;
        [[nodiscard]] char     ascii() const;
        chr&  operator*() { return *this; }
        [[nodiscard]] uint16_t attributes() const;
        chr& operator <<(glyph::type gl);
        chr& operator <<(accent_fr::type ac);
        chr& operator << (cadre::index fr);
        chr& operator <<(color::pair cp);

        
        chr& operator <<(chr Ch)
        {
            d = Ch.d;
            return *this;
        }

        static std::string render(const chr::string& _string);
        static std::string render(const chr* _blk, int _width);
        
        chr&     operator <<(char Ch);
        [[nodiscard]] std::string render_colors() const;
        explicit    operator std::string() const;
        [[nodiscard]] std::string details() const;
    };


private:
    friend class element;
    ///...

    chr*        _blk_{nullptr};       ///< Shared Pointer to the toplevel Bloc Window;
    chr*        _cursor_{nullptr};    ///< Internal cursor to chr pointer.
    rectangle   _rect_{};             ///< this twindc geometry, which defines also the containment geometry of the element.
                                    ///< All non-toplevel element are relative to their parent element.
    rectangle   _dirty_area_{};     //< ...
    twindc*     _parent_dc_{nullptr}; ///< shared pointer to the parent DC;
    cxy         _pxy_{};             ///< Stored coordinates from peek_xy(...)
    using children_dc = std::vector<twindc*>; ///< Mandatory children windc for message propagation such as resize; widget state; style changes; etc.

    //void clip(rectangle& rect);

public:
    twindc() = default;
    explicit twindc(twindc& _parent_win);
    twindc(twindc&&) = default;
    ~twindc();

    twindc& operator =  (twindc&& twdc) noexcept = default;
    twindc& operator =  (twindc& twdc) = default;
    template<typename T=int> std::optional<T> width()  { return _rect_.width<T>(); }
    template<typename T=int> std::optional<T> height() { return _rect_.height<T>(); }
    template<typename T=int> std::optional<T> area()   { return _rect_.height<T>() * _rect_.width<T>(); }
    book::code set_geometry(const rectangle& _rect);
    [[nodiscard]] const rectangle& geometry() const { return _rect_; }

    chr*       cursor(const cxy& xy);

    book::code update_child(const twindc& wdc);
    void       render();
    book::code clear(const color::pair& _cp, rectangle _rect={});
    book::code dirty(rectangle _rect);
    cxy where_is(chr* _c);
    book::code update();
    void resize(ui::size new_geometry);
};







}  // namespace tuxin::ui
