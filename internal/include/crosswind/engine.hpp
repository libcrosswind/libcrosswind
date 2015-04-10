#pragma once

#include <map>
#include <memory>
#include <string>

#include <glm/glm.hpp>

#include <crosswind/interface/settings.hpp>
#include <crosswind/implementation/composition/core.hpp>
#include <crosswind/implementation/composition/stage.hpp>

namespace cw{

    class engine;

}// namespace cw

class cw::engine{
public:
	engine(interface::settings engine_settings = interface::settings()){

        core    = std::make_shared<class implementation::composition::core>(engine_settings);
        stage   = std::make_shared<class implementation::composition::stage>(core);

	}

	void run(){

   		core->application->start();

        while (core->application->alive()) {

            core->video->window->begin_frame();

            update();
            render();

            core->video->window->end_frame();

        }

	}


private:
    void update(){
        core->application->update();
        core->input->update();
        core->physics->update(1.0f/60.0f);
        stage->update(1.0f/60.0f);
    }

    void render(){
        core->video->window->clear();

        core->video->renderer->begin();

        core->video->renderer->set_uniform_matrix("projection_matrix",
                stage->get_scene("current")->get_camera("current")->get_camera_matrix());

        for(auto& group_mapping : stage->get_scene("current")->get_group_map()){
            for(auto& actor_mapping : group_mapping.second->get_actor_map()){
                for(auto& model_mapping : actor_mapping.second->get_model_map()){
                    core->video->renderer->upload(model_mapping.second->get_render_sprite());
                }
            }
        }

        for(auto& actor_mapping: stage->get_scene("current")->get_actor_map()){
            for(auto& model_mapping : actor_mapping.second->get_model_map()){
                core->video->renderer->upload(model_mapping.second->get_render_sprite());
            }
        }

        core->video->renderer->draw();
        core->video->renderer->end();

        core->physics->debug_draw_world(stage->get_scene("current")->get_camera("current")->get_camera_matrix());
        core->video->window->present();
    }

public:
    std::shared_ptr<implementation::composition::core>  core;
    std::shared_ptr<implementation::composition::stage> stage;

};// class engine