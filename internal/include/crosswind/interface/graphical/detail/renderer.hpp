#pragma once

#include <string>

#include <glm/glm.hpp>

namespace cw{
namespace interface{
namespace graphical{
namespace detail{

	class renderer;

}// namespace detail
}// namespace graphical
}// namespace interface
}// namespace cw

class cw::interface::graphical::detail::renderer{
public:
	renderer(){

	}

	virtual void begin() = 0;
	virtual void set_uniform_matrix(const std::string& uniform_matrix_name, const glm::mat4& value) = 0;

/*	void upload(std::shared_ptr<cw::simulation::model> model){
		sprite_batch->upload(model);
	}*/

    virtual void draw() = 0;
	virtual void end() = 0;

};// class renderer