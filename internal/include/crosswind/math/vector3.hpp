#pragma once 

#include <LinearMath/btVector3.h>

namespace cw{
namespace math{

    template<class T>
    class vector3;

}// namespace math
}// namespace cw


template<class T>
class cw::math::vector3: public btVector3{

};// class vector3