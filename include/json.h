#ifndef _LAB2_JSON_H_
#define _LAB2_JSON_H_

#include <bits/stdc++.h>

namespace json
{

class _value_wrapper;

typedef long long       integer;
typedef double          real;
typedef bool            boolean;
typedef std::monostate  null_type;
typedef std::string     string;

const null_type null = null_type {};

typedef std::map<std::string, _value_wrapper> object;
typedef std::vector<_value_wrapper> array;

typedef std::variant<
    null_type,
    integer,
    real,
    boolean,
    string,
    object,
    array
> value;

class _value_wrapper: public value
{
public:
    template <typename... Args>
    _value_wrapper(Args&&... args)
        : value { std::forward<Args>(args)... } {}
    virtual ~_value_wrapper() = default;
};

template <typename T>
T &get(value &val) { return std::get<T>(val); }
template <typename T>
T &&get(value &&val) { return std::get<T>(std::move(val)); }
template <typename T>
const T &get(const value &val) { return std::get<T>(val); }

std::string to_string(const value &val);

} // namespace json

#endif // _LAB2_JSON_H_
