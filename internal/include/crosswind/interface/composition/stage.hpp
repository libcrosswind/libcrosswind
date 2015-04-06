#pragma once

#include <memory>
#include <functional>

#include <crosswind/interface/core.hpp>
#include <crosswind/implementation/composition/scene.hpp>

namespace cw{
namespace interface{
namespace composition{

	class stage;

}// namespace composition
}// namespace implementation
}// namespace cw

class cw::interface::composition::stage{
protected:
	typedef std::shared_ptr<implementation::composition::scene> scene_ptr;
	typedef std::map<std::string, scene_ptr> scene_map;
public:
	stage(std::shared_ptr<interface::composition::core> c_core): core(c_core){
		
	}

	virtual void handle_events() = 0;
	virtual void post_event(const std::function<void()>& event) = 0;

	virtual void load_scene(const std::string& name) = 0;
	virtual void unload_scene(const std::string& name) = 0;

	virtual scene_ptr create_scene() = 0;

	virtual void add_scene(const std::string& scene_name, scene_ptr scene) = 0;
	virtual void swap_scene(const std::string& previous_scene, const std::string& new_scene) = 0;
	virtual void remove_scene(const std::string& scene_name) = 0;

	virtual void update(const float& dt) = 0;

	virtual void set_scene_map(const scene_map& new_scene_map) = 0;

	virtual scene_map& get_scene_map() = 0;

	virtual scene_ptr get_scene(const std::string& scene_name) = 0;

protected:
	std::shared_ptr<interface::composition::core> core;

	scene_map scenes;
	std::vector<std::function<void()> > event_queue;

};// class scene