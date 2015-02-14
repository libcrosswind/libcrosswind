#pragma once

#include <mutex>

namespace cw{
namespace core{
namespace concurrent{

    template<class T>
    class mutexed_property;

}// namespace concurrent
}// namespace core
}// namespace cw

template<class T>
class cw::core::concurrent::mutexed_property{
public:
    mutexed_property(){
        property_value = T();
    }
    template<typename ... Args>
    mutexed_property(Args... args){
        property_value = T(args...);
    }

    T& acquire(){
        property_mutex.lock();
        return property_value;
    }
    
    void release(){
        property_mutex.unlock();
    }

    operator T(){
    	auto& value = this->acquire();
    	T result = value;
    	this->release();

    	return result;
    }

    void operator=(const T& other){
    	auto& value = this->acquire();

        value = other;

        this->release();
    }

private:
    std::mutex property_mutex;
    T property_value;
};// class mutexed_property
