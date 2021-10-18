#ifndef _LAB2_JSON_PRIMITIVE_H_
#define _LAB2_JSON_PRIMITIVE_H_

#include "json_value.h"

namespace json
{

template <typename T>
class primitive: public crtp_value<primitive<T>>
{
private:
    T primitive_value;

public:
    primitive(const T &primitive_value)
        : primitive_value(primitive_value) {}
    operator T&() { return primitive_value; }

    virtual std::string to_string() const override 
        { return std::to_string(primitive_value); }
};

typedef primitive<long long>   integer;
typedef primitive<double>      real;
typedef primitive<std::string> string;
typedef primitive<bool>        boolean;

class null: public crtp_value<null>
{
public:
    virtual std::string to_string() const override
        { return "null"; }
};

} // namespace json

#endif // _LAB2_JSON_PRIMITIVE_H_
