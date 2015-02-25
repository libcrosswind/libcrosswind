#pragma once

#include <atomic>

#include <crosswind/core/concurrent/detail/property_interface.hpp>

namespace cw{
namespace core{
namespace concurrent{

    template<class T>
    class atomical_property;            

}// namespace concurrent
}// namespace core
}// namespace cw



template<class T>
class cw::core::concurrent::atomical_property: public detail::property_interface<T>{
public:
    atomical_property(): detail::property_interface<T>(){
        property_value.store(0);
        this->init();
    }

    atomical_property(const T& value): detail::property_interface<T>(value){
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
};//class atomical_property
