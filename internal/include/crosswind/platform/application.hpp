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

	void start();

	bool alive();

	void exit();

private:
	auto was_init(Uint32 flags);
	
	void init_subsystem(Uint32 flags);

	void quit_subsystem(Uint32 flags);

    bool running;

    SDL_Event event;

};// class application

}// namespace platform
}// namespace cw