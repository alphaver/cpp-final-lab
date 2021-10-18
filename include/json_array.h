#ifndef _LAB2_JSON_ARRAY_H_
#define _LAB2_JSON_ARRAY_H_

#include "json_value.h"

namespace json
{

class array: public crtp_value<array>
{
private:
    std::vector<std::unique_ptr<value>> values;
    void clean_array();
    void copy_array(const array &other);

public:
    class iterator
    {
    private:
        std::vector<std::unique_ptr<value>>::iterator pos;

    public:
        iterator(const std::vector<std::unique_ptr<value>>::iterator &pos)
            : pos(pos) {}
        iterator(const iterator &other)
            : pos(other.pos) {}

        iterator &operator++()   { ++pos; return *this; }
        iterator operator++(int) { iterator old(*this); ++pos; return old; }
        iterator &operator--()   { --pos; return *this; }
        iterator operator--(int) { iterator old(*this); --pos; return old; }
        
        iterator operator+ (int poses) const { return iterator(pos + poses); } 
        iterator operator- (int poses) const { return iterator(pos - poses); }
        iterator &operator+= (int poses) { pos += poses; return *this; }
        iterator &operator-= (int poses) { pos -= poses; return *this; }

        std::ptrdiff_t operator- (const iterator &other) const
            { return this->pos - other.pos; }

        value &operator*()  { return *(*pos); }
        value *operator->() { return pos->get(); }

        std::vector<std::unique_ptr<value>>::iterator get_pos() { return pos; }
    };

    array() = default;
    array(const array &other);
    array(array &&other) = default;
    virtual ~array() = default;

    template <typename... JsonValues>
    array(const JsonValues &... values)
        : crtp_value<array>(), values()
    {
        for (auto &value: { values... }) {
            this->values.push_back(std::move(value.clone()));
        }
    }

    array &operator= (const array &other);
    array &operator= (array &&other) = default;

    iterator begin() { return iterator(values.begin()); }
    iterator end() { return iterator(values.end()); }

    iterator insert(iterator pos, const value &val)
        { return iterator(values.insert(pos.get_pos(), val.clone())); }
    iterator erase(iterator pos)
        { return iterator(values.erase(pos.get_pos())); }
    void push_back(const value &val)
        { values.push_back(val.clone()); }
    void pop_back()
        { values.pop_back(); }
    value &at(std::size_t index) const
        { return *values.at(index); }
    value &operator[](std::size_t index) const
        { return *values[index]; }
    std::size_t size() const
        { return values.size(); }

    virtual std::string to_string() const override;
};

inline array::iterator 
operator+ (int poses, const array::iterator &iter)
{ 
    return iter + poses; 
}

} // namespace json

#endif // _LAB2_JSON_ARRAY_H_
