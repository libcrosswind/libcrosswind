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
        auto& raw_json = data.acquire();
        raw_json = jsoncons::json::parse_file(filename);
        data.release();
        return *this;
    }

    json& from_string(std::string json_string){
        auto& raw_json = data.acquire();
        raw_json = jsoncons::json::parse_string(json_string);
        data.release();
        return *this;
    }

    bool has(std::string member) {
        bool has_member = data.acquire().has_member(member);

        data.release();
        return has_member;
    }

    core::concurrent::mutexed_property<jsoncons::json> data;

};