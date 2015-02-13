#pragma once

#include <jsoncons/json.hpp>
#include <string>

namespace cw{
	namespace datatypes{
				class json{ //This is not multithreaded.

				public:
				    json(){
				        raw_json = std::shared_ptr<jsoncons::json>(new jsoncons::json());
				    }

				    auto& from_file(std::string filename){
				        raw_json = std::shared_ptr<jsoncons::json>(new jsoncons::json(jsoncons::json::parse_file(filename)));
				        return *this;
				    }

				    auto& from_string(std::string json_string){
				        raw_json = std::shared_ptr<jsoncons::json>(new jsoncons::json(jsoncons::json::parse_string(json_string)));
				        return *this;
				    }

				    template<typename Type>
				    void set(std::string key, Type value){ //TODO, in order to make this multithreaded we will need to restrict some functions.

				    }


				    auto& operator[](std::string key){

				        if(!this->has(key)){
				            (*raw_json)[key] = jsoncons::json();
				        }

				        return (*raw_json)[key];
				    }


				    bool has(std::string key){
				        return (*raw_json).has_member(key);
				    }

				    auto& data() //TODO multithraeding will require to return a copy, not a reference, unless, stated.
				    {
				        return (*raw_json);
				    }

				private:
				    std::shared_ptr<jsoncons::json> raw_json;

				};

		}

}