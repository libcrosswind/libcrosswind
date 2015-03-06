#pragma once

#include <atomic>

#include <crosswind/concurrent/detail/property_interface.hpp>

namespace cw{
namespace concurrent{

    template<class T>
    class atomic_property;            

}// namespace concurrent
}// namespace cw

template<class T>
class cw::concurrent::atomic_property: public cw::concurrent::detail::property_interface<T>{
public:
    atomic_property(): detail::property_interface<T>(){
        property_value.store(0);
        this->init();
    }

    atomic_property(const T& value): detail::property_interface<T>(value){
        property_value.store(value);
        this->init();
    }

protected:
    void init() override {
        
        this->set = [this](const T& value){
            this->property_value.store(value);
        };

        this->get = [this](){
            return this->property_value.load();
        };

    }

    std::atomic<T> property_value;
};//class atomic_property
