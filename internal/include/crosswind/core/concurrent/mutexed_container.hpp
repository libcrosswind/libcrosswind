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

    template<class T>
    class mutexed_vector;

    template<class T>
    class mutexed_forward_list;

    template<class T, class U>
    class mutexed_map;

}// namespace concurrent
}// namespace core
}// namespace cw

template<class T>
class cw::core::concurrent::mutexed_container{
public:
    mutexed_container(){
/*        iterator = [this](std::function<void(T&)>& iterative){
            auto& container = data.acquire();

            for(auto& item: container){
                if(iterative(item) != 0)
                    break;
            }

            data.release();
        };*/
    }

    template<typename U>
	auto operator()(const U& key){

        auto& container = data.acquire();
        auto value = container[key];
        data.release();

        return value;
    }

    template<typename U, typename V>
    void operator()(const U& key, const V& value){
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

//    std::function<void(T&)> iterator;

    mutexed_property<T> data;
};// class mutexed_map

#include <vector>

template<class T>
class cw::core::concurrent::mutexed_vector: public cw::core::concurrent::mutexed_container<std::vector<T> >{
public:
    void push_back(const T& element){
        auto& container = this->data.acquire();

        container.push_back(element);

        this->data.release();
    }
};

#include <forward_list>

template<class T>
class cw::core::concurrent::mutexed_forward_list: public mutexed_container<std::forward_list<T> >{
    
};

#include <map>
template<class T, class U>
class cw::core::concurrent::mutexed_map: public mutexed_container<std::map<T, U> >{

};

