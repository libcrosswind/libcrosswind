#pragma once

#include <mutex>

template<typename T>
class mutexed_property{
public:
    T operator()(){

        property_mutex.lock();
        T property_value = property_value;
        property_mutex.unlock();

        return property_value;
    }

    void operator=(T other){
        std::lock_guard<std::mutex> lock(property_mutex);
        property_value = other;
    }

private:
    std::mutex property_mutex;
    T property_value;
};
