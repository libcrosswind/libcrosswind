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

void cw::platform::application::start(){
	running = true;
}

bool cw::platform::application::alive(){
	return running;
}

void cw::platform::application::exit(){
	running = false;
}

auto cw::platform::application::was_init(Uint32 flags) {

	return SDL_WasInit(flags);

}

void cw::platform::application::init_subsystem(Uint32 flags) {

	if (SDL_InitSubSystem(flags) != 0)
		throw exception("SDL_InitSubsystem");

}

void cw::platform::application::quit_subsystem(Uint32 flags) {

	SDL_QuitSubSystem(flags);

} 