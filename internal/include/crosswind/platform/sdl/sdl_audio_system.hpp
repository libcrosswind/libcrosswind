#pragma once

#include <SDL2/SDL_mixer.h>

#include <crosswind/concurrent/mutex_container.hpp>
#include <crosswind/platform/sdl/sdl_music.hpp>
#include <crosswind/platform/sdl/sdl_exception.hpp>


namespace cw{
namespace platform{
namespace sdl{

	class sdl_audio_system;

}// namespace sdl
}// namespace platform
}// namespace cw

class cw::platform::sdl::sdl_audio_system{
public:
	template<typename... Args>
	sdl_audio_system(Args... args) {

		if (Mix_OpenAudio(args...) < 0)
		 throw sdl_exception("SDL_mixer could not initialize! SDL_mixer Error: %s\n");//, Mix_GetError());

	}

	~sdl_audio_system() {
    	Mix_Quit();
	}

	void load_music(const std::string& name, const std::string& path){

			bgm_tracks(name, std::make_shared<sdl_music>(path));

	}


	void play_music(const std::string& name){

		if(Mix_PlayingMusic() == 0){ 					// If there is no music playing
			auto track = bgm_tracks(name);
			auto track_ptr = track->music.acquire();

			Mix_PlayMusic(track_ptr, -1);				// Play the music

			track->music.release();

		} else {										// There is music playing
			stop_music();								// Stop the music

			auto track = bgm_tracks(name);
			auto track_ptr = track->music.acquire();

			Mix_PlayMusic(track_ptr, -1);				// Play the music

			track->music.release();
		}

	}

	void pause_music(){

		Mix_PausedMusic() == 1 ? // If the music is paused
        Mix_ResumeMusic()	   : // Resume the music, else
		Mix_PauseMusic ();    	 // Pause the music        		

	}


	void resume_music(){

 		if(Mix_PausedMusic() == 1){// If the music is paused
            //Resume the music
            Mix_ResumeMusic();
        } 
	}

	void stop_music(){
        Mix_HaltMusic();// Stop the music
	}


private:
	// non-copyable
	sdl_audio_system(const sdl_audio_system& other) = delete;
	sdl_audio_system& operator=(const sdl_audio_system& other) = delete;

	// non-movable
	sdl_audio_system(sdl_audio_system&& other) = delete;
	sdl_audio_system& operator=(sdl_audio_system&& other) = delete;

	// non-default
	sdl_audio_system() = delete;

    concurrent::mutex_map<std::string, std::shared_ptr<sdl_music> > bgm_tracks;
};// class sdl_audio_system