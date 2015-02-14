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

    T& acquire(){
        property_mutex.lock();
        return property_value;
    }
    
    void release(){
        property_mutex.unlock();
    }

/*    operator T(){
        property_mutex.lock();
        T property_value = property_value;
        property_mutex.unlock();

        return property_value;
    }*/

    void operator=(T& other){
        std::lock_guard<std::mutex> lock(property_mutex);
        property_value = other;
    }

private:
    std::mutex property_mutex;
    T property_value;
};// class mutexed_property
