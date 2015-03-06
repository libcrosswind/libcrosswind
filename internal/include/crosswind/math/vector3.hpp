#pragma once 

#include <LinearMath/btVector3.h>

namespace cw{
namespace math{

    class vector3;

}// namespace math
}// namespace cw


class cw::math::vector3: public btVector3{
public:
	vector3(): btVector3(0.0f, 0.0f, 0.0f){

	}
	
	vector3(float x, float y, float z): btVector3(x, y, z){
		
	}
};// class vector3