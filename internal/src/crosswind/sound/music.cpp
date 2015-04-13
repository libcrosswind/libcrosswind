#include "crosswind/sound/music.hpp"

cw::sound::music::music(const std::string& file_path): 
data(Mix_LoadMUS, Mix_FreeMusic, file_path.c_str()) {

}