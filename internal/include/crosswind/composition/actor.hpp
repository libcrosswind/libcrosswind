#pragma once

#include <map>
#include <memory>
#include <string>

#include "crosswind/composition/detail/named_component.hpp"
#include "crosswind/composition/detail/spatial_component.hpp"
#include "crosswind/composition/detail/logic_component.hpp"

// forward declarations
namespace cw {

namespace composition {
	
	class core;

}// namespace composition

namespace graphical{
namespace object{
	
	class model;
	class text;

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

class actor: public detail::named_component,
			 public detail::spatial_component,
			 public detail::logic_component{
	
public:
	actor();
	~actor();

	virtual void set_origin(const glm::vec3& f_origin) override;
	virtual void set_size(const glm::vec3& f_size) override;
	virtual void set_alpha(const float& f_alpha) override;

	void update(const float& dt);

	void add_text(const std::string& text_name,
				  const std::string& text,
				  const glm::vec3& origin,
				  const glm::vec3& color,
				  const int& size,
				  const std::string& font_path);

	void remove_text(const std::string& text_name);

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

	std::map<std::string, std::shared_ptr<graphical::object::model> >& get_model_map();

	std::map<std::string, std::shared_ptr<graphical::object::text> >& get_text_map();

	std::shared_ptr<core> core;
	std::map<std::string, bool> conditions;

private:
	std::map<std::string, std::shared_ptr<graphical::object::model> > 		model_map;
	std::map<std::string, std::shared_ptr<graphical::object::text> > 		text_map;
	std::map<std::string, std::shared_ptr<simulation::detail::body> >       body_map;
	std::map<std::string, std::shared_ptr<simulation::detail::character> >  character_map;

};// class actor

}// namespace composition
}// namespace cw