#pragma once 

#include <Crosswind/gui/widgets/detail/widget.h>
#include <Crosswind/textures/TextureManager.hpp>

namespace cw{


    /*
    class logical_texture{
    public:


    private:

        std::map<std::string, Texture> textures;
    };

*/
	class button: public widget{

    public:
        void load(std::string theme = std::string("blue"),
                int w = 40, int h = 20,
                int x = 50, int y = 50, int z = 0){


            ispressed   = false;
            isdraggable = false;
            width = w;
            height = h;
            position = std::shared_ptr<pointXYZ>(new pointXYZ(x, y, z));

            textures["on"] = texturemanager::loadTexture("button_on.png", width, height, theme + "/" + "button");
            textures["off"] = texturemanager::loadTexture("button_off.png", width, height, theme + "/" + "button");

            textures["current"] = textures["off"];

            setupActions();

        }

        //TODO disable default constructors, create friendship with widget.
        explicit button(bool default_settings = true){
            if(default_settings) { load(); }
        }

    private:

        void setupActions(){
            //TODO capture only required variables in lambda.
            on_mouse_down += [&](int button){
                if(!pressed()){
                    pressed() = true;
                    textures["current"] = textures["on"];
                }
            };

            on_mouse_move += [&](int x, int y){

                if(draggable() && pressed()){
                    getX() = x;
                    getY() = y;
                }

            };

            on_mouse_up += [&]{
                if(pressed()){
                    pressed() = false;
                    textures["current"] = textures["off"];
                }
            };
        }

    };

}