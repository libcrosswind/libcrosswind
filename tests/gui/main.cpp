//#include <Crosswind/util/filesystem.hpp>

//#include <Crosswind/pools/widget_pool.hpp>
#include <iostream>
#include <string>

#include <crosswind/core/concurrent/atomical_property.hpp>
#include <crosswind/core/concurrent/mutexed_property.hpp>
#include <crosswind/core/concurrent/mutexed_container.hpp>
#include <crosswind/core/container/cacheable.hpp>
#include <crosswind/core/javascript/json.hpp>

#include <crosswind/core/crypto/base64.hpp>
#include <crosswind/core/crypto/sha1.hpp>

#include <crosswind/standard/geometry/rectangle.hpp>

int main(int argc, char **argv) {


    cw::core::concurrent::atomical_property<bool> the_bool;
    cw::core::concurrent::mutexed_property<std::string> the_string;
    cw::core::concurrent::mutexed_container<std::map<std::string, std::string> > the_map;
    cw::core::container::cacheable<bool> cache;
    cw::core::javascript::json json;

    cw::standard::geometry::rectangle<double> rect1(0, 0, 10, 10);
    cw::standard::geometry::rectangle<double> rect2(0, 0, 5, 10);

    the_map("K", "R");

    the_bool = true;
    bool boolean;
    boolean = the_bool;

    std::string str;
    str = the_map("K");
    std::cout << str <<std::endl;

    cache.store("boolean", false);

    cache.add_manipulation("true_manipulation", [](auto& map){
        for(auto& item : map){
            item.second = true;
        }
    });

    cache.apply_manipulation("true_manipulation");

    std::cout<< cache.load("boolean") << std::endl;

    cache.add_manipulation("false_manipulation", [](auto& map){
        for(auto& item: map){
            item.second = false;
        }
    });

    cache.apply_manipulation("false_manipulation");

    std::cout<< cache.load("boolean") << std::endl;

    std::string encoded = cw::core::crypto::base64::encode("THE STRING");
    std::string decoded = cw::core::crypto::base64::decode(encoded);

    std::cout<< encoded << std::endl;
    std::cout<< decoded << std::endl;

    std::cout<< "SHA1:" << cw::core::crypto::sha1::compress(decoded) << std::endl;


    std::string json_string = "{\"value\":1}";

    json.from_string(json_string);

    std::cout << json.data()["value"] << std::endl;

    std::cout << rect1.contains_xy(2.0, 5.0) << std::endl;

    std::cout << rect1.contains(rect2) << std::endl;



/*
    cw::filesystem::add_directory("assets", true);
    cw::filesystem::add_directory("tests/gui", true);

    auto button      = cw::widget_pool::create(0.1, 0.2, 0.4, 0.3, "blue");
*/
    return 0;

}