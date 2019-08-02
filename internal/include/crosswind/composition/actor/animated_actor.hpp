#pragma once

#include <map>
#include <memory>
#include <string>

#include "crosswind/composition/actor/actor.hpp"

// forward declarations
namespace cw {

namespace graphical{
namespace object{

	class renderable;
	class model;

}// namespace object
}// namespace graphical

namespace simulation{
namespace detail{
	
	class body;
	class character;

}// namespace detail
}// namespace simulation

}// namespace cw



namespace cw{
namespace composition{

class animated_actor: public actor{
	
public:
	animated_actor(const std::string& c_name);
	~animated_actor();

	virtual void set_origin(const glm::vec3& f_origin) override;
	virtual void set_size(const glm::vec3& f_size) override;
	virtual void set_alpha(const float& f_alpha) override;

	void update(const float& dt);

	void add_model(const std::string& model_name,
				   const glm::vec3& origin,
				   const glm::vec3& size,
				   const std::string& template_file);

	std::shared_ptr<graphical::object::model> get_model(const std::string& model_name);

	void remove_model(const std::string& model_name);

	void add_rigid_body(const std::string& body_name,
			            const glm::vec3& origin,
			            const glm::vec3& size,
			            const float& mass);

	auto get_rigid_body(const std::string& body_name);

	void remove_rigid_body(const std::string& body_name);

	void add_character(const std::string& character_name,
					   const glm::vec3& origin,
					   const glm::vec2& size,
					   const float& step_height);

	auto get_character(const std::string& character_name);

	void remove_character(const std::string& character_name);

	std::map<std::string, std::shared_ptr<graphical::object::renderable> >& get_model_map();

private:
	std::map<std::string, std::shared_ptr<graphical::object::model> > 		model_map;
	std::map<std::string, std::shared_ptr<simulation::detail::body> >       body_map;
	std::map<std::string, std::shared_ptr<simulation::detail::character> >  character_map;

};// class actor

}// namespace composition
}// namespace cw