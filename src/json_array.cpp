#include "json_array.h"

namespace json
{

void
array::clean_array()
{
    values.clear();
}

void
array::copy_array(const array &other)
{
    std::for_each(
        other.values.begin(), other.values.end(),
        [&] (const std::unique_ptr<value> &ptr) {
            this->values.push_back(std::move(ptr->clone()));
        }
    );
}

array::array(const array &other)
    : crtp_value<array>(), values()
{
    copy_array(other);
} 

array &
array::operator=(const array &other)
{
    clean_array();
    copy_array(other);
    return *this;
}

std::string
array::to_string() const
{
    std::string result = "[ ";
    for (auto pos = values.cbegin(); pos != values.cend(); ++pos) {
        if (pos != values.cbegin())
            result += ", ";
        result += (*pos)->to_string();
    } 
    result += " ]";
    return result;
}

} // namespace json
