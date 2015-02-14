#pragma once 

#include <functional>
#include <map>
#include <mutex>

namespace cw{
namespace core{
namespace concurrent{

	template<class T, class U>
	class mutexed_map;

}// namespace concurrent
}// namespace core
}// namespace cw

template<class T, class U>
class cw::core::concurrent::mutexed_map{
public:
	U operator()(T key){

        map_mutex.lock();
        U property_value = property_map[key];
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

    void apply(std::function<void(std::map<T, U>&)> method){
		std::lock_guard<std::mutex> lock(map_mutex);
    	method(property_map);
    }

private:
    std::mutex map_mutex;
    std::map<T, U> property_map;

};// class mutexed_map
