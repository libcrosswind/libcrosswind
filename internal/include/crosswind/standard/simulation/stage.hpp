#pragma once 

namespace cw{
namespace standard{
namespace simulation{

	class stage;

}// namespace simulation
}// namespace standard
}// namespace cw


class cw::standard::simulation::stage{
	
	stage(){

	}
	
	virtual void handle_event(SDL_Event* e){
//		auto& v = 
	}

	virtual void update(double delta){

	}

	virtual void render(auto sdl_renderer){

	}

	std::function<void(T&)> update();

	concurrent::mutexed_container<std::vector<std::shared_ptr<image_actor> > > gui_elements;

	platform::generic::application* application;
	
};// class stage