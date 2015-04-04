#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <glm/glm.hpp>

namespace cw{
namespace interface{

    struct settings;
    
}// namespace interface
}// namespace cw


struct cw::interface::settings{

    struct{

        int flags;

    } application;

    struct{

        int frequency;
        uint16_t format;
        int channels;
        int chunk_size;

    } audio;

    struct video_settings{

        std::string window_title;
        glm::i32vec2  window_position;
        glm::i32vec2  default_resolution;
        glm::i32vec2  window_resolution;

        int image_flags;
        int window_flags;
        float fps;

    } video;

    struct{

        glm::vec3 gravity;
        glm::vec3 scale;
        glm::vec3 unit_value;

    } physics;

    glm::i32vec4  audio_settings;

    settings(){
        application.flags        = SDL_INIT_VIDEO | SDL_INIT_AUDIO;

        audio.frequency          = 44100;
        audio.format             = MIX_DEFAULT_FORMAT;
        audio.channels           = 2;
        audio.chunk_size         = 2048;

        video.window_title       = "Main";
        video.window_position    = glm::i32vec2(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        video.default_resolution = glm::i32vec2(320, 224);
        video.window_resolution  = glm::i32vec2(640, 480);
        video.image_flags        = IMG_INIT_PNG;
        video.window_flags       = SDL_WINDOW_OPENGL;
        video.fps                = 60.0f;

        auto world_scale =
                glm::vec3(video.window_resolution[0] / video.default_resolution[0],
                          video.window_resolution[1] / video.default_resolution[1], 1.0);

        physics.gravity         = glm::vec3(0.0f, -10.0f, 0.0f);
        physics.scale           = glm::vec3(0.01f, 0.01f, 0.01f);

        glm::vec3 unit_value(1.0f, 1.0f, 1.0f);
        unit_value.x *= world_scale.x;
        unit_value.y *= world_scale.y;
        unit_value.z *= world_scale.z;

        physics.unit_value      = unit_value;

    }

};// struct settings