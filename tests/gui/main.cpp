#include <crosswind/core/concurrent/atomical_property.hpp>
#include <crosswind/core/concurrent/mutexed_property.hpp>
#include <crosswind/core/concurrent/mutexed_container.hpp>
#include <crosswind/core/container/cacheable.hpp>
#include <crosswind/core/javascript/json.hpp>
#include <crosswind/core/crypto/base64.hpp>
#include <crosswind/core/crypto/sha1.hpp>

#include <crosswind/platform/generic/application.hpp>
#include <crosswind/platform/generic/filesystem.hpp>

#include <iostream>
#include <string>


int main(int argc, char **argv) {

    //Concurrent data structures.
    cw::core::concurrent::atomical_property<bool> foo_boolean(false);
    cw::core::concurrent::mutexed_property<std::string> foo_mutexed_string("Hello world");
    cw::core::concurrent::mutexed_container<std::map<std::string, std::string> > foo_map;
    cw::core::container::cacheable<bool> bool_cache;
    cw::core::javascript::json json;

    foo_map("Key", "Value");
    bool temporal_bool = foo_boolean.get();
    foo_boolean.set(true);

    std::string temporal_string = foo_mutexed_string.get();

    bool_cache.store("foolean", true);

    bool_cache.add_manipulation("false_manipulation", [](auto& map){
        for(auto& item : map){
            item.second = false;
        }
    });

    bool_cache.add_manipulation("true_manipulation", [](auto& map){
        for(auto& item : map){
            item.second = true;
        }
    });

    bool_cache.apply_manipulation("false_manipulation");

    std::cout << bool_cache.load("foolean") << std::endl;

    bool_cache.apply_manipulation("true_manipulation");

    std::cout << bool_cache.load("foolean") << std::endl;

    std::string base64_encoded_string = cw::core::crypto::base64::encode("Base string");
    std::string base64_decoded_string = cw::core::crypto::base64::encode(base64_encoded_string);

    std::cout << base64_encoded_string << std::endl;
    std::cout << base64_decoded_string << std::endl;

    std::cout << "SHA1: " << cw::core::crypto::sha1::compress(base64_decoded_string) << std::endl;

    std::string json_string = "{\"value\":1}";

    json.from_string(json_string);

    {
        auto& raw_json = json.data.acquire();
        std::cout << raw_json["value"] << std::endl;
        json.data.release();
    }

    cw::platform::generic::filesystem::add_directory("assets", true);
    cw::platform::generic::filesystem::add_directory("tests/gui", true);

    if(cw::platform::generic::filesystem::exists("data.json")){
        json.from_file(cw::platform::generic::filesystem::get_file_path("data.json"));

        auto& raw_json = json.data.acquire();
        std::cout << raw_json["compact"] << std::endl;
        std::cout << raw_json["schema"] << std::endl;
        json.data.release();

    }


    cw::platform::generic::application app;




    app.run();

    return 0;

}