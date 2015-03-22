#pragma once

#include <memory>
#include <string>
#include <jsoncons/json.hpp>

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

        data = jsoncons::json::parse_file(platform::filesystem::get_file_path(filename));

        return *this;
    }

    json& from_string(const std::string& json_string){

        data = jsoncons::json::parse_string(platform::filesystem::get_file_path(json_string));
        return *this;
    }

    bool has(const std::string& member) {
        return data.has_member(member);
    }


    jsoncons::json data;

};// class json