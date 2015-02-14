#pragma once 

#include <functional>
#include <map>
#include <mutex>

#include <crosswind/core/concurrent/mutexed_property.hpp>

namespace cw{
namespace core{
namespace concurrent{

	template<class T>
	class mutexed_container;

}// namespace concurrent
}// namespace core
}// namespace cw

template<class T>
class cw::core::concurrent::mutexed_container{
public:
    template<typename U>
	auto operator()(U key){

        auto& container = data.acquire();
        auto value = container[key];
        data.release();

        return value;
    }

    template<typename U, typename V>
    void operator()(U key, V value){
        auto& container = data.acquire();
    	container[key] = value;
        data.release();
    }

    void clear(){
        auto& container = data.acquire();

    	container.clear();

        data.release();
    }

    void apply(std::function<void(T&)> method){
        auto& container = data.acquire();

    	method(container);

        data.release();
    }

    mutexed_property<T> data;
};// class mutexed_map
