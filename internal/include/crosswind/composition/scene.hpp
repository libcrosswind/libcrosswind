#pragma once 

#include <memory>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <functional>

#include "glm/glm.hpp"

#include "crosswind/composition/detail/named_component.hpp"
#include "crosswind/composition/detail/logic_component.hpp"

// forward declarations
namespace cw{
namespace composition{
	
	class core;
	class camera;
	class actor;

}// namespace composition
}// namespace cw

namespace cw{
namespace composition{

class scene: public detail::named_component,
			 public detail::logic_component {
	friend class stage;
public:
	scene(const std::string& c_name);

	void add_camera(const std::string& camera_name, std::shared_ptr<camera> camera);

	void set_camera(const std::string& camera_name);

	std::shared_ptr<camera> get_camera(const std::string& camera_name);

	auto& get_camera_map();

	void update(const float& delta);

	std::shared_ptr<core> core;

private:
	std::map<std::string, std::shared_ptr<camera> > camera_map;

};// class stage

}// namespace composition
}// namespace cw