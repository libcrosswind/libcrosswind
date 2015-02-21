#include <crosswind/core/concurrent/atomical_property.hpp>
#include <crosswind/core/concurrent/mutexed_property.hpp>
//#include <crosswind/core/javascript/json.hpp>
#include <crosswind/platform/generic/application.hpp>

#include <iostream>
#include <string>


int main(int argc, char **argv) {

    //Concurrent data structures.
    cw::core::concurrent::atomical_property<bool> foo_boolean(false);
    cw::core::concurrent::mutexed_property<bool> foo_mutexed_boolean(false);
    cw::platform::generic::application app;
    app.run();

    return 0;

}