#pragma once

#include <string>
#include <map>
#include <memory>
#include <cstdint>
#include <utility>

//forward declarations
namespace cw{
namespace sound{
	
	class music;
	class chunk;

}// namespace sound
}// namespace cw

namespace cw{
namespace sound{

class mixer{

class audio_callback{
public:
	static void channel_ended(int channel);
	static mixer* data;

};

public:
	mixer(int frequency, uint16_t format, int channels, int chunk_size);

	~mixer();

	void load_music(const std::string& name, const std::string& path);

	void play_music(const std::string& name, const int& loops = -1);

	bool is_playing_music(const std::string& name);

	void pause_music();

	void resume_music();

    void stop_music();

    void load_effect(const std::string& name, const std::string& path);

    void play_effect(const std::string& name);

	bool is_playing_effect(const std::string& name);

private:
	std::map<std::string, std::shared_ptr<music> > bgm_tracks;
	std::map<std::string, std::shared_ptr<chunk> > sfx_tracks;
	std::map<std::string, std::pair<int, bool> > bgm_info;
	std::map<std::string, std::pair<int, bool> > sfx_info;

};// class mixer

}// namespace sound
}// namespace cw