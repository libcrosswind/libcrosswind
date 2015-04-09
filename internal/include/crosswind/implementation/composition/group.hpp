#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>

#include <crosswind/interface/composition/named_component.hpp>
#include <crosswind/interface/composition/spatial_component.hpp>
#include <crosswind/interface/composition/logic_component.hpp>


#include <crosswind/implementation/composition/core.hpp>
#include <crosswind/implementation/composition/actor.hpp>

namespace cw{
namespace implementation{
namespace composition{
	
	class group;

}// namespace composition
}// namespace implementation
}// namespace cw

class cw::implementation::composition::group: public cw::interface::composition::named_component,
											  public cw::interface::composition::spatial_component,
											  public cw::interface::composition::logic_component{
public:
	group(){
	}

	virtual void set_origin(const glm::vec3& f_origin) override {
		for (auto &actor : actor_map) {
			auto translated_origin = actor.second->get_origin() + f_origin - origin;
			actor.second->set_origin(translated_origin);
		}

		origin = f_origin;
	}

	virtual void set_size(const glm::vec3& f_size) override {
		for (auto &actor : actor_map) {
			auto percented_size = actor.second->get_size() * f_size / size;
			actor.second->set_size(percented_size);
		}

		size = f_size;
	}

	virtual void set_alpha(const float& f_alpha) override {
		alpha = f_alpha;
		for (auto &actor : actor_map) {
			actor.second->set_alpha(alpha);
		}
	}

	void add_actor(const std::string& actor_name, std::shared_ptr<actor> new_actor){
		actor_map[actor_name] = new_actor;
	}

	std::shared_ptr<actor> get_actor(const std::string& actor_name){
		return actor_map[actor_name];
	}

	void remove_actor(const std::string& actor_name){
		actor_map.erase(actor_name);
	}

	std::map<std::string, std::shared_ptr<actor> >& get_actor_map(){
		return actor_map;
	}

	void update(const float& delta){
		for(auto& actor_mapping : actor_map){
			actor_mapping.second->update(delta);
		}

		logic(delta);
	}

public:
	std::shared_ptr<core> core;

private:
	std::map<std::string, std::shared_ptr<actor> > actor_map;

};// class group