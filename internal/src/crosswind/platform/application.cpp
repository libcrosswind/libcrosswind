#include "crosswind/platform/application.hpp"
#include "crosswind/platform/exception.hpp"

cw::platform::application::application(const int& flags): 
running(false){

	if (SDL_Init(flags) != 0)
		throw exception("SDL_Init");
    
}

cw::platform::application::~application(){
	
	SDL_Quit();

}

void cw::platform::application::update() {

    while(SDL_PollEvent(&event)){
            //User requests quit
            if(event.type == SDL_QUIT){
                    running = false;
            }
    }

}

auto cw::platform::application::was_init(auto flags) {

	return SDL_WasInit(flags);

}

void cw::platform::application::init_subsystem(auto flags) {

	if (SDL_InitSubSystem(flags) != 0)
		throw exception("SDL_InitSubsystem");

}

void cw::platform::application::quit_subsystem(auto flags) {

	SDL_QuitSubSystem(flags);

} 