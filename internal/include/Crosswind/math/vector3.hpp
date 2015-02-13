#pragma once 

#include <Crosswind/concurrency/atomical_property.hpp>

namespace cw{
    namespace math{
        template<typename T>
        class vector3{
            vector3(T x_component, T y_component, T z_component){
                x = x_component;
                y = y_component;
                z = z_component;
            }

            atomical_property<T> x;
            atomical_property<T> y;
            atomical_property<T> z;
        };

    }
}