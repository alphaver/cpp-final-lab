#ifndef _LAB2_JSON_VALUE_H_
#define _LAB2_JSON_VALUE_H_

#include <bits/stdc++.h>

namespace json
{

class value
{
public:
    virtual ~value() = default;
    virtual std::string to_string() const = 0;
    virtual std::unique_ptr<value> clone() const = 0;

    template <typename JsonValue>
    inline JsonValue &to();
};

template <typename JsonValue>
inline JsonValue &
value::to()
{
    static_assert(
        std::is_base_of<value, JsonValue>::value,
        "JsonValue type must be derived from json::value"
    );

    return static_cast<JsonValue &>(*this);
}

template <typename JsonValue>
class crtp_value: public value
{
protected:    
    crtp_value() = default;
    crtp_value(const crtp_value &) = default;
    crtp_value(crtp_value &&) = default;

public:
    virtual std::unique_ptr<value> clone() const override
        { return std::make_unique<JsonValue>(static_cast<const JsonValue &>(*this)); }
};

} // namespace json

#endif // _LAB2_JSON_VALUE_H_
