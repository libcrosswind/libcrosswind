#pragma once

#include <SDL2/SDL.h>

// verify SDL_Event forward declaration

namespace cw{
namespace platform{

class application{
public:
	application(const int& flags);

	~application();

    void update();

private:
	auto was_init(auto flags);
	
	void init_subsystem(auto flags);

	void quit_subsystem(auto flags);

    bool running;

    SDL_Event event;

};// class application

}// namespace platform
}// namespace cw