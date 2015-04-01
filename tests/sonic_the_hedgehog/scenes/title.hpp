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
	    time_to_team = false;
	    time_to_intro = false;

	    time_count = 0.0f;

	    core->video->window->set_clear_color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		get_actor("sega_logo")->set_alpha(0.0f);
	    get_actor("team_logo")->set_alpha(0.0f);
    }

    virtual void deinit(){

    }

	virtual void logic(const float& delta){

		//Sega logo music is 2 seconds long + 2 seconds from the startup animation.
		if(time_count <= 2.0f){

			get_actor("sega_logo")->set_alpha(time_count/2.0f);

		} else if (time_count >= 6.0f && time_count <= 8.0f){

			const float blend_alpha = (8.0f - time_count) / 2.0f;
			get_actor("sega_logo")->set_alpha(blend_alpha);
			core->video->window->set_clear_color(glm::vec4(blend_alpha, blend_alpha, blend_alpha, 1.0f));

		} else if(time_count >= 10.0f && time_count <= 14.0f){

			const float blend_alpha = (4.0f - (14.0f - time_count)) / 4.0f;
			get_actor("team_logo")->set_alpha(blend_alpha);

		}

		if(time_count >=  2.0f && !time_to_team){
			time_to_team = true;
			core->mixer->play_music("logo_bgm", 0);
		} else if(time_count >= 10.0f && !time_to_intro){
			time_to_intro = true;
			remove_actor("sega_logo");
		} else {
			time_count+=delta;
		}

	}

private:
	float time_count;
	bool time_to_intro;
	bool time_to_team;

};// class title