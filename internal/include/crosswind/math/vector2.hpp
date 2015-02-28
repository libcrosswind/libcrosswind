#pragma once 

#include <crosswind/concurrent/atomic_property.hpp>

namespace cw{
namespace math{

    template<class T>
    class vector2;

}// namespace math
}// namespace cw


template<class T>
class cw::math::vector2{
public:
    vector2(T x_component, T y_component){
        x = x_component;
        y = y_component;
    }

    concurrent::atomic_property<T> x;
    concurrent::atomic_property<T> y;
};// class vector2

 