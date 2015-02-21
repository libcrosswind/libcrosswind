#include <crosswind/core/concurrent/atomical_property.hpp>
#include <crosswind/core/concurrent/mutexed_property.hpp>
#include <crosswind/core/javascript/json.hpp>

#include <iostream>
#include <string>

class my_class{
public:



    cw::core::concurrent::mutexed_property<std::string> foo_string;
    cw::core::concurrent::atomical_property<bool> foo_boolean;
};

int main(int argc, char **argv) {

    //Concurrent data structures.
    my_class my_object;

    my_object.foo_boolean = true;
    my_object.foo_string = std::string("Hello world");

    auto& internal_string = my_object.foo_string.acquire();

    internal_string = "new message";

    my_object.foo_string.release();

    bool the_boolean = my_object.foo_boolean;
    std::string the_string = my_object.foo_string;

    std::cout << the_boolean << std::endl;
    std::cout << the_string  << std::endl;

    return 0;

}