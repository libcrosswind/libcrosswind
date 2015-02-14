#pragma once

#include <Crosswind/events/delegate.hpp>

namespace cw{
	class input_listener{
	public:
        delegate<void, int, int>		  on_mouse_up;
        delegate<void, int, int>          on_mouse_move;
		delegate<void, int, int, int>     on_mouse_down;

        delegate<void, int> on_key_down;
        delegate<void, int> on_key_up;

	};
}