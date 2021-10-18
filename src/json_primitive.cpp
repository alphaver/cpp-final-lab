#include "json_primitive.h"

template <>
std::string
json::primitive<std::string>::to_string() const
{
    return "\"" + primitive_value + "\"";
}

