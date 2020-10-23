#pragma once

#include <glm/glm.hpp>

//#include <crosswind/composition/core.hpp>
#include <crosswind/composition/sprite_set.hpp>
#include <crosswind/composition/physical.hpp>
#include <crosswind/geometry/rectangle.hpp>

namespace game {
	namespace scenes {
		class title;
	}
	namespace characters {
		namespace title {

			class terra;

		}// namespace title
	}// namespace characters
}// namespace game


namespace cw {
	namespace composition {
		class core;
	}
}

class game::characters::title::terra : 
	public cw::composition::sprite_set
	/*public cw::composition::physical */{
	typedef std::map<std::string, std::vector<std::pair<glm::vec3, glm::vec3> > > actor_collision_map;
	typedef std::map<std::string, actor_collision_map> scene_collision_map;

public:

	terra(std::shared_ptr<cw::composition::core> core, 
		  std::shared_ptr<game::scenes::title> title,
		  const std::string& path);

	std::string get_collision_map(const std::string& actor_a);

	void find_collisions();
	void logic(const float& dt);
	void draw(std::shared_ptr<cw::graphical::opengl::renderer> renderer);

	void set_position(const glm::vec2& new_position);
	glm::vec2 get_position();

private:

	bool can_move_right;
	bool can_move_left;
	bool can_move_up;
	bool can_move_down;

	glm::vec2 position;

	cw::geometry::rectangle bbox;

	//scene_collision_map collisions;

	std::map<std::string, std::string> collisions;

	
	std::shared_ptr<game::scenes::title> title;

	std::shared_ptr<cw::composition::core> core;
	int sprite_index;
	float animation_time;
	std::shared_ptr<cw::graphical::object::sprite> current_sprite;
};