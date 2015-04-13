#pragma once

#include <string>

#include "jsoncons/json.hpp"

namespace cw{
namespace modules{
namespace javascript{

class json{
public:
    json(){
    }

    auto& from_file(const std::string& filename){

        data = jsoncons::json::parse_file(filename);

        return *this;
    }

    auto& from_string(const std::string& json_string){

        data = jsoncons::json::parse_string(json_string);
        return *this;
    }

    bool has(const std::string& member) {
        return data.has_member(member);
    }


    jsoncons::json data;

};// class json

}// namespace javascript
}// namespace modules
}// namespace cw