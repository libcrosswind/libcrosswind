#pragma once 

#include <memory>
#include <mutex>
#include <map>
#include <functional>

namespace cw{
	namespace concurrency{
		
		template<typename T, typename U>
		class mutexed_map{

			U operator()(T key){ //TODO change to unique_ptr.

		        map_mutex.lock();
		        std::shared_ptr<U> property_value = property_map[key];
		        map_mutex.unlock();

		        return property_value;
		    }

		    void operator()(T key, U value){
		        std::lock_guard<std::mutex> lock(map_mutex);
		    	property_map[key] = value;
		    }

		    void clear(){
				std::lock_guard<std::mutex> lock(map_mutex);
		    	property_map.clear();
		    }

		    void apply(std::function<void(std::map<T, U>)> method){
				std::lock_guard<std::mutex> lock(map_mutex);
		    	method(&property_map);
		    }

		    std::mutex map_mutex;
		    std::map<T, U> property_map;

		};

	}
}