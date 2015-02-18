#include <SDL.h>
#include <stdio.h>


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#include <memory>

template<typename Creator, typename Destructor, typename... Arguments>
auto make_resource(Creator c, Destructor d, Arguments&&... args);



int main(int argc, char **argv) {

    auto window = make_resource(SDL_CreateWindow, SDL_DestroyWindow, "App Name", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);


}