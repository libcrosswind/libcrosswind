#pragma once

#include <SDL2/SDL_mixer.h>

#include <crosswind/platform/backend/interface/core/mixer.hpp>
#include <crosswind/platform/backend/sdl/audio/chunk.hpp>
#include <crosswind/platform/backend/sdl/audio/music.hpp>
#include <crosswind/platform/backend/sdl/core/exception.hpp>
#include <crosswind/platform/filesystem.hpp>

namespace cw{
namespace platform{
namespace backend{
namespace sdl{
namespace core{

	class mixer;

}// namespace core
}// namespace sdl
}// namespace backend
}// namespace platform
}// namespace cw

class cw::platform::backend::sdl::core::mixer: public cw::platform::backend::interface::core::mixer{
public:
	template<typename... Args>
	mixer(Args... args) {

		if (Mix_OpenAudio(args...) < 0)
		 throw exception("SDL_mixer could not initialize! SDL_mixer Error: %s\n");//, Mix_GetError());

	}

	~mixer() {
    	Mix_Quit();
	}

	virtual void load_music(const std::string& name, const std::string& path){

        bgm_tracks[name] = std::make_shared<audio::music>(cw::platform::filesystem::get_file_path(path));

	}

	virtual void play_music(const std::string& name){

		if(Mix_PlayingMusic() == 0){ 							// If there is no music playing

			Mix_PlayMusic(bgm_tracks[name]->data.ptr(), -1);	// Play the music

		} else {												// There is music playing

			stop_music();										// Stop the music
			Mix_PlayMusic(bgm_tracks[name]->data.ptr(), -1);	// Play the music

		}

	}

	virtual void pause_music(){

		Mix_PausedMusic() == 1 ? // If the music is paused
        Mix_ResumeMusic()	   : // Resume the music, else
		Mix_PauseMusic ();    	 // Pause the music       

	}

	virtual void resume_music(){

 		if(Mix_PausedMusic() == 1){// If the music is paused
            //Resume the music
            Mix_ResumeMusic();
        } 
	}

    virtual void stop_music(){
        Mix_HaltMusic();// Stop the music
    }

    virtual void load_effect(const std::string& name, const std::string& path){
        sfx_tracks[name] = std::make_shared<audio::chunk>(cw::platform::filesystem::get_file_path(path));
    }

    virtual void play_effect(const std::string& name){

        Mix_PlayChannel(-1, sfx_tracks[name]->data.ptr(), 0); // Play the effect

    }

private:
	// non-copyable
	mixer(const mixer& other) = delete;
	mixer& operator=(const mixer& other) = delete;

	// non-movable
	mixer(mixer&& other) = delete;
	mixer& operator=(mixer&& other) = delete;

	// non-default
	mixer() = delete;

private:
	std::map<std::string, std::shared_ptr<audio::music> > bgm_tracks;
	std::map<std::string, std::shared_ptr<audio::chunk> > sfx_tracks;

};// class mixer