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
	class text;

}// namespace object
}// namespace graphical

}// namespace cw



namespace cw{
namespace composition{

class text_actor: public actor{
	
public:
	text_actor(const std::string& c_name);
	~text_actor();

	virtual void set_origin(const glm::vec3& f_origin) override;
	virtual void set_size(const glm::vec3& f_size) override;
	virtual void set_alpha(const float& f_alpha) override;

	void update(const float& dt) override;

	void add_text(const std::string& text_name,
				  const std::string& text,
				  const glm::vec3& origin,
				  const glm::vec3& color,
				  const int& size,
				  const std::string& font_path =  "ui_font.ttf");

	std::shared_ptr<graphical::object::text> get_text(const std::string& text_name);

	void remove_text(const std::string& text_name);

	std::map<std::string, std::shared_ptr<graphical::object::renderable> > get_model_map() override;

private:
	std::map<std::string, std::shared_ptr<graphical::object::text> > 		text_map;
};// class text_actor

}// namespace composition
}// namespace cw