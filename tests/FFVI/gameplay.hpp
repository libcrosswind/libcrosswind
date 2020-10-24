#pragma once 

#include <memory>

#include <glm/glm.hpp>

#include <crosswind/composition/core.hpp>
#include <crosswind/composition/scene.hpp>
#include <crosswind/composition/camera.hpp>
#include <crosswind/composition/core.hpp>

#include <crosswind/geometry/rectangle.hpp>

#include <crosswind/graphical/object/sprite.hpp>
#include <crosswind/graphical/object/model.hpp>

#include <sega_logo.hpp>
/*#include <characters/title/team_logo.hpp>

#include <characters/title/title_background.hpp>*/


namespace game {
	namespace scenes {

		class gameplay;

	}// namespace zones
}// namespace game

namespace cw {
	namespace composition {
		class tilemap;
		class sprite_set;
		//class physical;
	}
}

class game::scenes::gameplay : public cw::composition::scene, 
							   public std::enable_shared_from_this<gameplay> {
public:
	gameplay();
	~gameplay();

	virtual void init();

	virtual void deinit();

	virtual void logic(const float& delta);
	virtual void draw(std::shared_ptr<cw::graphical::opengl::renderer> renderer);

	std::vector<cw::geometry::rectangle > walls;
	std::map<std::string, cw::geometry::rectangle > doors;

private:
	std::shared_ptr<cw::graphical::object::model> title_model;
	std::shared_ptr<cw::composition::tilemap> tilemap;
	std::shared_ptr<cw::composition::sprite_set> terra;

};// class title