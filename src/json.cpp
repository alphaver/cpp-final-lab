#include <bits/stdc++.h>
#include "json.h"

namespace json 
{

namespace 
{

struct string_visitor
{
    std::string operator()(null_type) const       { return "null"; }
    std::string operator()(integer i) const       { return std::to_string(i); }
    std::string operator()(real r) const          { return std::to_string(r); }
    std::string operator()(boolean b) const       { return b ? "true" : "false"; }
    std::string operator()(const string &s) const { return "\"" + s + "\""; }

    std::string operator()(const object &obj) const;
    std::string operator()(const array &arr) const;
};

template <typename Iter, typename ElemToStrFunc>
std::string
iterable_to_string(
    Iter begin, Iter end, 
    const std::string &open, const std::string &close,
    ElemToStrFunc conv
)
{
    if (begin == end)
        return open + close;

    std::string result = open + " ";
    for (auto pos = begin; pos != end; ++pos) {
        if (begin != pos)
            result += ", ";
        result += conv(*pos);
    }
    result += " " + close;
    return result;
}

std::string 
string_visitor::operator()(const object &obj) const
{
    return iterable_to_string(
        obj.cbegin(), obj.cend(), "{", "}",
        [](const object::value_type &p) 
            { return "\"" + p.first + "\": " + to_string(p.second); }
    );
}

std::string
string_visitor::operator()(const array &arr) const
{
    return iterable_to_string(arr.cbegin(), arr.cend(), "[", "]", to_string);
}

} // namespace 

std::string
to_string(const value &val)
{
    return std::visit(string_visitor(), val);
}

} // namespace json
