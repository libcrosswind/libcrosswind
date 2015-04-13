#include "crosswind/composition/core.hpp"
#include "crosswind/composition/stage.hpp"

cw::engine::engine(const configuration::settings& engine_settings){
        core    = std::make_shared<class cw::composition::core>(engine_settings);
        stage   = std::make_shared<class cw::composition::stage>(core);
}

void cw::engine::run(){

    core->application->start();

    while (core->application->alive()) {

        core->video->window->begin_frame();

        update();
        render();

        core->video->window->end_frame();

    }

}

void cw::engine::update(){
    core->application->update();
    core->input->update();
    core->physics->update(1.0f/60.0f);
    stage->update(1.0f/60.0f);
}

void cw::engine::render(){
    core->video->window->clear();

    core->video->renderer->begin();

    core->video->renderer->set_uniform_matrix("projection_matrix",
            stage->get_scene("current")->get_camera("current")->get_camera_matrix());

    for(auto& group_mapping : stage->get_scene("current")->get_group_map()){
        for(auto& actor_mapping : group_mapping.second->get_actor_map()){
            for(auto& model_mapping : actor_mapping.second->get_model_map()){
                core->video->renderer->upload(model_mapping.second->get_render_sprite());
            }
            for(auto& text_mapping : actor_mapping.second->get_text_map()){
                core->video->renderer->upload(text_mapping.second->get_render_sprite());
            }
        }
    }

    for(auto& actor_mapping: stage->get_scene("current")->get_actor_map()){
        for(auto& model_mapping : actor_mapping.second->get_model_map()){
            core->video->renderer->upload(model_mapping.second->get_render_sprite());
        }

        for(auto& text_mapping : actor_mapping.second->get_text_map()){
            core->video->renderer->upload(text_mapping.second->get_render_sprite());
        }
    }

    core->video->renderer->draw();
    core->video->renderer->end();

    core->physics->debug_draw_world(stage->get_scene("current")->get_camera("current")->get_camera_matrix());
    core->video->window->present();
}
