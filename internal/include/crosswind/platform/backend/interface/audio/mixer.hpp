#pragma once

#include <string>
#include <memory> 

namespace cw{
namespace platform{
namespace backend{
namespace interface{
namespace audio{

	class mixer_interface;

}// namespace audio
}// namespace interface
}// namespace backend
}// namespace platform
}// namespace cw

class cw::platform::backend::interface::audio::mixer_interface{
public:
	virtual void load_music(const std::string& name, const std::string& path) = 0;
	virtual void play_music(const std::string& name) = 0;
	virtual void pause_music(const std::string& name) = 0;

	virtual void load_effect(const std::string& name, const std::string& path) = 0;
	virtual void play_effect(const std::string& name) = 0;

private:
	std::map<std::string, std::shared_ptr<music> > bgm_tracks;
	std::map<std::string, std::shared_ptr<chunk> > sfx_tracks;

private:
	// non-copyable
	mixer_interface(const mixer_interface& other) = delete;
	mixer_interface& operator=(const mixer_interface& other) = delete;

	// non-movable
	mixer_interface(mixer_interface&& other) = delete;
	mixer_interface& operator=(mixer_interface&& other) = delete;
};// class mixer_interface