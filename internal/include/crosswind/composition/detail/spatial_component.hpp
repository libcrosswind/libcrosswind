#pragma once

#include <glm/glm.hpp>

namespace cw{
namespace composition{
namespace detail{

class spatial_component{
public:
	spatial_component(): origin(0.0f, 0.0f, 0.0f), size(1.0f, 1.0f, 1.0f), alpha(1.0f){

	}

	virtual void set_origin(const glm::vec3& f_origin) {
		origin = f_origin;
	}

	virtual glm::vec3 get_origin(){
		return origin;
	}

	virtual void set_size(const glm::vec3& f_size){
		size = f_size;
	}

	virtual glm::vec3 get_size(){
		return size;
	}

	virtual void set_alpha(const float& f_alpha){
		alpha = f_alpha;
	}

	virtual float get_alpha(){
		return alpha;
	}


protected:
	glm::vec3 origin;
	glm::vec3 size;
	float alpha;

};// class spatial_component

}// namespace detail
}// namespace composition
}// namespace cw

