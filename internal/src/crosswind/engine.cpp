#include <functional>

#include "crosswind/engine.hpp"
#include "crosswind/composition/core.hpp"
#include "crosswind/composition/stage.hpp"
#include "crosswind/composition/scene.hpp"
#include "crosswind/composition/camera.hpp"
#include "crosswind/platform/application.hpp"
#include "crosswind/platform/input.hpp"
#include "crosswind/graphical/video.hpp"
#include "crosswind/graphical/object/text.hpp"
#include "crosswind/graphical/opengl/renderer.hpp"
#include "crosswind/graphical/opengl/window.hpp"
#include "crosswind/simulation/physics.hpp"

cw::engine::engine(const configuration::settings& engine_settings){
        core    = std::make_shared<class cw::composition::core>(engine_settings);
        stage   = std::make_shared<class cw::composition::stage>(core);
}

void cw::engine::run(){

    core->application->start();

    while (core->application->alive()) {

        core->video->window->begin_frame();

        update();
        draw();

        core->video->window->end_frame();

    }

}

void cw::engine::update(){
    core->application->update();
    core->input->update(1.0f/60.0f);
    core->physics->update(1.0f/60.0f);
    stage->update(1.0f/60.0f);
}

void cw::engine::draw(){
    core->video->window->clear();

    core->video->renderer->begin();

    core->video->renderer->set_uniform_matrix("projection_matrix",
            stage->get_scene("current")->get_camera("current")->get_camera_matrix());

    /*std::function<void(std::shared_ptr<cw::composition::group>)> render_group = [this, &render_group](auto group){
        for(auto& actor_mapping : group->get_actor_map()){
            for(auto& model_mapping : actor_mapping.second->get_model_map()){
                this->core->video->renderer->upload(model_mapping.second->get_render_sprite());
            }
        }

        for(auto& group_mapping : group->get_group_map()){
            render_group(group_mapping.second);
        }
    };

    // TODO Recursive group rendering.

    for(auto& group_mapping : stage->get_scene("current")->get_group_map()){
        render_group(group_mapping.second);
    }*/

    /*for(auto& actor_mapping: stage->get_scene("current")->get_actor_map()){
        for(auto& model_mapping : actor_mapping.second->get_model_map()){
            core->video->renderer->upload(model_mapping.second->get_render_sprite());
        }
    }*/

    core->video->renderer->draw();
    core->video->renderer->end();

    core->physics->debug_draw_world(stage->get_scene("current")->get_camera("current")->get_camera_matrix());
    core->video->window->present();
}
