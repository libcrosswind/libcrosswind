#pragma once

#include <SDL2/SDL.h>

#include <crosswind/interface/platform/application.hpp>
#include <crosswind/implementation/platform/exception.hpp>

namespace cw{
namespace implementation{
namespace platform{

	class application;

}// namespace platform
}// namespace implementation
}// namespace cw

class cw::implementation::platform::application: public cw::interface::platform::application{
public:
	application(const int& flags){

		if (SDL_Init(flags) != 0)
			throw exception("SDL_Init");
    
	}

	virtual ~application(){
		SDL_Quit();
	}

    virtual void update() {
        while(SDL_PollEvent(&event)){
                //User requests quit
                if(event.type == SDL_QUIT){
                        running = false;
                }
        }
    }

private:
	SDL_Event event;

private:
	auto was_init(auto flags) {
		return SDL_WasInit(flags);
	}

	void init_subsystem(auto flags) {
		if (SDL_InitSubSystem(flags) != 0)
			throw exception("SDL_InitSubsystem");
	}

	void quit_subsystem(auto flags) {
		SDL_QuitSubSystem(flags);
	}

};// class application