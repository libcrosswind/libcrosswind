#pragma once 

#include <memory>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <functional>

#include "crosswind/composition/detail/named_component.hpp"
#include "crosswind/composition/detail/logic_component.hpp"

// forward declarations
namespace cw{
namespace composition{
	
	class core;
	class camera;
	class group;
	class actor;

}// namespace composition
}// namespace cw

namespace cw{
namespace composition{

class scene: public named_component,
			 public logic_component{
	friend class stage;
public:
	scene();

	void add_camera(const std::string& camera_name, std::shared_ptr<camera> camera);

	auto get_camera(const std::string& camera_name);

	void add_actor(const std::string& actor_name, std::shared_ptr<actor> actor);

	auto get_actor(const std::string& actor_name);

	void remove_actor(const std::string& actor_name);

	void load_actor(const std::string& actor_name);

	void unload_actor(const std::string& actor_name);

	void add_group(const std::string& group_name, std::shared_ptr<group> group);

	auto get_group(const std::string& group_name);

	void remove_group(const std::string& group_name);

	void load_group(const std::string& group_name);

	void unload_group(const std::string& group_name);

	auto& get_camera_map();

	auto& get_group_map();

	auto& get_actor_map();

	void check_collisions();

	auto& get_collision_map(const std::string& actor_a);

	void handle_events();

	void post_event(const std::function<void()>& event, const bool& continuous = false);

	void update(const float& delta);

	std::shared_ptr<core> core;

public:
	void set_bool(const std::string item_name, const bool& value);
	bool& get_bool(const std::string item_name);
	void set_float(const std::string item_name, const float& value);
	float& get_float(const std::string item_name);
	void set_int(const std::string item_name, const int& value);
	int& get_int(const std::string item_name);

private:
	std::map<std::string, bool> conditions;
	std::map<std::string, float> float_values;
	std::map<std::string, int> int_values;

	std::map<std::string, std::shared_ptr<actor> > actor_map;
	std::map<std::string, std::shared_ptr<group> > group_map;
	std::map<std::string, std::shared_ptr<camera> > camera_map;
	std::vector<std::pair<bool, std::function<void()> > > event_queue;

	typedef std::map<std::string, std::vector<std::pair<glm::vec3, glm::vec3> > > actor_collision_map;
	std::map<std::string, actor_collision_map> scene_collision_map;


};// class stage

}// namespace composition
}// namespace cw