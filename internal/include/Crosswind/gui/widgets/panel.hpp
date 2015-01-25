#pragma once 

#include <Crosswind/gui/widgets/detail/grid.hpp>
#include <Crosswind/gui/widgets/detail/widget.hpp>
#include <Crosswind/pools/texture_pool.hpp>

namespace cw{

    class panel: public grid, public widget, public gui_element{

    public:
        void init(FlagSet<InitFlags> flags = FlagSet<InitFlags>()){
            //TODO assert for each required field.
            textures["blank"] = std::shared_ptr<texture>(new texture(get_width(), get_height(), get_depth(), 4));
            textures["current"] = texture_pool::loadTexture("panel.png", get_width(), get_height(), get_theme() + "/" + "panel");

            textures["previous"] = textures["current"];


            on_mouse_down += [this](int x, int y, int button){

                for(auto& element : elements){
                    element->on_mouse_down(x, y, button);
                }

            };


            on_mouse_move += [this](int x, int y){

                for(auto& element : elements){
                    element->on_mouse_move(x, y);
                }

            };

            on_mouse_up += [this](int x, int y){

                for(auto& element : elements){
                    element->on_mouse_up(x, y);
                }

            };

        }

        void show(){
            set_visible(true);
            switch_texture("current", textures["previous"]);
        }

        void hide(){
            set_visible(false);
            switch_texture("previous", textures["current"]);
            switch_texture("current", textures["blank"]);

        }

        void update(double delta){

            /*     frame_counter += delta;

                 if (frameCounter >= (max_fps)) {
                     frameCounter = 0.f;
                 }
             */

        }

        void render(std::shared_ptr<texture> render_texture){

            texture_mutex.lock();
            textures["current"]->render_to_target(get_x(), get_y(), render_texture);
            for(auto& element : elements){
                element->render(render_texture);
            }
            texture_mutex.unlock();

        }

        void loop(){

        }

    };

}