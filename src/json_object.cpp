#include "json_object.h"

namespace json
{

void
object::clean_object()
{
    children.clear();
}

void
object::copy_object(const object &other)
{
    std::for_each(
        other.children.begin(), other.children.end(),
        [&] (const std::pair<const std::string, std::unique_ptr<value>> &p) {
            this->children.insert(std::make_pair(p.first, std::move(p.second->clone())));
        }
    );
}    

object::object(const object &other)
    : crtp_value<object>(), children()
{
    copy_object(other);
}

object &
object::operator=(const object &other)
{
    clean_object();
    copy_object(other);
    return *this;
}

std::string
object::to_string() const 
{
    std::string result = "{ ";
    for (auto pos = children.begin(); pos != children.end(); ++pos) {
        if (pos != children.begin())
            result += ", ";
        result += "\"" + pos->first + "\": " + pos->second->to_string();
    }
    result += " }";
    return result;
}

} // namespace json
