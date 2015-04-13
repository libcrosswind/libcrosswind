#pragma once

#include <memory>
#include <functional>
#include <string>

#include "glm/glm.hpp"

// forward declarations
namespace cw{
namespace composition{
	
	class core;
	class scene;

}// namespace composition
}// namespace cw

namespace cw{
namespace composition{

class stage{
public:
	stage(std::shared_ptr<core> c_core);

	void handle_events();

	void post_event(const std::function<void()>& event);

	auto create_scene();

	auto create_camera(const glm::i32vec2& f_size);

	auto create_actor();

	auto create_group();

	void add_scene(const std::string& scene_name, std::shared_ptr<scene> scene);

	auto get_scene(const std::string& scene_name);

	void remove_scene(const std::string& scene_name);

	void load_scene(const std::string& name);

	void unload_scene(const std::string& name);

	void swap_scene(const std::string& previous_scene, const std::string& new_scene);

	void update(const float& dt);

private:
	std::shared_ptr<core> core;
	std::map<std::string, std::shared_ptr<scene> > scene_map;
	std::vector<std::function<void()> > event_queue;

};// class stage


}// namespace composition
}// namespace cw