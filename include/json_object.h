#ifndef _LAB2_JSON_OBJECT_H_
#define _LAB2_JSON_OBJECT_H_

#include "json_value.h"

namespace json
{

class object: public crtp_value<object>
{
private:
    std::map<std::string, std::unique_ptr<value>> children;
    void clean_object();
    void copy_object(const object &other);

public:
    typedef std::pair<
        std::reference_wrapper<const std::string>, 
        std::reference_wrapper<value>
    > child_type;

    class iterator 
    {
    private:
        std::map<std::string, std::unique_ptr<value>>::iterator pos; 
        child_type inner_pair;

        void update_inner_pair() 
        { 
            inner_pair = { std::cref(pos->first), std::ref(*(pos->second)) };
        }

    public:
        iterator(const std::map<std::string, std::unique_ptr<value>>::iterator &pos)
            : pos(pos)
            , inner_pair({ std::cref(pos->first), std::ref(*(pos->second)) }) {}
        iterator(const iterator &other) 
            : pos(other.pos), inner_pair(other.inner_pair) {}
        
        iterator &operator++ () 
            { ++pos; update_inner_pair(); return *this; }
        iterator operator++ (int) 
            { iterator old(*this); ++pos; update_inner_pair(); return old; }
        iterator &operator-- () 
            { --pos; update_inner_pair(); return *this; }
        iterator operator-- (int) 
            { iterator old(*this); --pos; update_inner_pair(); return old; }

        child_type operator*()  { return inner_pair; }
        child_type *operator->() { return &inner_pair; }

        using difference_type = long;
        using value_type = child_type;
        using pointer = child_type *;
        using reference = child_type &;
        using iterator_category = std::bidirectional_iterator_tag;
    };

    object() = default;
    object(const object &other);
    object(object &&other) = default;
    virtual ~object() = default;
    
    template <typename... JsonValues>
    object(std::pair<std::string, JsonValues>... children)
        : crtp_value<object>(), children()
    {
        for (value &child: { children... }) {
            this->children.insert(std::make_pair(child.first, std::move(child.second.clone())));
        }
    } 

    object &operator=(const object &other);
    object &operator=(object &&other) = default;

    iterator begin() { return iterator(children.begin()); }
    iterator end() { return iterator(children.end()); }
    bool insert(const std::string &key, const value &val)
        { return children.insert({ key, val.clone() }).second; }
    std::size_t erase(const std::string &key)
        { return children.erase(key); }
    iterator find(const std::string &key)
        { return iterator(children.find(key)); }
    std::size_t size() const
        { return children.size(); }

    virtual std::string to_string() const override;
};

} // namespace json

#endif // _LAB2_JSON_OBJECT_H_
