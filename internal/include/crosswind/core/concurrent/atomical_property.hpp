#pragma once

#include <atomic>

namespace cw{
namespace core{
namespace concurrent{

    template<class T>
    class atomical_property;            

}// namespace concurrent
}// namespace core
}// namespace cw

template<class T>
class cw::core::concurrent::atomical_property: public detail::property<T>{
public:
    atomical_property(){
        property_value.store(0);
    }
/*
    void assign(T value){
        property_value.store(value);
    }

    T retrieve(){
        property_value.load();
    }
*/
    operator T(){
        return property_value.load();
    }

    operator +(const T& other){
        return property_value.load() + other;
    }

    operator -(const T& other){
        return property_value.load() - other;
    }

    void operator=(T other){
        property_value.store(other);
    }

private:
    std::atomic<T> property_value;
};//class atomical_property
