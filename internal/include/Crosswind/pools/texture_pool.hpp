#pragma once 


#include <Crosswind/graphics/texture.hpp>
#include <Crosswind/util/filesystem.hpp>

#include <unordered_map>
#include <string>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <regex>

namespace cw {

	class texture_pool{

    public:
		static auto create_texture(std::string path,
                                    double width, double height,
                                    std::string name = ""){

           auto result_texture =  std::shared_ptr<texture>(new texture(filesystem::get_file_path(path), width, height));

           texture->set_name(name);

           return result_texture;
        }

        static auto getTexture(std::string name){
            std::lock_guard<std::mutex> lock(pool_texture_mutex);

            if(textures.find(name) != textures.end()) {

                return textures[name];

            } else {
                throw std::runtime_error(name + std::string(": Texture not loaded, load it first."));
            }

        }

	private:
         static std::forward_list<std::shared_ptr<texture> > textures;
         static std::mutex pool_texture_mutex;

	};

    std::forward_list<std::shared_ptr<texture> > texture_pool::textures;
    std::mutex texture_pool::pool_texture_mutex;
}

