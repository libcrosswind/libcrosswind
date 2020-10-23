#pragma once

#include <string>
#include "glm/glm.hpp"

namespace cw{
namespace configuration{

struct settings{

	struct application_settings{
		int flags;
	} application;

    struct audio_settings{

        int frequency;
        uint16_t format;
        int channels;
        int chunk_size;

    } audio;

    struct video_settings{
        std::string window_title;
        glm::i32vec2  window_position;
        float fps;
        int video_flags;
        int window_flags;
    } video;

    struct window_settings{
        std::string title;
        glm::i32vec2  resolution;
        bool resizable;
    } window;

    /*struct{

        glm::vec3 gravity;
        glm::vec3 scale;
        glm::vec3 unit_value;

    } physics;*/

    settings();

};// struct settings

}// namespace configuration
}// namespace cw
