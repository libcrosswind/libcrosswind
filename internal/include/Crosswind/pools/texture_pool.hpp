#pragma once 

#include <unordered_map>
#include <string>
#include <memory>
#include <mutex>
#include <stdexcept>

#include <Crosswind/graphics/texture.hpp>
#include <Crosswind/util/filesystem.hpp>


namespace cw {

	class texture_pool{

    public:
		static std::shared_ptr<texture> loadTexture(std::string name,
                                                    double width, double height,
                                                    std::string path = "",
                                                    std::string filename = "", bool create_copy = false){

            std::lock_guard<std::mutex> lock(pool_texture_mutex);

            std::shared_ptr<texture> texture;

            if(textures.find(name) != textures.end()) {

                if(create_copy){
                    bool match = false;
                    int replica_num = 0;

                    std::regex regex("^("+filename+"+)_([0-9]*)$");

                    for(auto& texture : textures){

                        std::smatch sm;
                        if(std::regex_match(texture.first(), sm, regex)){
                            replica_num = std::stoul(sm[2]);
                            ++replica_num;
                        }
                    }

                    textures[name] = std::shared_ptr<texture>
                            (new texture(filesystem::get_file_path(name, path), width, height));

                    texture = textures[name];


                } else {
                    texture = textures[name];
                }

            } else {

                textures[name] = std::shared_ptr<texture>
                                (new texture(filesystem::get_file_path(name, path), width, height));

                texture = textures[name];
            }

            return texture;
        }



        static std::shared_ptr<texture> getTexture(std::string name){
            std::lock_guard<std::mutex> lock(pool_texture_mutex);

            if(textures.find(name) != textures.end()) {

                return textures[name];

            } else {
                throw std::runtime_error(name + std::string(": Texture not loaded, load it first."));
            }

        }

	private:
		static std::unordered_map<std::string, std::shared_ptr<texture> > textures;
        static std::mutex pool_texture_mutex;

	};

    std::unordered_map<std::string, std::shared_ptr<texture> > texture_pool::textures;
    std::mutex texture_pool::pool_texture_mutex;
}

