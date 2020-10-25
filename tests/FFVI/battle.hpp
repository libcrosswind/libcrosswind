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

		class battle;

	}// namespace zones
}// namespace game

namespace cw {
	namespace composition {
		class tilemap;
		class sprite_set;
		//class physical;
	}
}

namespace cw {
	namespace graphical {
		namespace object {
			class sprite;
		}
	}
}

namespace game {
	namespace characters {
		class base;
	}
}

class game::scenes::battle : public cw::composition::scene, public std::enable_shared_from_this<battle> {
public:
	battle(const std::string& battle_back_path, 
		   std::vector<std::shared_ptr<game::characters::base> > player_party,
		   std::vector<std::shared_ptr<game::characters::base> > enemy_party);

	~battle();

	virtual void init();

	virtual void deinit();

	virtual void logic(const float& delta);
	virtual void draw(std::shared_ptr<cw::graphical::opengl::renderer> renderer);

	enum class battle_status {
		player_input,
		player_turn
	};

private:
	std::string battle_back_path;
	std::string ui_path;
	std::shared_ptr<cw::graphical::object::sprite> battle_back;
	std::vector<std::shared_ptr<game::characters::base> > player_party;
	std::vector<std::shared_ptr<game::characters::base> > enemy_party;

	std::shared_ptr<cw::graphical::object::sprite> window_background;
	std::shared_ptr<cw::graphical::object::sprite> window_foreground;

};// class title