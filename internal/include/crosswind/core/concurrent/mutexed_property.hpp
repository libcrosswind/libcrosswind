#pragma once

#include <mutex>
#include <crosswind/core/concurrent/detail/property_interface.hpp>

namespace cw{
namespace core{
namespace concurrent{

    template<class T>
    class mutexed_property;

}// namespace concurrent
}// namespace core
}// namespace cw

template<class T>
class cw::core::concurrent::mutexed_property: public detail::property_interface<T>{
public:
    mutexed_property(){
        property_value = T();
    }

    mutexed_property(const T& value){
        property_value = value;
    }

    T& acquire(){
        property_mutex.lock();
        return property_value;
    }

    void release(){
        property_mutex.unlock();
    }

protected:
    void init() override{

        this->set = [this](const T& value){
            auto& local_value = this->acquire();
            local_value = value;
            this->release();
        };

        this->get = [this](){
            auto& local_value = this->acquire();
            T value = local_value;
            this->release();

            return value;
        };

    }

private:
    std::mutex property_mutex;
    T property_value;
};// class mutexed_property
