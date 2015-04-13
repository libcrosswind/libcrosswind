#pragma once

#include <map>
#include <memory>
#include <string>

#include "crosswind/composition/detail/named_component.hpp"
#include "crosswind/composition/detail/spatial_component.hpp"
#include "crosswind/composition/detail/logic_component.hpp"

// forward declarations
namespace cw{
namespace composition{

	class actor;
	class core;

}// namespace cw
}// namespace composition

namespace cw{
namespace composition{

class group: public detail::named_component,
			 public detail::spatial_component,
			 public detail::logic_component{
public:
	group();

	virtual void set_origin(const glm::vec3& f_origin) override;
	virtual void set_size(const glm::vec3& f_size) override;
	virtual void set_alpha(const float& f_alpha) override;

	void add_actor(const std::string& actor_name, std::shared_ptr<actor> new_actor);

	std::shared_ptr<actor> get_actor(const std::string& actor_name);
	
	void remove_actor(const std::string& actor_name);

	std::map<std::string, std::shared_ptr<actor> >& get_actor_map();

	void update(const float& delta);


	std::shared_ptr<core> core;

private:
	std::map<std::string, std::shared_ptr<actor> > actor_map;

};// class group


}// namespace composition
}// namespace cw