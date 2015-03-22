#pragma once 

#include <string>

namespace cw{
namespace backend{
namespace interface{
namespace simulation{
	
	class loader;

}// namespace simulation
}// namespace interface
}// namespace backend
}// namespace cw

class cw::backend::interface::simulation::loader{
public:
    std::shared_ptr<simulation::model> load_model(const glm::vec3& origin, const glm::vec3& size, const std::string& template_file){

/*        cw::javascript::json json;
        json.from_file(template_file);

        auto& raw_json = json.data;

        auto model = std::make_shared<simulation::model>();

        for (auto t = raw_json["textures"].begin_members(); t != raw_json["textures"].end_members(); ++t)
        {
            load_texture(t->name(), t->value().as<std::string>());
        }

        std::map<std::string, glm::vec3> sprite_sheet_sizes;

        for (auto s = raw_json["spritesheets"].begin_members(); s != raw_json["spritesheets"].end_members(); ++s)
        {
            std::string name    = s->name();                        // spritesheet name

            auto s_props = s->value().begin_members();

            std::string sprite_size_prop = s_props->name();  // property name.

            glm::vec3 sprite_size(s_props->value()[0].as<double>(), // sprite size.
                                  s_props->value()[1].as<double>(),
                                  0.0);

            sprite_sheet_sizes[name] = sprite_size;
        }


        std::map<std::string, std::shared_ptr<simulation::sprite> > sprites;

        for (auto s = raw_json["sprites"].begin_members(); s != raw_json["sprites"].end_members(); ++s)
        {
            std::string name    = s->name();                        // sprite name

            auto s_props = s->value().begin_members();

            std::string texture = s_props->name();  // mapped texture.


            glm::vec4 uv(s_props->value()[0].as<double>(), // uv coordinates.
                         s_props->value()[1].as<double>(),
                         s_props->value()[2].as<double>(),
                         s_props->value()[3].as<double>());

            sprites[name] = std::make_shared<simulation::sprite>(origin, sprite_sheet_sizes[texture], uv, load_texture(texture)->id);
        }

        std::map<std::string, std::shared_ptr<simulation::sprite_animation> > animations;

        for (auto a = raw_json["animations"].begin_members(); a != raw_json["animations"].end_members(); ++a)
        {

            std::vector<std::shared_ptr<simulation::sprite> > frames;

            for(auto f = a->value()["frames"].begin_elements(); f != a->value()["frames"].end_elements();  ++f){
                frames.push_back(sprites[f->as<std::string>()]);
            }

            auto animation = std::make_shared<simulation::sprite_animation>();
            animation->duration = a->value()["time"].as<double>();
            animation->frames = frames;

            animations[a->name()] = animation;
        }

        model->get_animations() = animations;

        model->change_animation(raw_json["properties"]["default-animation"].as<std::string>());

        model->set_origin(origin);
        model->set_size(size);

        return model;*/
    }



};// class loader