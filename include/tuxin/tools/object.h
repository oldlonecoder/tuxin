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
#include "tuxin/tools/book.h"


namespace tuxin
{

class  TUXIN_API object
{
    CLASSNAME_START(object)
protected:
    u64 event_mask{0};
public:
    object(){}
    using list = std::vector<object*>;

    using iterator = object::list::iterator;
    object(object* parent_obj, const std::string& obj_id);
    object(object&&)  = delete;
    object(const object&) = delete;

    virtual ~object();

    object& operator = (object&&) noexcept = delete;
    object& operator = (const object&) = delete;

    [[maybe_unused]] void set_id(const std::string& obj_id) { m_id = obj_id; }
    object::iterator get_child_iterator(object* obj);
    [[maybe_unused]] object::iterator get_child_iteratorby_id(const std::string& aid);

    //Book::Enums::Code detach();
    book::code detach(object* obj_ptr=nullptr);
    // -- All does the same, ...as a different name lol!
    
    template<typename T> [[maybe_unused]] T* as() { return dynamic_cast<T*>(this); }

    // -----------------------------------------------------------------------------
    template<typename T> T* parent() {
        if(!m_parent) return nullptr;
        return dynamic_cast<T*>(m_parent);
    }


    template<typename T> [[maybe_unused]] T* first_parent_of() {
        if(!m_parent) return nullptr;
        object* o = m_parent;
        while(o)
        {
            T* tp = dynamic_cast<T*>(o);
            if(tp) return tp;
            o = o->m_parent;
        }
        return nullptr;
    }

    template<typename T> [[maybe_unused]] std::vector<T*> children_list()
    {
        std::vector<T*> A;
        for(auto* o : m_children)
        {
            T* tp = dynamic_cast<T*>(o);
            if(tp) A.push_back(tp);
        }
        return A;
    }

    [[nodiscard]] std::string id() const { return m_id; }


    /*!
     * @brief Missing original meaning and reasons for this....sorry
     * @tparam T
     * @param fn
     */
    template<typename T> [[maybe_unused]] void for_each(std::function<bool(T& obj, bool alast)> fn)
    {
        auto it = m_children.begin();
        while(it != m_children.end())
        {
            bool l = (it + 1) == m_children.end();
            T* ty = (*it)->as<T>();
            if(ty)
                if (fn)
                    fn(*ty,l);
            ++it;
        }
    }
    void append_child(object* o);

    [[maybe_unused]] object::iterator begin() { return m_children.begin(); }
    [[maybe_unused]] object::iterator end()   { return m_children.end(); }

protected:
    object::list m_children = {};
    std::string m_id{};
    object* m_parent = nullptr;

};

} // lsg
