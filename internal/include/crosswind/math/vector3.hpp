#pragma once 

#include <LinearMath/btVector3.h>

namespace cw{
namespace math{

    class vector3;

}// namespace math
}// namespace cw


class cw::math::vector3: public btVector3{
public:
	vector3(double x, double y, double z): btVector3(x, y, z){
		
	}
};// class vector3