#pragma once

#include <glm/glm.hpp>

//#include <crosswind/composition/core.hpp>
#include <crosswind/composition/sprite_set.hpp>

namespace game {
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

class game::characters::title::terra : public cw::composition::sprite_set {
public:

	terra(std::shared_ptr<cw::composition::core> core, const std::string& path);

	void logic(const float& dt);
	void draw(std::shared_ptr<cw::graphical::opengl::renderer> renderer);

private:
	int sprite_index;
	float animation_time;
	std::shared_ptr<cw::graphical::object::sprite> current_sprite;
};