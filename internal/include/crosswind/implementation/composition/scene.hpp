#pragma once

#include <crosswind/interface/composition/scene.hpp>

namespace cw{
namespace implementation{
namespace composition{

	class scene;

}// namespace composition
}// namespace implementation
}// namespace cw

class cw::implementation::composition::scene: public cw::interface::composition::scene{
public:
	scene(){
		
	}

	virtual void add_stage(std::shared_ptr<detail::stage> stage){
/*      stage->setup(engine);
        stage->init(engine);
        engine->physics->init_debug_drawer(stage->get_camera("main_camera"));
        stages[stage->name] = stage;*/
    }

	virtual void swap_stage(const std::string& previous_stage, const std::string& new_stage){
//        stages[previous_stage] = stages[new_stage];
    }

	virtual void remove_stage(const std::string& stage_name){
//        stages["current"]->deinit(engine);
	}

	virtual void update(float dt){
//        stages["current"]->update(1/60.0/*video->window->fps_limiter->get_delta()*/);
	}

	virtual void render(){

        renderer->begin();

        renderer->set_uniform_matrix("projection_matrix", camera_list["current"]->get_camera_matrix());

        for(auto& model_mapping : model_list){
	        renderer->upload(model_mapping.second);
        }

		renderer->draw();

        renderer->end();

	}

	virtual void draw(){

		for(auto& element: graphical_queue){
           element->draw();
        }

	}



};// class scene