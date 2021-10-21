#ifndef _LAB2_JSON_H_
#define _LAB2_JSON_H_

#include <bits/stdc++.h>

namespace json
{

class object;
class array;

typedef std::variant<
    std::monostate,
    long long,
    double,
    bool,
    std::string,
    object,
    array
> value;

std::string to_string(const value &val);

class object
{
private:
    using container_type = std::map<std::string, value>;
    container_type children;

public:
    using child_type = container_type::value_type;
    using iterator = container_type::iterator;

    object() = default;
    object(const object &) = default;
    object(object &&) = default;
    object(const std::initializer_list<child_type> &list);
    ~object() = default;

    object &operator=(const object &) = default;
    object &operator=(object &&) = default;

    class value_proxy
    {
    private:
        container_type &children;
        value &val;

    public:
        value_proxy(container_type &children, const std::string &key)
            : children(children), val(children[key]) {}
        ~value_proxy(); 

        operator value&() { return val; }
        operator const value&() const { return val;  }
    };
    value_proxy operator[](const std::string &key)
        { return value_proxy(*this, key); }

    iterator begin() 
        { return children.begin(); }
    iterator end() 
        { return children.end(); }
    std::pair<iterator, bool> insert(const child_type &c) 
        { return children.insert(c); }
    std::pair<iterator, bool> insert(child_type &&c) 
        { return children.insert(std::move(c)); }
    iterator find(const std::string &key)
        { return children.find(key); }
    std::size_t erase(const std::string &key)
        { return children.erase(key); }    
    std::size_t size() const
        { return children.size(); }
    bool empty() const
        { return children.empty(); }
};

class array
{
private:
    using container_type = std::vector<value>;
    container_type values;

public:
    using child_type = container_type::value_type;
    using iterator = container_type::iterator;
    using const_iterator = container_type::const_iterator;

    array() = default;
    array(const array &) = default;
    array(array &&) = default;
    array(const std::initializer_list<child_type> &list);
    ~array() = default;

    array &operator=(const array &) = default;
    array &operator=(array &&) = default;

    value &operator[](std::size_t idx) 
        { return values[idx]; }
    const value &operator[](std::size_t idx) const
        { return values[idx]; }
    value &at(std::size_t idx)
        { return values.at(idx); }
    const value &at(std::size_t idx) const
        { return values.at(idx); }

    void insert(const_iterator iter, const value &val)
        { values.insert(iter, val); }
    void insert(const_iterator iter, value &&val)
        { values.insert(iter, std::move(val)); }
    void push_back(const value &val)
        { values.push_back(val); }
    void push_back(value &&val)
        { values.push_back(std::move(val)); }
    iterator erase(const_iterator iter)
        { return values.erase(iter); }
    void pop_back()
        { values.pop_back(); }
};

} // namespace json

#endif // _LAB2_JSON_H_
