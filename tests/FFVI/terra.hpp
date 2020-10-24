#pragma once

#include <glm/glm.hpp>

//#include <crosswind/composition/core.hpp>
#include <crosswind/composition/sprite_set.hpp>
#include <crosswind/composition/physical.hpp>
#include <crosswind/geometry/rectangle.hpp>

#include "base.hpp"

namespace game {
	namespace scenes {
		class gameplay;
	}
	namespace characters {
		class terra;
	}// namespace characters
}// namespace game


namespace cw {
	namespace composition {
		class core;
	}
}

class game::characters::terra : 
	public game::characters::base,
	public std::enable_shared_from_this<terra>
	/*public cw::composition::physical */{
	typedef std::map<std::string, std::vector<std::pair<glm::vec3, glm::vec3> > > actor_collision_map;
	typedef std::map<std::string, actor_collision_map> scene_collision_map;

public:

	terra(std::shared_ptr<cw::composition::core> core, 
		  std::shared_ptr<game::scenes::gameplay> title,
		  const std::string& path);

	std::string get_collision_map(const std::string& actor_a);

	void find_collisions();
	void logic(const float& dt);
	void draw(std::shared_ptr<cw::graphical::opengl::renderer> renderer);

	void set_position(const glm::vec2& new_position);
	glm::vec2 get_position();

private:
	bool battle_trigger;

	bool idle_right;
	bool idle_left;
	bool idle_up;
	bool idle_down;

	glm::vec2 position;

	cw::geometry::rectangle bbox;

	//scene_collision_map collisions;

	std::map<std::string, std::string> collisions;

	
	std::shared_ptr<game::scenes::gameplay> gameplay;

	std::shared_ptr<cw::composition::core> core;
	int sprite_index;
	float animation_time;
	enum walking_direction {
		up,
		down,
		left,
		right
	};

	walking_direction walking_direction_facing;
	std::map<std::string, float> animation_times;
	std::map<std::string, std::vector<std::shared_ptr<cw::graphical::object::sprite> > > animations;
};