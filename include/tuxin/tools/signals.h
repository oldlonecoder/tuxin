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
#include <functional>
#include <utility>

// ------- copied, intellectual proprietary to:
// https://schneegans.github.io/tutorials/2015/09/20/signal-slot :
// 0xAC6A { 44138 }
// Modified and adapted for Rem and implement in basic threads, by oldlonecoder
// ------------------------------------------------------------------

namespace tuxin::signals
{


    
template<typename... Args> class action
{

public:
    std::string m_id{"anonymous signal"};
    int16_t    Handle{-1};
    using slot = std::function<book::action(Args...)>;
    using array = std::vector<typename action::slot>;
    using iterator = typename action::array::iterator;
    using accumulator = std::vector<book::action>;

    action() = default;
    ~action() = default;

    explicit action(std::string id_) : m_id(std::move(id_))
    {}

    action(std::string id_, typename action::accumulator &acc) : m_id(std::move(id_)), _acc(&acc)
    {}

    // Copy constructor and assignment create a new notifier.
    action(action const & /*unused*/)
    {}

    action &operator=(action const &other)
    {
        if (this != &other)
        {
            disconnect_all();
        }
        return *this;
    }

    // Move constructor and assignment operator work as expected.
    action(action &&other) noexcept:
        _slots(std::move(other._slots)),
        m_id(std::move(other.m_id)),
        _acc(std::move(other._acc))
    {}

    action &operator=(action &&other) noexcept
    {
        if (this != &other)
        {
            _slots = std::move(other._slots);
            m_id = std::move(other.m_id);
            _acc = std::move(other._acc);
        }

        return *this;
    }


    // Connects a std::function to the notifier. The returned
    // value can be used to Disconnect the function again.
    int16_t connect(std::function<book::action(Args...)> const &aslot) const
    {
        _slots.push_back(aslot);
        return (_slots.size()-1) & 0x7FFF;
    }

    // Convenience member method to Connect explicitely a member function of an
    // object to this notifier.
    template<typename T> int16_t connect_member(T *inst, book::action(T::* fun)(Args...))
    {
        return connect([=](Args... args)
                       {
                           return (inst->*fun)(args...);
                       });
    }

    // Convenience method to Connect a member function of an
    // object to this notifier.
    template<typename T> int16_t connect(T *inst, book::action(T::* fun)(Args...))
    {
        return connect([=](Args... args)
                       {
                           return (inst->*fun)(args...);
                       });
    }


    // Convenience method to Connect a const member function
    // of an object to this notifier.
    template<typename T> int16_t Connect(T *inst, book::action(T::* fun)(Args...) const)
    {
        return connect([=](Args... args)
                       {
                           return (inst->*fun)(args...);
                       });
    }

    // Disconnects a previously connected function.
    void disconnect(int16_t id) const
    {
        if(id>=_slots.size()) return ;
        auto I = _slots.begin() + id;
        _slots.erase(I);
    }

    // Disconnects all previously connected functions.
    void disconnect_all() const
    {
        if(!_slots.empty())
            _slots.clear();
    }

    //// Calls all connected functions.
    book::action operator()(Args... p)
    {
        if (_slots.empty())
            return book::action::continu;
        book::action R;
        for (auto const &fn: _slots)
        {
            R = fn(p...);
            if (_acc) _acc->push_back(R);
            if (R != book::action::continu) return R;
        }
        return R;
    }


    // Calls all connected functions except for one.
    book::action emit_for_all_but_one(const std::string &id_, Args... p)
    {
        book::action R;
        for (auto const &it: _slots)
        {
            if (it.m_id != id_)
            {
                R = it(p...);
                if (_acc) _acc->push_back(R);
                if (R != book::action::continu) return R;
            }
        }
        return R;
    }

    // Calls only one connected function.
    book::action to(int16_t id_, Args... p)
    {
        book::action R;
        if (id_ >= _slots.size())
        {
            R = (*_slots[id_])(p...);
            if (_acc) _acc->push_back(R);
            if (R != book::action::continu) return R;
        }
        return R;
    }

    bool empty()
    { return _slots.empty(); }

private:

    mutable typename action::array _slots;
    mutable typename action::accumulator *_acc{nullptr};
};

}


