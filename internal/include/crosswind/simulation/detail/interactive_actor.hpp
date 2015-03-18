#pragma once

#include <memory>
#include <string>

#include <SDL2/SDL_events.h>


#include <crosswind/functional/delegate.hpp>
#include <crosswind/platform/backend/interface/core/input_listener.hpp>

namespace cw{
namespace simulation{
namespace detail{

	class interactive_actor;

}// namespace detail
}// namespace simulation
}// namespace cw


class cw::simulation::detail::interactive_actor{
public:
	interactive_actor(){

	}

	virtual void handle_input(std::shared_ptr<platform::backend::interface::core::input_listener> input_listener) = 0;

public:
    functional::delegate<void> on_mouse_down;
    functional::delegate<void> on_mouse_up;

};// class image_actor