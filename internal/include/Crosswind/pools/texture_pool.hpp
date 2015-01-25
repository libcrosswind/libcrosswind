#pragma once 

#include <unordered_map>
#include <string>
#include <memory>
#include <stdexcept>

#include <Crosswind/graphics/texture.hpp>
#include <Crosswind/util/filesystem.hpp>


namespace cw {

	class texture_pool{

    public:
		static std::shared_ptr<texture> loadTexture(std::string name,
                                                    double width, double height,
                                                    std::string path = ""){

            if(textures.find(name) != textures.end()) {

                return textures[name];

            } else {

                textures[name] = std::shared_ptr<texture>
                                (new texture(filesystem::get_file_path(name, path), width, height));

                return textures[name];
            }
        }

        static std::shared_ptr<texture> getTexture(std::string name){

            if(textures.find(name) != textures.end()) {

                return textures[name];

            } else {
                throw std::runtime_error(name + std::string(": Texture not loaded, load it first."));
            }

        }

	private: //TODO  replace_texture, multithreaded.
		static std::unordered_map<std::string, std::shared_ptr<texture> > textures;

	};

    std::unordered_map<std::string, std::shared_ptr<texture> > texture_pool::textures;
}

