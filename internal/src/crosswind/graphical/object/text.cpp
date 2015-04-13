#include "crosswind/graphical/object/text.hpp"
#include "crosswind/graphical/object/sprite.hpp"
#include "crosswind/graphical/sdl/font.hpp"
#include "crosswind/graphical/sdl/surface.hpp"

cw::interface::graphical::object::text::text(const std::string& c_text,
											 const glm::vec3& c_origin,
											 const glm::vec3& c_color,
											 const uint32_t& c_size){

	text_value = c_text;
	origin = c_origin;
	color = c_color;
	size = c_size;

}

void cw::interface::graphical::object::text::set_text(const std::string& f_text){
	
	text_value = f_text;

}

std::string& cw::interface::graphical::object::text::get_text(){
	
	return text_value;

}

void cw::interface::graphical::object::text::set_origin(const glm::vec3& f_origin){
	
	origin = f_origin;

}

glm::vec3 cw::interface::graphical::object::text::get_origin(){
	
	return origin;

}

void cw::interface::graphical::object::text::set_size(const uint32_t& f_size){
	
	size = f_size;

}

uint32_t cw::interface::graphical::object::text::get_size(){
	
	return size;

}

void cw::interface::graphical::object::text::set_color(const glm::vec3& f_color){
	
	color = f_color;

}

glm::vec3 cw::interface::graphical::object::text::get_color(){
	
	return color;

}

void cw::interface::graphical::object::text::set_render_sprite(std::shared_ptr<detail::sprite> sprite){
	
	render_sprite = sprite;

}

auto cw::interface::graphical::object::text::get_render_sprite(){

	return render_sprite;

}

auto cw::interface::graphical::object::text::render(std::shared_ptr<sdl::font> font){
	SDL_Color text_color = {uint8_t(color.r * 255),
							uint8_t(color.g * 255),
							uint8_t(color.b * 255)};

	auto surface =
			std::make_shared<sdl::surface>(font->data.ptr(), text_value, text_color);

	return surface;
}

 