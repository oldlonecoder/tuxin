/***************************************************************************
 *   Copyright (C) 1965/1987/2023 by Serge Lussier                         *
 *   serge.lussier@oldlonecoder.club                                       *
 *                                                                         *
 *                                                                         *
 *   Unless otherwise specified, all Code IsIn this project is written       *
 *   by the author (Serge Lussier)                                         *
 *   and no one else then not even {copilot, chatgpt, or any other AI}     *
 *   --------------------------------------------------------------------- *
 *   Copyrights from authors other than Serge Lussier also apply here      *
 ***************************************************************************/


#pragma once
#include "tuxin/tools/string.h"

namespace tuxin::ui
{


struct TUXIN_API cxy {

    int x = -1;
    int y = -1;

    using array = std::vector<cxy>;
    using iterator = cxy::array::iterator;
    using citerator = cxy::array::const_iterator;

    cxy() = default;
    cxy(cxy &&) noexcept = default;
    ~cxy() = default;
    cxy(int c_x, int c_y) : x(c_x), y(c_y){}
    cxy(const cxy &p) = default;
    cxy &operator=(const cxy &p) = default;
    cxy &operator-=(const cxy &dxy);
    cxy &operator+=(const cxy &dxy);
    bool operator==(cxy rhs) const;
    bool operator>(cxy rhs) const;
    bool operator<(cxy rhs) const;
    cxy operator+(const cxy &dxy) const;

    cxy operator+(int dx) const
    {
        return {dx + x, y};
    }
    [[nodiscard]] cxy get_max(const cxy &rhs) const;
    [[nodiscard]] cxy get_min(const cxy &rhs) const;
    cxy operator-(const cxy &rhs) const;
    [[nodiscard]] cxy lesser(cxy rhs) const;
    [[nodiscard]] cxy greater(cxy rhs) const;
    // cxy operator<<(cxy rhs) const;
    // cxy operator>>(cxy rhs) const;
    cxy &operator++();
    cxy &operator++(int);
    cxy &operator--();
    cxy &operator--(int);
    cxy &operator()(int x_, int y_);
    operator std::string() const;
};


struct TUXIN_API size {
    int w = 0;
    int h = 0;
    // size policies:
    cxy min_size{};
    cxy max_size{};
    // --------------
    operator bool() const { return ((w > 0) && (h > 0)); }
    operator std::string() const;
    bool operator<(const size &dwh) const;
    bool operator==(const size &dwh) const;
    bool operator>(const size &dwh) const;
    bool operator!=(const size &dwh) const;
    void set_min_max(cxy mi, cxy ax);
    [[nodiscard]] int32_t area() const { return w*h;}
    bool has_minmax() const;
};


/*!
 * @brief Rectangular Geometry object (inspired by the Qt project, many, many years ago).
 *
 * It has evolved with my own point of view and limitations.
 * @li Provides internal Cursor relative coordinates
 * @li Still needs more limit implementations (min-max restrictions helpers)
 *
 * @author oldlonecoder (lussier.serge@gmail.com)
 *
 */
struct TUXIN_API rectangle {

    cxy a{0, 0};
    cxy b{0, 0};
    cxy cursor{0,0}; ///< inner cursor coordinates used by the location operations, relative to the rectangle::a (topleft) coord.

    size dwh;
    bool nowrap = true;

    //static constexpr std::string_view    string_format = R"((\{3d},\{-3d})-[a:(\{3d},\{-3d}) b:(\{3d},\{-3d})]-[w:\{3d} h:\{-3d}])";  Disabled;

    using array = std::vector<rectangle>;
    using iterator = rectangle::array::iterator;
    using citerator = rectangle::array::const_iterator;

