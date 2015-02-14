#pragma once

#include <memory>
#include <string>
#include <jsoncons/json.hpp>

namespace cw{
namespace core{
namespace javascript{

    class json;

}// namespace javascript
}// namespace core
}// namespace cw

class cw::core::javascript::json{
public:
    json(){
        raw_json = std::shared_ptr<jsoncons::json>(new jsoncons::json());
    }

    json& from_file(std::string filename){
        (*raw_json) = jsoncons::json::parse_file(filename);
        return *this;
    }

    json& from_string(std::string json_string){
        (*raw_json) = jsoncons::json::parse_string(json_string);
        return *this;
    }

    template<typename Type>
    void set(std::string key, Type value){ //TODO, in order to make this multithreaded we will need to restrict some functions.

    }


    jsoncons::json& operator[](std::string key){

        if(!this->has(key)){
            (*raw_json)[key] = jsoncons::json();
        }

        return (*raw_json)[key];
    }


    bool has(std::string key){
        return (*raw_json).has_member(key);
    }

    jsoncons::json& data() //TODO multithraeding will require to return a copy, not a reference, unless, stated.
    {
        return (*raw_json);
    }

private:
    std::shared_ptr<jsoncons::json> raw_json;

};