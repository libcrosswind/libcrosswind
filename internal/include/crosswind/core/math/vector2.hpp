#pragma once 

#include <crosswind/core/concurrent/atomical_property.hpp>

namespace cw{
namespace core{
namespace math{

    template<class T>
    class vector2;

}// namespace math
}// namespace core
}// namespace cw


template<class T>
class cw::core::math::vector2{
public:
    vector2(T x_component, T y_component){
        x = x_component;
        y = y_component;
    }

    concurrent::atomical_property<T> x;
    concurrent::atomical_property<T> y;
};// class vector2

 