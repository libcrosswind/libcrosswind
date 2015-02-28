#pragma once

#include <mutex>
#include <crosswind/concurrent/detail/property_interface.hpp>

namespace cw{
namespace concurrent{

    template<class T>
    class mutex_property;

}// namespace concurrent
}// namespace cw

template<class T>
class cw::concurrent::mutex_property: public cw::concurrent::detail::property_interface<T>{
public:
    mutex_property(){
        property_value = T();
        this->init();
    }

    mutex_property(const T& value){
        property_value = value;
        this->init();
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
};// class mutex_property
