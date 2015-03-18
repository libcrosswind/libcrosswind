#pragma once

#include <memory>
#include <string>
#include <jsoncons/json.hpp>

#include <crosswind/concurrent/mutex_property.hpp>
#include <crosswind/platform/filesystem.hpp>

namespace cw{
namespace javascript{

    class json;

}// namespace javascript
}// namespace cw

class cw::javascript::json{
public:
    json(){
    }

    json& from_file(const std::string& filename){
         
         if(cw::platform::filesystem::exists(filename)){

            auto& raw_json = data.acquire();
            raw_json = jsoncons::json::parse_file
            (cw::platform::filesystem::get_file_path(filename));
            data.release();

        }

        return *this;
    }

    json& from_string(const std::string& json_string){
        auto& raw_json = data.acquire();
        raw_json = jsoncons::json::parse_string(json_string);
        data.release();
        return *this;
    }

    bool has(const std::string& member) {
        bool has_member = data.acquire().has_member(member);

        data.release();
        return has_member;
    }


    jsoncons::json data;

};// class json