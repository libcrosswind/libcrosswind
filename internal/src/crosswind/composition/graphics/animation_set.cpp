#include "crosswind/composition/graphics/animation_set.hpp"
#include "crosswind/graphical/object/sprite.hpp"
#include "crosswind/graphical/object/sprite_animation.hpp"
#include "crosswind/modules/javascript/json.hpp"

#include "crosswind/composition/core.hpp"
#include "crosswind/graphical/video.hpp"

#include "crosswind/graphical/opengl/texture.hpp"

cw::composition::graphics::animation_set::animation_set(std::shared_ptr<composition::core>  core,
                                                        const std::string& path):
origin(0.0f, 0.0f, 0.0f),
delta_count(0.0f){

	glm::vec3 size;

	modules::javascript::json json;
	json.from_file(path);

	auto& raw_json = json.data;

	for (auto t = raw_json["texture"].begin_members(); t != raw_json["texture"].end_members(); ++t)
	{
			core->video->load_texture(t->name(), t->value().as<std::string>());
	}

	std::map<std::string, std::shared_ptr<graphical::object::sprite> > sprites;

	for (auto s = raw_json["sprites"].begin_members(); s != raw_json["sprites"].end_members(); ++s)
	{
			std::string name    = s->name();                        // sprite name

			auto s_props = s->value().begin_members();

			std::string texture = s_props->name();  // mapped texture.

			glm::vec4 uv(s_props->value()[0].as<double>(), // uv coordinates.
									 s_props->value()[1].as<double>(),
									 s_props->value()[2].as<double>(),
									 s_props->value()[3].as<double>());

			sprites[name] = std::make_shared<graphical::object::sprite>(origin,
                                                                         size,
                                                                         glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                                                                         uv,
                                                                         core->video->load_texture(texture)->id);
	}

	std::map<std::string, std::shared_ptr<graphical::object::sprite_animation> > animations;

	for (auto a = raw_json["animations"].begin_members(); a != raw_json["animations"].end_members(); ++a)
	{

			std::vector<std::shared_ptr<graphical::object::sprite> > frames;

			for(auto f = a->value()["frames"].begin_elements(); f != a->value()["frames"].end_elements();  ++f){
					frames.push_back(sprites[f->as<std::string>()]);
			}

			auto animation = std::make_shared<graphical::object::sprite_animation>();
			animation->duration = a->value()["time"].as<double>();
			animation->frames = frames;

			animations[a->name()] = animation;
	}

	this->set_animations(animations);

	auto anim = raw_json["properties"]["default-animation"].as<std::string>();
	this->change_animation(anim);

	this->set_render_sprite(this->animations["current"]->
										 			frames[this->animations["current"]->current_frame]);
}

void cw::composition::graphics::animation_set::set_origin(const glm::vec3& new_origin){

	origin = new_origin;
	for(auto& animation : animations){
		animation.second->set_origin(origin);
	}

}

glm::vec3 cw::composition::graphics::animation_set::get_origin(){

	return origin;

}

void cw::composition::graphics::animation_set::change_animation(const std::string& new_animation){

	if(animations["current"] != animations[new_animation]){
		animations["current"] = animations[new_animation];
	}

}

void cw::composition::graphics::animation_set::update(const float& delta){

    delta_count += delta;

    if(delta_count >= animations["current"]->duration / (float) animations["current"]->frames.size()){

        delta_count = 0;

        animations["current"]->current_frame++;

        if(animations["current"]->current_frame >= animations["current"]->frames.size()){
            animations["current"]->current_frame = 0;
        }
    }

	set_render_sprite(animations["current"]->frames[animations["current"]->current_frame]);

}

void cw::composition::graphics::animation_set::set_render_sprite(std::shared_ptr<cw::graphical::object::sprite> sprite){

	render_sprite = sprite;

}

void cw::composition::graphics::animation_set::set_animations(const std::map<std::string, std::shared_ptr<cw::graphical::object::sprite_animation> >& new_animations){

	animations.clear();

	for(auto mapping : new_animations){
		animations[mapping.first] = mapping.second;
	}

}
