#pragma once

#include <map>
#include <memory>
#include <string>

#include <glm/glm.hpp>

#include <crosswind/interface/settings.hpp>
#include <crosswind/implementation/platform/application.hpp>
#include <crosswind/implementation/platform/filesystem.hpp>
#include <crosswind/implementation/platform/input.hpp>
#include <crosswind/implementation/graphical/video.hpp>
#include <crosswind/implementation/sound/mixer.hpp>
#include <crosswind/implementation/simulation/physics.hpp>
#include <crosswind/implementation/composition/stage.hpp>

namespace cw{
    
    class engine;

}// namespace cw

class cw::engine{
public:
	engine(interface::settings engine_settings = interface::settings()){
        application = std::make_shared<implementation::platform::application>(engine_settings.application.flags);
        filesystem  = std::make_shared<implementation::platform::filesystem>();

        input       = std::make_shared<implementation::platform::input>();
        video       = std::make_shared<implementation::graphical::video>(engine_settings.video.window_title,
                                                                         engine_settings.video.window_position,
                                                                         engine_settings.video.window_resolution,
                                                                         engine_settings.video.fps,
                                                                         engine_settings.video.image_flags,
                                                                         engine_settings.video.window_flags);

        mixer       = std::make_shared<implementation::sound::mixer>(engine_settings.audio.frequency,
                                                                     engine_settings.audio.format,
                                                                     engine_settings.audio.channels,
                                                                     engine_settings.audio.chunk_size);

        physics     = std::make_shared<implementation::simulation::physics>(engine_settings.physics.gravity,
                                                                            engine_settings.physics.scale,
                                                                            engine_settings.physics.unit_value);

        stage       = std::make_shared<implementation::composition::stage>();

/*
            //We wil treat centimeters as pixels where 1 millimeter = 3.78 pixels

            std::vector<glm::vec3> physics_settings{
                    glm::vec3(0.0f, -10.0f, 0.0f),// gravity
                    glm::vec3(0.01f, 0.01f, 0.01f),// scale
                    glm::vec3(1.0f * world_scale[0], 1.0f * world_scale[1], 1.0f * world_scale[2])    // unit value
            };// 1 pixel represents 0.00026458 meters. We set this property to ensure correct graphical calculations.

*/
	}

	void run(){

   		application->start();

        while (application->alive()) {

            video->window->begin_frame();

            update();
            render();

            float fps = video->window->end_frame();

        }

	}


private:
    void update(){
        application->update();
        input->update();
    	physics->update(1.0f/60.0f);
        stage->update(1.0f/60.0f);
    }

    void render(){
        video->window->clear();

        video->renderer->begin();

        video->renderer->set_uniform_matrix("projection_matrix",
                stage->get_scene("current")->get_camera("current")->get_camera_matrix());

        for(auto& actor_mapping: stage->get_scene("current")->get_actor_map()){
            for(auto& sprite_mapping = actor_mapping.second->get_render_sprite_list()){
               // video->renderer->upload(actor_mapping.second->get_render_sprite_list());
            }
       }

        video->renderer->draw();

        video->renderer->end();

//        physics->draw_world();
        video->window->present();
    }

public:
    std::shared_ptr< interface::platform::application > application;
    std::shared_ptr< interface::platform::filesystem  > filesystem;
    std::shared_ptr< interface::platform::input       >	input;
    std::shared_ptr< interface::graphical::video 	  >	video;
    std::shared_ptr< interface::sound::mixer          > mixer;
    std::shared_ptr< interface::simulation::physics   >	physics;
    std::shared_ptr< interface::composition::stage    > stage;

private:
//

};// class engine