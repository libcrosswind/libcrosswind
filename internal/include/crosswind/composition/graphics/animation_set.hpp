#pragma once

#include <memory>
#include <string>
#include <map>

#include "glm/glm.hpp"

#include "crosswind/graphical/object/renderable.hpp"

// forward declarations
namespace cw{
namespace composition{

    class core;

}// namespace composition
}// namespace cw

// forward declarations
namespace cw{
namespace graphical{
namespace object{

	class sprite;
	class sprite_animation;

}// namespace object
}// namespace graphical
}// namespace cw


namespace cw{
namespace composition{
namespace graphics{

class animation_set : public graphical::object::renderable{
public:
	animation_set(std::shared_ptr<composition::core>  core,
								const std::string& path);

	void set_origin(const glm::vec3& new_origin);

	glm::vec3 get_origin();

	void change_animation(const std::string& new_animation);

	void set_animations(const std::map<std::string, std::shared_ptr<sprite_animation> >& new_animations);

	void update(const float& delta);

private:
	void set_render_sprite(std::shared_ptr<sprite> sprite);

private:
	glm::vec3 origin;
	glm::vec3 size;
	float delta_count;

	std::shared_ptr<object::sprite> render_sprite;
	std::map<std::string, std::shared_ptr<sprite_animation> > animations;

};// class model

}// namespace object
}// namespace graphical
}// namespace cw
