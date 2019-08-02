#pragma once

#include <memory>
#include <string>
#include <map>

#include "glm/glm.hpp"

#include "graphical/object/renderable.hpp"

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
namespace graphical{
namespace object{

class model : public renderable{
public:
	model();

	void change_animation(const std::string& new_animation);

	void update(const float& delta);

	void set_render_sprite(std::shared_ptr<sprite> sprite);

	virtual std::shared_ptr<object::sprite> get_render_sprite() override;

	void set_animations(const std::map<std::string, std::shared_ptr<sprite_animation> >& new_animations);

	std::map<std::string, std::shared_ptr<sprite_animation> >& get_animations();

	void set_origin(const glm::vec3& new_origin);

	glm::vec3 get_origin();

	void set_size(const glm::vec3& new_size);

	glm::vec3 get_size();

	std::map<std::string, int>  data;

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
