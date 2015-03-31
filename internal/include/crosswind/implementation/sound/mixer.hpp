#pragma once

#include <string>

#include <SDL2/SDL_mixer.h>

#include <crosswind/interface/sound/mixer.hpp>
#include <crosswind/implementation/sound/music.hpp>
#include <crosswind/implementation/sound/chunk.hpp>
#include <crosswind/implementation/platform/exception.hpp>

namespace cw{
namespace implementation{
namespace sound{

	class mixer;

}// namespace sound
}// namespace implementation
}// namespace cw

class cw::implementation::sound::mixer: public cw::interface::sound::mixer{

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

	static mixer* data;

};

public:
	mixer(int frequency, uint16_t format, int channels, int chunk_size) {

		if (Mix_OpenAudio(frequency, format, channels, chunk_size) < 0)
		 throw platform::exception("SDL_mixer could not initialize! SDL_mixer Error: %s\n");//, Mix_GetError());


		audio_callback::data = this;

		Mix_ChannelFinished(audio_callback::channel_ended);

	}

	virtual ~mixer() {
    	Mix_Quit();
	}


	virtual void load_music(const std::string& name, const std::string& path){

		bgm_info[name]   = std::make_pair(-21, false); // channel, playing.
        bgm_tracks[name] = std::make_shared<music>(path);

	}

	virtual void play_music(const std::string& name, const int& loops = -1){

		if(Mix_PlayingMusic() == 0){ 							// If there is no music playing

			bgm_info[name].first = Mix_PlayMusic(bgm_tracks[name]->data.ptr(),loops);	// Play the music
			bgm_info[name].second = true;

		} else {												// There is music playing

			stop_music();										// Stop the music
			bgm_info[name].first = Mix_PlayMusic(bgm_tracks[name]->data.ptr(), loops);	// Play the music
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
	    sfx_tracks[name] = std::make_shared<chunk>(path);

    }

    virtual void play_effect(const std::string& name){
	    sfx_info[name].first = Mix_PlayChannel(-1, sfx_tracks[name]->data.ptr(), 0); // Play the effect
	    sfx_info[name].second = true;
    }


	virtual bool is_playing_effect(const std::string& name){

		if(sfx_info[name].second){
			sfx_info[name].second  = Mix_Playing(sfx_info[name].first);
		} else {
			sfx_info[name].first = -2;
			sfx_info[name].second = false;
		}

		return sfx_info[name].second;
	}

private:
	std::map<std::string, std::shared_ptr<music> > bgm_tracks;
	std::map<std::string, std::shared_ptr<chunk> > sfx_tracks;

	std::map<std::string, std::pair<int, bool> > bgm_info;
	std::map<std::string, std::pair<int, bool> > sfx_info;


};// class mixer

cw::implementation::sound::mixer* cw::implementation::sound::mixer::audio_callback::data = nullptr;
