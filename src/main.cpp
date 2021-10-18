#include "json.h"

int
main()
{
    json::object obj(
        std::make_pair(std::string("a"), json::integer(1)),
        std::make_pair(std::string("b"), json::array(json::integer(10), json::integer(20)))
    );
    std::cout << obj.to_string() << '\n';
}
