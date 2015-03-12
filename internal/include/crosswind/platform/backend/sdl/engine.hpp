#pragma once

namespace cw{
namespace platform{
namespace backend{
namespace sdl{

	class engine;

}// namespace sdl
}// namespace backend
}// namespace platform
}// namespace cw


class cw::platform::backend::sdl::engine: public cw::platform::backend::interface::engine{
public:
	engine(std::map<std::string, std::vector<int> > config){

		sdl_core  = std::make_shared<sdl_core>(config["core"]);
		sdl_audio = std::make_shared<sdl_core>(config["audio"]);
		sdl_image = std::make_shared<sdl_core>(config["image"]);

	}

	std::shared_ptr<  core::sdl_core >   sdl_core;
    std::shared_ptr< image::sdl_image >  sdl_image;
    std::shared_ptr< audio::sdl_mixer >  mixer;

};// class engine