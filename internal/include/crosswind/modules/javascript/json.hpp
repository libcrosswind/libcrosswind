#pragma once

#include <string>
#include <fstream>

#include "jsoncons/json.hpp"

namespace cw{
namespace modules{
namespace javascript{

class json{
public:
    json(){
    }

    auto& from_file(const std::string& filename){

        std::ifstream is(filename);

        data = jsoncons::json::parse(is);

        return *this;
    }

    auto& from_string(const std::string& json_string){

        data = jsoncons::json::parse(json_string);
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