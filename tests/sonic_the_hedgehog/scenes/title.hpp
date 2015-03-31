#pragma once 

#include <memory>

#include <crosswind/interface/core.hpp>
#include <crosswind/interface/composition/scene.hpp>
#include <crosswind/implementation/composition/camera.hpp>


#include <characters/title/logo.hpp>
#include <characters/title/sonic.hpp>
#include <characters/title/backgrond.hpp>


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


	    auto sega_logo        = this->create_actor<game::characters::title::logo>();
	    auto sonic_team_logo  = this->create_actor<game::characters::title::logo>();


	    auto title_animation  = this->create_actor<game::characters::title::sonic_animation>();
	    auto title_logo       = this->create_actor<game::characters::title::logo>();
	    auto title_background = this->create_actor<game::characters::title::background>();

	    add_actor("sega_logo", sega_logo);
	    add_actor("sonic_team_logo", sonic_team_logo);
	    add_actor("title_animation", title_animation);
	    add_actor("title_logo", title_logo);
	    add_actor("title_background", title_background);

	    for(auto& actor: actors){
		    actor.second->init();
	    }

    }

    virtual void deinit(){

    }

	virtual void logic(const float& dt){

		time_count+=dt;

		//Sega logo music is 2 seconds long + 2 seconds from the startup animation.

		if(time_count >= 60.0f * 2.0f){

		} else if(time_count >= 60.0f * 4.0f){

		}

/*		get_camera("current")->set_position(get_actor("sonic")->get_character("sonic")->get_origin());

		auto& sonic_map = get_collision_map("sonic");
		if(!sonic_map.empty()){
			if(sonic_map.find("sonic_monitor") != sonic_map.end() && get_actor("sonic")->conditions["rolling"]){
				std::dynamic_pointer_cast<game::items::monitor>(get_actor("sonic_monitor"))->destroy();
				this->core->mixer->play_effect("box_break");
				this->core->mixer->play_music("extra_life", 0);
			}
		}*/


	}

private:
	float time_count;

};// class title