#include "crosswind/sound/chunk.hpp"

cw::sound::chunk::chunk(const std::string& file_path):
data(Mix_LoadWAV_RW, Mix_FreeChunk, SDL_RWFromFile(file_path.c_str(), "rb"), 1) {

}