    rectangle() = default;
    ~rectangle() = default;
    rectangle(rectangle &&r) noexcept = default;
    rectangle(const rectangle &r) = default;
    rectangle(const cxy &a_, const cxy &b_);
    rectangle(const cxy &a_, const size &d);
    rectangle(int x, int y, int w, int h);
    explicit rectangle(const size &dxy);
    rectangle &operator=(rectangle &&r) noexcept = default;
    rectangle &operator=(const rectangle &r) = default;
    void assign(int x, int y, int w, int h);
    void assign(const cxy &a_, const cxy &b_);
    void assign(const cxy &a_, const size &dxy);
    cxy local();
    rectangle tolocal();
    cxy relative();
    void set_topleft(cxy pt);
    rectangle grow(cxy dxy);
    bool operator == (const rectangle& rhs) const;
    rectangle &operator+=(const cxy &dx);
    rectangle &operator-=(const cxy &dx);
    void resize(const size &new_sz);
    void moveat(const cxy &p);
    bool in(const cxy &pt) const;
    void move(const cxy &deltapt);
    std::tuple<cxy,cxy,ui::size> components() const { return {a, b,dwh}; }
    // [[nodiscard]] int width() const { return dwh.w; }
    // [[nodiscard]] int height() const { return dwh.h; }
    template<typename T=int> std::optional<T> width() const
    {
        if constexpr (std::is_same_v<T, float>)             return static_cast<float>(dwh.w         );
        else if constexpr (std::is_same_v<T, double>)       return static_cast<double>(dwh.w        );
        else if constexpr (std::is_same_v<T, int>)          return static_cast<int>(dwh.w           );
        else if constexpr (std::is_same_v<T, unsigned int>) return static_cast<unsigned int>(dwh.w  );
        else if constexpr (std::is_same_v<T, char>)         return static_cast<char>(dwh.w          );
        else if constexpr (std::is_same_v<T, unsigned char>)return static_cast<unsigned char>(dwh.w );
        else if constexpr (std::is_same_v<T, bool>)         return static_cast<bool>(dwh.w          );
        else if constexpr (std::is_same_v<T, i8>)           return static_cast<i8>(dwh.w            );
        else if constexpr (std::is_same_v<T, u8>)           return static_cast<u8>(dwh.w            );
        else if constexpr (std::is_same_v<T, u16>)          return static_cast<u16>(dwh.w           );
        else if constexpr (std::is_same_v<T, u32>)          return static_cast<u32>(dwh.w           );
        else if constexpr (std::is_same_v<T, u64>)          return static_cast<u64>(dwh.w           );
        else if constexpr (std::is_same_v<T, size_t>)       return static_cast<size_t>(dwh.w        );// like u64
        else if constexpr (std::is_same_v<T, i16>)          return static_cast<i16>(dwh.w           );
        else if constexpr (std::is_same_v<T, u16>)          return static_cast<u16>(dwh.w           );
        else if constexpr (std::is_same_v<T, u32>)          return static_cast<u32>(dwh.w           );
        else if constexpr (std::is_same_v<T, i64>)          return static_cast<u64>(dwh.w           );
        else if constexpr (std::is_same_v<T, std::string>)  return std::to_string(dwh.w             ); 
        //book::error() << book::code::expected << " compatible left-value type";
        return {};
    }
    template<typename T=int> std::optional<T> height() const
    {
        if constexpr (std::is_same_v<T, float>)             return static_cast<float>(dwh.h);
        else if constexpr (std::is_same_v<T, double>)       return static_cast<double>(dwh.h);
        else if constexpr (std::is_same_v<T, int>)          return static_cast<int>(dwh.h);
        else if constexpr (std::is_same_v<T, unsigned int>) return static_cast<unsigned int>(dwh.h);
        else if constexpr (std::is_same_v<T, char>)         return static_cast<char>(dwh.h);
        else if constexpr (std::is_same_v<T, unsigned char>)return static_cast<unsigned char>(dwh.h);
        else if constexpr (std::is_same_v<T, bool>)         return static_cast<bool>(dwh.h);
        else if constexpr (std::is_same_v<T, i8>)           return static_cast<i8>(dwh.h);
        else if constexpr (std::is_same_v<T, u8>)           return static_cast<u8>(dwh.h);
        else if constexpr (std::is_same_v<T, u16>)          return static_cast<u16>(dwh.h);
        else if constexpr (std::is_same_v<T, u32>)          return static_cast<u32>(dwh.h);
        else if constexpr (std::is_same_v<T, u64>)          return static_cast<u64>(dwh.h);  // like u64
        else if constexpr (std::is_same_v<T, size_t>)       return static_cast<size_t>(dwh.h);
        else if constexpr (std::is_same_v<T, i16>)          return static_cast<i16>(dwh.h);
        else if constexpr (std::is_same_v<T, u16>)          return static_cast<u16>(dwh.h);
        else if constexpr (std::is_same_v<T, u32>)          return static_cast<u32>(dwh.h);
        else if constexpr (std::is_same_v<T, i64>)          return static_cast<u64>(dwh.h);
        else if constexpr (std::is_same_v<T, std::string>)  return std::to_string(dwh.h);
        //book::error() << book::code::expected << " compatible left-value type";
        return {};
    }

    bool operator[](const cxy &pt) const;
    cxy top_left()const;
    cxy top_right()const;
    cxy bottom_left()const;
    cxy bottom_right()const;
    [[nodiscard]] rectangle operator&(const rectangle &r) const;

    /*!
     * \brief operator / get the intersection between this and rhs then get the origin of this from rhs
     * \param rhs
     * \return result rectangle
     */
    rectangle operator/(const rectangle &rhs) const;

    /*!
        @brief merges this and r
    */
    rectangle operator|(const rectangle &r) const;
    rectangle operator+(const cxy &pt) const;
    rectangle operator-(const cxy &pt) const;
    [[nodiscard]] std::string tostring() const;
    operator std::string() const;
    operator bool() const { return (dwh); }//.operator bool();
    //------------- location operations ---------------------------------
    void home();
    bool operator++();
    bool operator++(int);
    bool operator--();
    bool operator--(int);
    bool goto_xy(cxy xy);
    cxy operator*() const
    { return cursor; }

};


struct TUXIN_API string2d
{
    tuxin::string win{};
    rectangle r;

    string2d& gotoxy(int x, int y);
    string2d& operator<< (cxy xy);
    void set_geometry(int w, int h);

    // internal cursor movements:
    string2d& operator++();
    void operator++(int);
    string2d& operator--();
    void operator--(int);
    // --------------------------
    template<typename t> string2d& operator<< (t v)
    {
        tuxin::string str;
        str << v;
        return put(str());
    }




    string2d& put(const std::string& txt);

    void clear();
    std::string details();
    operator std::string();// {return win ? win->str() : "";}

};

}
