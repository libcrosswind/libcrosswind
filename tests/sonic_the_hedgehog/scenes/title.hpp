#pragma once 

#include <memory>

#include <glm/glm.hpp>

#include <crosswind/interface/core.hpp>
#include <crosswind/interface/composition/scene.hpp>
#include <crosswind/implementation/composition/camera.hpp>

#include <characters/title/sega_logo.hpp>
#include <characters/title/team_logo.hpp>

#include <characters/title/title_background.hpp>
//#include <characters/title/title_logo.hpp>


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
	    auto title_background = this->create_actor<game::characters::title::title_background>();

//	    auto title_logo       = this->create_actor<game::characters::title::logo>();


	    add_actor("sega_logo", sega_logo);
	    add_actor("team_logo", team_logo);

	    add_actor("title_background", title_background);
	  //  add_actor("title_logo", title_logo);


	    for(auto& actor: actors){
		    actor.second->init();
	    }

	    sega_sound_ongoing  = false;
	    title_sound_ongoing = false;
	    sega_logo_duration  = 8.0f;
	    team_logo_duration  = 8.0f;
	    time_count = 0.0f;

	    core->video->window->set_clear_color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		get_actor("sega_logo")->set_alpha(0.0f);
	    get_actor("team_logo")->set_alpha(0.0f);
	    get_actor("title_background")->set_alpha(1.0f);

	    phase = scene_phase::sega_logo;
    }

    virtual void deinit(){

    }

	void draw_sega_logo(){

		if(time_count <= sega_logo_duration){

			if(time_count <= 2.0f){
				float alpha_blending = glm::sin(glm::radians(time_count / 2.0f * 90.0f));
				get_actor("sega_logo")->set_alpha(alpha_blending);
			} else if(!sega_sound_ongoing) {
				sega_sound_ongoing = true;
				core->mixer->play_music("logo_bgm", 0);
			} else if(time_count >= 6.0f && time_count <= 8.0f){

				const float time_range = 2.0f - (8.0f - time_count);

				float alpha_blending = glm::sin(glm::radians((time_range / 2.0f * 90.0f) + 90.0f));
				get_actor("sega_logo")->set_alpha(alpha_blending);
				core->video->window->set_clear_color(glm::vec4(alpha_blending, alpha_blending, alpha_blending, 1.0f));
			}

		} else {
			time_count = 0.0f;
			remove_actor("sega_logo");
			phase = scene_phase::team_logo;
		}

	}

	void draw_team_logo(){

		if(time_count <= sega_logo_duration){

			float alpha_blending = glm::sin(glm::radians(time_count / sega_logo_duration * 180.0f));
			get_actor("team_logo")->set_alpha(alpha_blending);

		} else {
			time_count = 0.0f;
			remove_actor("team_logo");
			phase = scene_phase::title_logo;
		}

	}

	void draw_title(){

		if(time_count <= 2.0f) {
	//		float alpha_blending = glm::sin(glm::radians(time_count / 2.0f * 90.0f));
	//		this->get_actor("title_background")->set_alpha(alpha_blending);
		} else if(!title_sound_ongoing) {
			title_sound_ongoing = true;
			core->mixer->play_music("title_bgm", 0);
		} else if(time_count >= 3.0f){

		} else {
			time_count = 0.0f;
		}

	}

	virtual void logic(const float& delta){

		time_count += delta;

		switch(phase){
/*			case scene_phase::sega_logo:
				draw_sega_logo();
				break;

			case scene_phase::team_logo:
				draw_team_logo();
				break;*/

			case scene_phase::title_logo:
//				draw_title();
				break;
		}

		if(core->input->is_key_down("Right")){
			get_camera("main_camera")->set_position(glm::vec3(get_camera("main_camera")->get_position().x + 10, 0.0f, 0.0f));
		} else if(core->input->is_key_down("Left")){
			get_camera("main_camera")->set_position(glm::vec3(get_camera("main_camera")->get_position().x - 10, 0.0f, 0.0f));
		}

		draw_title();

	}

private:
	float time_count;
	bool sega_sound_ongoing;
	bool title_sound_ongoing;
	float sega_logo_duration;
	float team_logo_duration;
	float intro_duration;

	int phase;

	enum scene_phase{
		sega_logo = 0,
		team_logo,
		title_logo
	};

};// class title