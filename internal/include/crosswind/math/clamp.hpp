#pragma once 

#include <crosswind/concurrent/atomic_property.hpp>

namespace cw{
namespace math{

    template<class T>
    class clamp;

}// namespace math
}// namespace cw


template<class T>
class cw::math::clamp{
public:
    clamp(T min_value, T max_value){
        minimum.set(min_value);
        maximum.set(max_value);
    }

    T operator()(T value){
        T result = value < minimum.get() ? minimum.get() : value;
        return result > maximum.get() ? maximum.get() : result;
    }

private:
    concurrent::atomic_property<T> minimum;
    concurrent::atomic_property<T> maximum;
};// class clamp


