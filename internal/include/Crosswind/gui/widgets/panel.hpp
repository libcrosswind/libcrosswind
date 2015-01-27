#pragma once 

#include <Crosswind/gui/widgets/detail/grid.hpp>
#include <Crosswind/gui/widgets/detail/widget.hpp>
#include <Crosswind/pools/texture_pool.hpp>

namespace cw{

    class panel: public grid, public widget, public gui_element{

    public:
        void init(std::shared_ptr<init_flags> flags = nullptr){
            //TODO assert for each required field.

            switch_texture("current", texture_pool::loadTexture("panel.png", get_width(), get_height(), get_theme() + "/" + "panel"));
            switch_texture("previous", get_texture("current"));
            set_x_offset(12.0);
            set_y_offset(14.0);

            on_attached += [this](){
                //TODO

                return [this](std::shared_ptr<widget> element){
                    element->set_x(this->get_x() + get_x_offset());
                    element->set_y(this->get_y() + get_y_offset());
                };

            }();

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

            get_texture("current")->render_to_target(get_x(), get_y(), render_texture);
            for(auto& element : elements){
                element->render(render_texture);
            }

        }

        void loop(){

        }

    };

}