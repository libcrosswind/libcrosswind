#pragma once

#include <map>
#include <string>
//#include <crosswind/physics/detail/rigid_body.hpp>
//#include <crosswind/physics/kinematic_character.hpp>
#include <crosswind/graphical/object/sprite.hpp>
#include <crosswind/graphical/object/sprite_animation.hpp>
#include <crosswind/graphical/object/model.hpp>

namespace cw{
namespace graphical{
namespace object{

	class model;

}// namespace object
}// namespace graphical
}// namespace cw


class cw::graphical::object::model{
public:
	model();

	void change_animation(const std::string& new_animation, const bool& x_orientation = true);

	void update(const float& delta);

	std::shared_ptr<cw::graphical::object::sprite> get_sprite();

	std::map<std::string, std::shared_ptr<cw::graphical::object::sprite> >& get_render_sprite_list();

	void set_animations(std::map<std::string, std::shared_ptr<cw::graphical::object::sprite_animation> >& new_animations);

	std::map<std::string, std::shared_ptr<cw::graphical::object::sprite_animation> >& get_animations();

	void set_origin(const glm::vec3& new_origin);

	glm::vec3 get_origin();

	void set_size(const glm::vec3& new_size);

	glm::vec3 get_size();

protected:
	glm::vec3 origin;
	glm::vec3 size;
	float delta_count;

	std::map<std::string, std::shared_ptr<cw::graphical::object::sprite> > render_sprite_list;
	std::map<std::string, std::shared_ptr<cw::graphical::object::sprite_animation> > animations;

};// class model