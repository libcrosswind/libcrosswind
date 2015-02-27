#pragma once

#include <crosswind/core/functional/delegate.hpp>

namespace cw{
namespace platform{
namespace input{

	class input_listener_interface;

}// namespace input
}// namespace platform
}// namespace cw


class cw::platform::input::input_listener_interface{
public:
    delegate<void, int, int>		  on_mouse_up;
    delegate<void, int, int>          on_mouse_move;
	delegate<void, int, int, int>     on_mouse_down;

    delegate<void, int> on_key_down;
    delegate<void, int> on_key_up;
};// class input_listener_interface

