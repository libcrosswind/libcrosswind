#pragma once 

#include <memory>

#include <crosswind/interface/core.hpp>
#include <crosswind/interface/composition/scene.hpp>
#include <crosswind/implementation/composition/camera.hpp>

#include <characters/sonic.hpp>
#include <characters/chunk.hpp>


namespace game{
namespace scenes{

    class green_hill_zone;

}// namespace zones
}// namespace game

class game::scenes::green_hill_zone : public cw::interface::composition::scene{
public:
	green_hill_zone(){

	}
	
    virtual void init(){
	    auto main_camera = std::make_shared<cw::implementation::composition::camera>(core->video->window->get_size());
	    set_camera("main_camera", main_camera);

	    auto actor = std::make_shared<game::characters::sonic>();

	    glm::vec3 origin(0.0f, 0.0f, 0.0f);

	    std::vector<std::string> templates = {
			    "ground.json",
	    };

	    std::vector<glm::vec3> positions{
			    glm::vec3(0.0f, 0.0f, 0.0f)
	    };

	    std::vector<glm::vec3> sizes{
			    glm::vec3(40.0f, 42.0f, 0.0f)
	    };

	    auto ground = std::make_shared<game::characters::chunk>(origin, templates, positions, sizes);

	    add_actor("default", actor);
        add_actor("ground", ground);

	    for(auto actor: actors){
		    actor.second->core = core;
		    actor.second->init();
	    }

	    core->mixer->load_music("green_hill", core->filesystem->get_file_path("green_hill_zone_bgm.ogg"));
	    core->mixer->play_music("green_hill");

	    core->mixer->load_effect("jump", core->filesystem->get_file_path("Jump.wav"));
	    core->mixer->load_effect("stop", core->filesystem->get_file_path("Skid.wav"));
	    core->mixer->load_effect("spin", core->filesystem->get_file_path("Spin.wav"));

//	    this->sonic_body->set_jump_speed(6.5f + (224.0f / 480.0f * 6.5f));

    }

    virtual void deinit(){

    }

	void act_one(){

	}

	void act_two(){

	}

	void act_three(){

	}

	virtual void update(const float& dt) override {
		scene::update(dt);

		switch(phase){
			case stage_phase::act_1:
				break;

			case stage_phase::act_2:
				break;

			case stage_phase::act_3:
				break;
		}

	}

private:
	enum stage_phase{
		act_1 = 0,
		act_2 = 1,
		act_3 = 2
	};

	unsigned int phase;

};// class stage                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      