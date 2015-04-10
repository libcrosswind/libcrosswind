#pragma once

#include <map>
#include <string>

#include <glm/glm.hpp>

#include <crosswind/interface/graphical/detail/sprite.hpp>
#include <crosswind/interface/graphical/object/sprite_animation.hpp>

namespace cw{
namespace interface{
namespace graphical{
namespace object{

	class model;

}// namespace object
}// namespace graphical
}// namespace interface
}// namespace cw


class cw::interface::graphical::object::model{
public:
	model(): origin(0.0f, 0.0f, 0.0f), delta_count(0.0f){
	}

	virtual void change_animation(const std::string& new_animation) = 0;
	virtual void update(const float& delta) = 0;

	virtual void set_render_sprite(std::shared_ptr<detail::sprite> sprite) = 0;
	virtual std::shared_ptr<detail::sprite> get_render_sprite() = 0;
	virtual void set_animations(std::map<std::string, std::shared_ptr<sprite_animation> >& new_animations) = 0;
	virtual std::map<std::string, std::shared_ptr<sprite_animation> >& get_animations() = 0;

	virtual void set_origin(const glm::vec3& new_origin) = 0;
	virtual glm::vec3 get_origin() = 0;

	virtual void set_size(const glm::vec3& new_size) = 0;
	virtual glm::vec3 get_size() = 0;

	std::map<std::string, int>  data;

protected:
	glm::vec3 origin;
	glm::vec3 size;
	float delta_count;

	std::shared_ptr<detail::sprite> render_sprite;
	std::map<std::string, std::shared_ptr<sprite_animation> > animations;
};// class model