#pragma once

#include <glm/glm.hpp>

#include <crosswind/composition/sprite_set.hpp>
#include <crosswind/geometry/rectangle.hpp>

namespace game {
	namespace scenes {
		class gameplay;
	}
	namespace characters {
		class base;
	}// namespace characters
}// namespace game

namespace cw {
	namespace composition {
		class core;
	}
}

class game::characters::base :
	public cw::composition::sprite_set {

public:

	base(std::shared_ptr<cw::composition::core> core, const std::string& path);

	void set_position(const glm::vec2& new_position);
	glm::vec2 get_position();

	std::shared_ptr<cw::graphical::object::sprite> current_sprite;

protected:
	
	glm::vec2 position;

	cw::geometry::rectangle bbox;
};