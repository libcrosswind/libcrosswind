#pragma once

#include <memory>
#include <string>
#include <jsoncons/json.hpp>

#include <crosswind/core/concurrent/mutexed_property.hpp>

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
    }

    json& from_file(std::string filename){
        data = jsoncons::json::parse_file(filename);
        return *this;
    }

    json& from_string(std::string json_string){
        data = jsoncons::json::parse_string(json_string);
        return *this;
    }

/*    template<typename Type>
    void set(std::string key, Type value){ //TODO, in order to make this multithreaded we will need to restrict some functions.

    }
*/

/*    jsoncons::json& operator[](std::string key){

        if(!this->has(key)){
            data.acquire()[key] = jsoncons::json();
            data.release();
        }


        return (*raw_json)[key];
    }*/


    bool has(std::string member){
        bool has_member = data.acquire().has_member(member);
        
        data.release();
        return has_member;
    }

    core::concurrent::mutexed_property<jsoncons::json> data;

};