#pragma once 

#include <crosswind/core/concurrent/atomical_property.hpp>

namespace cw{
namespace core{
namespace math{

    template<class T>
    class clamp;

}// namespace math
}// namespace core
}// namespace cw


template<class T>
class cw::core::math::clamp{
public:
    clamp(T min_value, T max_value){
        minimum = min_value;
        maximum = max_value;
    }

    T operator()(T value){
        T result = value < minimum ? minimum : value;
        return result > maximum ? maximum : result;
    }

private:
    concurrent::atomical_property<T> minimum;
    concurrent::atomical_property<T> maximum;
};// class clamp


