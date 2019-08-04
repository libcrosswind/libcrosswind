#pragma once

#include <memory>
#include <string>
#include <map>

#include "glm/glm.hpp"

// forward declarations
namespace cw{
namespace graphical{
namespace object{

	class sprite;
	class sprite_animation;

}// namespace object
}// namespace graphical
}// namespace cw


namespace cw{
namespace graphical{
namespace object{

class renderable{
public:
	virtual std::shared_ptr<sprite> get_render_sprite() = 0;
};// class renderable

}// namespace object
}// namespace graphical
}// namespace cw
