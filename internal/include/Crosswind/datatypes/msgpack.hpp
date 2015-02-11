#pragma once

#include <msgpack.hpp>
#include <sstream>
#include <string>
#include <memory>
#include <iostream>


namespace cw{
	namespace datatypes{

			class messagepack{
			public:
		    	template<typename... Args>
				static std::shared_ptr<std::stringstream> encode(Args... args){

					auto ss = std::shared_ptr<std::stringstream>(new std::stringstream());

                    auto arguments = {args...};

					for(auto& arg : arguments ){
					    msgpack::pack(*ss, arg);
                    }

					return ss;
				}

				template<typename T>
				static T decode(std::string data){
					
				}

			};

	}
}