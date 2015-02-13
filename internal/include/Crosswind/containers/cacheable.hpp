#pragma once
#include <Crosswind/concurrency/mutexed_map.hpp>

#include <memory>
#include <mutex>
#include <map>
#include <functional>

namespace cw{
	namespace containers{

		 	template<typename T>
		    class cacheable{ //implement timestamps.

		        void store(std::string resource_name, std::string path){
		            cache(resource_name, source(path));
		        }

                T load(std::string resource_name){
		            return cache(resource_name);
		        }

		        void swap(std::string resource_name, T data){
		            cache(resource_name, data);
		        }

		        void clear(){
		            cache.clear();
		        }

                void apply_manipulation(std::string name){
                    cache.apply(manipulations(name));
                }

                concurrency::mutexed_map<std::string, T> cache;
                concurrency::mutexed_map<std::string,
                        std::function<void(std::map<std::string, T>) > manipulations;

		        delegate<T, std::string> source;
		    };

	}
}