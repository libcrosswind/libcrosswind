#pragma once

#include <atomic>
#include <functional>

namespace cw{
namespace core{
namespace concurrent{

    template<class T>
    class atomical_property;            

}// namespace concurrent
}// namespace core
}// namespace cw

template<class T>
class cw::core::concurrent::atomical_property{
public:
    atomical_property(){
        property_value.store(0);
        init();
    }

    atomical_property(const T& value){
        property_value.store(value);
    }

    operator T(){
        return this->get();
    }

    void operator=(T other){
        this->set(other);
    }

    operator +(const T& other){
        return this->get() + other;
    }

    operator -(const T& other){
        return this->get() - other;
    }

    std::function<void(const T&)> set;
    std::function<T(void)> get;

protected:
    void init() {
        
        set = [this](const T& value){
            this->property_value.store(value);
        };

        get = [this](){
            return this->property_value.load();
        };

    }

    std::atomic<T> property_value;
};//class atomical_property
