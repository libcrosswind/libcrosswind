#include <memory>
#include <string>
#include <stdexcept>

#include "glm/glm.hpp"

#include "crosswind/composition/actor/text_actor.hpp"
#include "crosswind/composition/core.hpp"
#include "crosswind/platform/filesystem.hpp"
#include "crosswind/graphical/video.hpp"
#include "crosswind/graphical/object/model.hpp"
#include "crosswind/graphical/object/text.hpp"
#include "crosswind/graphical/object/sprite.hpp"
#include "crosswind/graphical/object/sprite_animation.hpp"
#include "crosswind/simulation/physics.hpp"
#include "crosswind/simulation/detail/character.hpp"
#include "crosswind/simulation/detail/body.hpp"

cw::composition::text_actor::text_actor(const std::string& c_name): actor(c_name){

}

cw::composition::text_actor::~text_actor(){

}

void cw::composition::text_actor::set_origin(const glm::vec3& f_origin){
	for (auto &text : text_map) {
		auto translated_origin = text.second->get_origin() + f_origin - origin;
		text.second->set_origin(translated_origin);
	}

	origin = f_origin;
}

void cw::composition::text_actor::set_size(const glm::vec3& f_size){
	for(auto& text_mapping : text_map){
		auto percented_size = text_mapping.second->get_size() * f_size / size;
		text_mapping.second->set_size(percented_size);
	}

	size = f_size;
}

void cw::composition::text_actor::set_alpha(const float& f_alpha){
	alpha = f_alpha;
	for(auto& model : text_map){
		auto frame = model.second->get_render_sprite();
		for(auto& vertex : frame->get_vertices()){
			vertex.set_alpha(alpha);
		}
	}
}

void cw::composition::text_actor::update(const float& dt){
	for(auto& model_mapping : text_map){
		//model_mapping.second->update(dt);
	}

	logic(dt);
}

void cw::composition::text_actor::add_text(const std::string& text_name,
										   const std::string& text,
										   const glm::vec3& origin,
										   const glm::vec3& color,
										   const int& size,
										   const std::string& font_path){

	if(text_map.find(name + "_" + text_name) == text_map.end()){
		text_map[name + "_" + text_name] = core->video->load_text(name + "_" + text_name,
																text,
																origin,
																color,
																size,
																core->filesystem->get_file_path(font_path));

	} else {
		throw std::runtime_error(name + "_" + text_name + " already exists, remove it first before adding one with the same name");
	}
}

std::shared_ptr<cw::graphical::object::text> 
cw::composition::text_actor::get_text(const std::string& text_name){
	if(text_map.find(name + "_" + text_name) != text_map.end()){
		return text_map[name + "_" + text_name];
	} else {
		throw std::runtime_error(name + "_" + text_name + " does not exist");
	}
}

void cw::composition::text_actor::remove_text(const std::string& text_name){
	if(text_map.find(name + "_" + text_name) != text_map.end()){
		text_map.erase(name + "_" + text_name);
	} else {
		throw std::runtime_error(name + "_" + text_name + " does not exist or was already removed");
	}
}

std::map<std::string, std::shared_ptr<cw::graphical::object::renderable> > cw::composition::text_actor::get_model_map(){

    std::map<std::string, std::shared_ptr<cw::graphical::object::renderable> > mmap;

    for(auto mapping : this->text_map){
        mmap[mapping.first] = mapping.second;
    }

	return mmap;
}