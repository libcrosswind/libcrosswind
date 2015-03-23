#pragma once

#include <map>
#include <memory>
#include <string>

#include <glm/glm.hpp>

#include <crosswind/interface/graphical/detail/sprite.hpp>
#include <crosswind/interface/graphical/detail/sprite_batch.hpp>

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

	virtual void upload(const std::map<std::string, std::shared_ptr<sprite> >& sprite_map) = 0;

    virtual void draw() = 0;
	virtual void end() = 0;

protected:
	std::shared_ptr<sprite_batch> sprite_batch;

};// class renderer