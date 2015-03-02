#pragma once 

#include <functional>
#include <map>
#include <mutex>

#include <crosswind/concurrent/mutex_property.hpp>

namespace cw{
namespace concurrent{

	template<class T>
	class mutex_container;

    template<class T>
    class mutex_vector;

    template<class T>
    class mutex_forward_list;

    template<class T, class U>
    class mutex_map;

}// namespace concurrent
}// namespace cw

template<class T>
class cw::concurrent::mutex_container{
public:
    mutex_container(){
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

    mutex_property<T> data;
};// class mutexed_map



#include <vector>

template<class T>
class cw::concurrent::mutex_vector: public cw::concurrent::mutex_container<std::vector<T> >{
public:
    template<typename U>
    void push_back(const U& element){
        push_back(is_pushable<std::vector<U> >{}, element);
    }

    template<typename U>
    void push_back(std::true_type, const U& element){
        auto& container = this->data.acquire();

        container.push_back(element);

        this->data.release();
    }

    template<typename U>
    void push_back( std::false_type, const U& element ) {

    }



private:
    template<typename U> struct is_pushable : public std::false_type {};
    template<typename A>
    struct is_pushable<std::vector<T, A> > : public std::true_type {};

};

#include <forward_list>

template<class T>
class cw::concurrent::mutex_forward_list: public cw::concurrent::mutex_container<std::forward_list<T> >{
    
};

#include <map>
template<class T, class U>
class cw::concurrent::mutex_map: public cw::concurrent::mutex_container<std::map<T, U> >{

};

