#include "crosswind/settings.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

cw::configuration::settings::settings(){

    application.flags        = SDL_INIT_VIDEO | SDL_INIT_AUDIO;

    audio.frequency          = 44100;
    audio.format             = MIX_DEFAULT_FORMAT;
    audio.channels           = 2;
    audio.chunk_size         = 2048;

    video.window_title      = "Main";
    video.window_position   = glm::i32vec2(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    video.fps               = 60.0f;
    video.video_flags       = IMG_INIT_PNG;
    video.window_flags      = SDL_WINDOW_OPENGL;

    window.title            = "Main";
    window.resizable        = false;
    window.resolution       = glm::i32vec2(640, 480);

    physics.gravity         = glm::vec3(0.0f, -10.0f, 0.0f);
    physics.scale           = glm::vec3(0.01f, 0.01f, 0.01f);

    glm::vec3 unit_value(1.0f, 1.0f, 1.0f);
    physics.unit_value      = unit_value;

}

