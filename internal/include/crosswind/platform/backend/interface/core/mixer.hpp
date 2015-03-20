#pragma once

#include <string>

namespace cw{
namespace platform{
namespace backend{
namespace interface{
namespace core{

	class mixer;

}// namespace core
}// namespace interface
}// namespace backend
}// namespace platform
}// namespace cw

class cw::platform::backend::interface::core::mixer{
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

private:
	// non-copyable
	mixer(const mixer& other) = delete;
	mixer& operator=(const mixer& other) = delete;

	// non-movable
	mixer(mixer&& other) = delete;
	mixer& operator=(mixer&& other) = delete;
};// class mixer