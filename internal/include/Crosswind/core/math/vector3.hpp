#pragma once 

#include <crosswind/core/concurrent/atomical_property.hpp>

namespace cw{
namespace core{
namespace math{

    template<class T>
    class vector3;

}// namespace math
}// namespace core
}// namespace cw


template<class T>
class cw::core::math::vector3{
public:
    vector3(T x_component, T y_component, T z_component){
        x = x_component;
        y = y_component;
        z = z_component;
    }

    concurrent::atomical_property<T> x;
    concurrent::atomical_property<T> y;
    concurrent::atomical_property<T> z;
};// class vector3