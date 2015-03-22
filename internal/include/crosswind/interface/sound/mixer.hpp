#pragma once

#include <string>

namespace cw{
namespace interface{
namespace sound{
	
	class mixer;

}// namespace sound
}// namespace interface
}// namespace cw

class cw::interface::sound::mixer{
public:
	mixer(){

	}

	virtual void load_music(const std::string& name, const std::string& path) = 0;
	virtual void play_music(const std::string& name) = 0;
	virtual bool is_playing_music(const std::string& name) = 0;
	virtual void pause_music() = 0;

	virtual void load_effect(const std::string& name, const std::string& path) = 0;
	virtual void play_effect(const std::string& name) = 0;
	virtual bool is_playing_effect(const std::string& name) = 0;
};// class mixer