#pragma once

#include <crosswind/interface/composition/scene.hpp>

namespace cw{
namespace interface{
namespace composition{

	class stage;

}// namespace composition
}// namespace implementation
}// namespace cw

class cw::interface::composition::stage{
protected:
	typedef std::map<std::string, std::shared_ptr<scene> > scene_map;
public:
	stage(){
		
	}

	virtual void handle_events() = 0;
	virtual void post_event(const std::function<void()>& event) = 0;

	virtual void load_scene(const std::string& name) = 0;
	virtual void unload_scene(const std::string& name) = 0;

	virtual void add_scene(std::shared_ptr<scene> scene) = 0;
	virtual void swap_scene(const std::string& previous_scene, const std::string& new_scene) = 0;
	virtual void remove_scene(const std::string& scene_name) = 0;

	virtual void update(float dt) = 0;

	virtual void set_scene_map(const scene_map& new_scene_map) = 0;

	virtual scene_map& get_scene_map() = 0;

	virtual std::shared_ptr<scene> get_scene(const std::string& scene_name) = 0;


protected:
	scene_map scenes;
	std::vector<std::function<void()> > event_queue;

};// class scene