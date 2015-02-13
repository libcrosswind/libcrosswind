#pragma once 

#include <Crosswind/concurrency/atomical_property.hpp>

namespace cw{
    namespace math{
        
        template<typename T>
        class vector2{
            vector2(T x_component, T y_component){
                x = x_component;
                y = y_component;
            }

            atomical_property<T> x;
            atomical_property<T> y;
        };

    }
}