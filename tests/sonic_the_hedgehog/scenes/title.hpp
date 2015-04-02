#pragma once 

#include <memory>

#include <glm/glm.hpp>

#include <crosswind/interface/core.hpp>
#include <crosswind/interface/composition/scene.hpp>
#include <crosswind/implementation/composition/camera.hpp>

#include <characters/title/sega_logo.hpp>
#include <characters/title/team_logo.hpp>

//#include <characters/title/title_background.hpp>
//#include <characters/title/title_logo.hpp>
//#include <characters/title/title_animation.hpp>

namespace game{
namespace scenes{

    class title;

}// namespace zones
}// namespace game

class game::scenes::title : public cw::interface::composition::scene{
public:
	title(){

	}
	
    virtual void init(){

	    auto main_camera = std::make_shared<cw::implementation::composition::camera>(core->video->window->get_size());
	    set_camera("main_camera", main_camera);

	    core->mixer->load_music("logo_bgm", core->filesystem->get_file_path("logo_bgm.ogg"));
	    core->mixer->load_music("title_bgm", core->filesystem->get_file_path("title_bgm.ogg"));


	    auto sega_logo  = this->create_actor<characters::title::sega_logo>();
	    auto team_logo  = this->create_actor<characters::title::team_logo>();


//	    auto title_background = this->create_actor<game::characters::title::background>();
//	    auto title_logo       = this->create_actor<game::characters::title::logo>();
//	    auto title_animation  = this->create_actor<game::characters::title::sonic_animation>();

	    add_actor("sega_logo", sega_logo);
	    add_actor("team_logo", team_logo);

//	    add_actor("title_background", title_background);
//	    add_actor("title_logo", title_logo);
//	    add_actor("title_animation", title_animation);

	    for(auto& actor: actors){
		    actor.second->init();
	    }

	    sega_logo_duration = 8.0f;
	    team_logo_duration = 8.0f;
	    time_count = 0.0f;

	    core->video->window->set_clear_color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		get_actor("sega_logo")->set_alpha(0.0f);
	    get_actor("team_logo")->set_alpha(0.0f);

	    phase = scene_phase::sega_logo;
    }

    virtual void deinit(){

    }

	void draw_sega_logo(const float& delta){

		if(time_count <= sega_logo_duration){

			if(time_count <= 2.0f){
				float alpha_blending = glm::sin(time_count / 2.0f * 90.0f);
				get_actor("sega_logo")->set_alpha(alpha_blending);
			} else if(time_count == 2.0f) {
				core->mixer->play_music("logo_bgm", 0);
			} else if(time_count >= 6.0f && time_count <= 8.0f){
				float alpha_blending = glm::sin((time_count / 8.0f * 90.0f) + 90.0f);
				get_actor("sega_logo")->set_alpha(alpha_blending);
				core->video->window->set_clear_color(glm::vec4(alpha_blending, alpha_blending, alpha_blending, 1.0f));
			}

		} else {
			time_count = 0.0f;
			phase = scene_phase::team_logo;
		}

	}

	void draw_team_logo(const float& delta){

		if(time_count <= sega_logo_duration){

			float alpha_blending = glm::sin(time_count / sega_logo_duration * 180.0f);
			get_actor("team_logo")->set_alpha(alpha_blending);

		} else {
			time_count = 0.0f;
			phase = scene_phase::intro;
		}

	}

	void draw_intro(const float& delta){

	}

	virtual void logic(const float& delta){


		switch(phase){
			case scene_phase::sega_logo:
				draw_sega_logo(delta);
				break;

			case scene_phase::team_logo:
				draw_team_logo(delta);
				break;

			case scene_phase::intro:
				draw_intro(delta);
				break;
		}

	}

private:
	float time_count;
	float sega_logo_duration;
	float team_logo_duration;
	float intro_duration;

	int phase;

	enum scene_phase{
		sega_logo = 0,
		team_logo,
		intro
	};

};// class title