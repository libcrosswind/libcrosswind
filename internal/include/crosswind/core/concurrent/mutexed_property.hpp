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
        return this->get();
    }

    void operator=(const T& other){
        this->set(other);
    }

    std::function<void(const T&)> set;
    std::function<T(void)> get;

protected:
    void init(){

        set = [this](const T& value){
            auto& local_value = this->acquire();
            local_value = value;
            this->release();
        };

        get = [this](){
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
