#pragma once 

#include <memory>

#include <glm/glm.hpp>

#include <crosswind/composition/core.hpp>
#include <crosswind/composition/scene.hpp>
#include <crosswind/composition/camera.hpp>
#include <crosswind/composition/core.hpp>

#include <crosswind/graphical/object/sprite.hpp>
#include <crosswind/graphical/object/model.hpp>

#include <sega_logo.hpp>
/*#include <characters/title/team_logo.hpp>

#include <characters/title/title_background.hpp>*/


namespace game {
	namespace scenes {

		class title;

	}// namespace zones
}// namespace game

namespace cw {
	namespace composition {
		class tilemap;
		class sprite_set;
		class physical;
	}
}

class game::scenes::title : public cw::composition::scene, public std::enable_shared_from_this<title> {
public:
	title();
	~title();

	virtual void init();

	virtual void deinit();

	void reset();

	/*void draw_sega_logo() {

		if (time_count <= sega_logo_duration) {

			if (time_count <= 2.0f) {
				float alpha_blending = glm::sin(glm::radians(time_count / 2.0f * 90.0f));
				get_actor("sega_logo")->set_alpha(alpha_blending);
			}
			else if (!sega_sound_ongoing) {
				sega_sound_ongoing = true;
				core->mixer->play_music("logo_bgm", 0);
			}
			else if (time_count >= 6.0f && time_count <= 8.0f) {

				const float time_range = 2.0f - (8.0f - time_count);

				float alpha_blending = glm::sin(glm::radians((time_range / 2.0f * 90.0f) + 90.0f));
				get_actor("sega_logo")->set_alpha(alpha_blending);
				core->video->window->set_clear_color(glm::vec4(alpha_blending, alpha_blending, alpha_blending, 1.0f));
			}

		}
		else {
			time_count = 0.0f;
			phase = scene_phase::team_logo;
		}

	}

	void draw_team_logo() {

		if (time_count <= sega_logo_duration) {

			float alpha_blending = glm::sin(glm::radians(time_count / sega_logo_duration * 180.0f));
			get_actor("team_logo")->set_alpha(alpha_blending);

		}
		else {
			time_count = 0.0f;
			phase = scene_phase::title_logo;
		}

	}*/

	void draw_title();

	virtual void logic(const float& delta);
	virtual void draw(std::shared_ptr<cw::graphical::opengl::renderer> renderer);

	std::vector<std::shared_ptr<cw::composition::physical> > walls;

private:
	std::shared_ptr<cw::graphical::object::model> title_model;
	std::shared_ptr<cw::composition::tilemap> tilemap;
	std::shared_ptr<cw::composition::sprite_set> terra;


	float time_count;
	bool sega_sound_ongoing;
	bool title_sound_ongoing;
	float sega_logo_duration;
	float team_logo_duration;
	float intro_duration;

	int phase;

	enum scene_phase {
		sega_logo = 0,
		team_logo,
		title_logo
	};

};// class title