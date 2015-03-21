#pragma once

#include <string>
#include <functional>

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

class audio_callback{
public:


	static void channel_ended(int channel) {

		for (auto &bgm : data->bgm_info) {
			if (bgm.second.first == channel) {
				bgm.second.first = -2;
				bgm.second.second = false;
			}
		}

		for (auto &sfx : data->sfx_info) {
			if (sfx.second.first == channel) {
				sfx.second.first = -2;
				sfx.second.second = false;
			}
		}

	}

	static sdl::core::mixer* data;

};

public:
	template<typename... Args>
	mixer(Args... args) {

		if (Mix_OpenAudio(args...) < 0)
		 throw exception("SDL_mixer could not initialize! SDL_mixer Error: %s\n");//, Mix_GetError());


		audio_callback::data = this;

		Mix_ChannelFinished(audio_callback::channel_ended);

	}

	~mixer() {
    	Mix_Quit();
	}


	virtual void load_music(const std::string& name, const std::string& path){

		bgm_info[name]   = std::make_pair(-21, false); // channel, playing.
        bgm_tracks[name] = std::make_shared<audio::music>(cw::platform::filesystem::get_file_path(path));

	}

	virtual void play_music(const std::string& name){

		if(Mix_PlayingMusic() == 0){ 							// If there is no music playing

			bgm_info[name].first = Mix_PlayMusic(bgm_tracks[name]->data.ptr(), -1);	// Play the music
			bgm_info[name].second = true;

		} else {												// There is music playing

			stop_music();										// Stop the music
			bgm_info[name].first = Mix_PlayMusic(bgm_tracks[name]->data.ptr(), -1);	// Play the music
			bgm_info[name].second = true;

		}

	}

	virtual bool is_playing_music(const std::string& name){

		bgm_info[name].second = Mix_Playing(bgm_info[name].first);
		return bgm_info[name].second;

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

	    for(auto& bgm : bgm_info){
		    bgm.second.first  = -2;
		    bgm.second.second = false;
	    }

	    for(auto& sfx : sfx_info){
		    sfx.second.first = -2;
		    sfx.second.second = false;
	    }

	    Mix_HaltMusic();// Stop the music
    }

    virtual void load_effect(const std::string& name, const std::string& path){

	    sfx_info[name] = std::make_pair(-2, false); // channel, playing.
	    sfx_tracks[name] = std::make_shared<audio::chunk>(cw::platform::filesystem::get_file_path(path));

    }

    virtual void play_effect(const std::string& name){

	    sfx_info[name].first = Mix_PlayChannel(-1, sfx_tracks[name]->data.ptr(), 0); // Play the effect
	    sfx_info[name].second = true;


	    std::cout << "Channel: " << sfx_info[name].first <<std::endl;

    }


	virtual bool is_playing_effect(const std::string& name){

/*		bool playing = sfx_info[name].second;

		if(playing){

		}
		*/

		if(sfx_info[name].second){
			sfx_info[name].second  = Mix_Playing(sfx_info[name].first);
		} else {
			sfx_info[name].first = -2;
			sfx_info[name].second = false;
		}

		return sfx_info[name].second;
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

	std::map<std::string, std::pair<int, bool> > bgm_info;
	std::map<std::string, std::pair<int, bool> > sfx_info;


};// class mixer

cw::platform::backend::sdl::core::mixer* cw::platform::backend::sdl::core::mixer::audio_callback::data = nullptr;
