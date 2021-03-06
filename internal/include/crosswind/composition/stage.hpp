#pragma once

#include <memory>
#include <map>
#include <functional>
#include <string>
#include <vector>

#include "glm/glm.hpp"

// forward declarations
namespace cw{
namespace composition{
	
	class core;
	class scene;
	class camera;
	class actor;

}// namespace composition
}// namespace cw

namespace cw{
namespace composition{

class stage{
public:
	stage(std::shared_ptr<core> c_core);

	std::shared_ptr<camera> create_camera(const glm::i32vec2& f_size);

	void add_scene(std::shared_ptr<scene> scene);

	std::shared_ptr<scene> get_scene(const std::string& scene_name);

	void remove_scene(const std::string& scene_name);

	void load_scene(const std::string& name);

	void unload_scene(const std::string& name);

	void swap_scene(const std::string& previous_scene, const std::string& new_scene);

	void update(const float& dt);

private:
	std::shared_ptr<core> core;
	std::map<std::string, std::shared_ptr<scene> > scene_map;

};// class stage


}// namespace composition
}// namespace cw