namespace tux
{





template<typename Ret=book::action, typename ...Parameters> class signal
{
    std::string m_id{"anonymous signal"};
    int16_t     handle{-1};
public:
    
    using slot = std::function<Ret(Parameters...)>;
    using array = std::vector<typename signal::slot>;
    using iterator = typename signal::array::iterator;
    using accumulator = std::vector<Ret>;

    signal() = default;

    ~signal() = default;

    explicit signal(std::string id_) : m_id(std::move(id_))
    {}

    signal(std::string id_, typename signal::accumulator &acc) : m_id(std::move(id_)), _acc(&acc)
    {}

    // Copy constructor and assignment create a new notifier.
    signal(signal const & /*unused*/)
    {}

    signal &operator=(signal const &other)
    {
        if (this != &other)
        {
            disconnect_all();
        }
        return *this;
    }

    // Move constructor and assignment operator work as expected.
    signal(signal &&other) noexcept:
        _slots(std::move(other._slots)),
        m_id(std::move(other.m_id)),
        _acc(std::move(other._acc))
    {}

    signal &operator=(signal &&other) noexcept
    {
        if (this != &other)
        {
            _slots = std::move(other._slots);
            m_id = std::move(other.m_id);
            _acc = std::move(other._acc);
        }

        return *this;
    }


    // Connects a std::function to the notifier. The returned
    // value can be used to Disconnect the function again.
    int16_t connect(std::function<Ret(Parameters...)> const &aslot) const
    {
        _slots.push_back(aslot);
        return (_slots.size()-1) & 0x7FFF;
    }

    // Convenience member method to Connect explicitly a member function of an
    // object to this notifier.
    template<typename T> int16_t connect_member(T *inst, Ret(T::* fun)(Parameters...))
    {
        return connect([=](Parameters... Args)
                       {
                           return (inst->*fun)(Args...);
                       });
    }

    // Convenience method to Connect a member function of an
    // object to this notifier.
    template<typename T>  int16_t connect(T *inst, Ret(T::* fun)(Parameters...))
    {
        return connect([=](Parameters... Args)
                       {
                           return (inst->*fun)(Args...);
                       });
    }


    // Convenience method to Connect a const member function
    // of an object to this notifier.
    template<typename T> typename signal::iterator connect(T *inst, Ret(T::* fun)(Parameters...) const)
    {
        return connect([=](Parameters... Args)
                       {
                           return (inst->*fun)(Args...);
                       });
    }

    // Disconnects a previously connected function.
    void disconnect(int16_t id) const
    {
        if(id>=_slots.size()) return;
        auto I = _slots.begin() + id;
        _slots.erase(I);
    }

    // Disconnects all previously connected functions.
    void disconnect_all() const
    {
        if(!_slots.empty())
            _slots.clear();
    }

    //// Calls all connected functions.
    // std::pair<Book::action, Ret>
    Ret operator()(Parameters... p)
    {
        if (_slots.empty())
            return Ret();
        Ret R;
        for (auto const &fn: _slots)
        {
            R = fn(p...);
            if (_acc) _acc->push_back(R);
        }
        return R;
    }


    // Calls all connected functions except for one.
    Ret emit_for_all_but_one(const std::string &id_, Parameters... p)
    {
        Ret R;
        for (auto const &it: _slots)
        {
            if (it.m_id != id_)
            {
                R = it(p...);
                if (_acc) _acc->push_back(R);
            }
        }
        return R;
    }

    // Calls only one connected function.
    Ret emit_for(typename signal::iterator id_, Parameters... p)
    {
        Ret R;
        if (id_ != _slots.end())
        {
            R = (*id_)(p...);
            if (_acc) _acc->push_back(R);
        }
        return R;
    }

    bool empty()
    { return _slots.empty(); }

private:

    mutable typename signal::array _slots;
    mutable typename signal::accumulator *_acc{nullptr};

};
}