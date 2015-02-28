#pragma once 

#include <crosswind/core/concurrent/atomic_property.hpp>

namespace cw{
namespace math{

    template<class T>
    class vector3;

}// namespace math
}// namespace cw


template<class T>
class cw::math::vector3{
public:
    vector3(T x_component, T y_component, T z_component){
        x = x_component;
        y = y_component;
        z = z_component;
    }

    concurrent::atomic_property<T> x;
    concurrent::atomic_property<T> y;
    concurrent::atomic_property<T> z;
};// class vector3