#pragma once 

#include <Crosswind/gui/widgets/detail/grid.hpp>
#include <Crosswind/gui/widgets/detail/widget.hpp>
#include <Crosswind/pools/texture_pool.hpp>

namespace cw{

    class horizontal_group: public grid, public widget{
    public:
        horizontal_group(): major_x(0.0){

            textures.clear(); //Removing default textures.



        }

        void set_major_x(double x){
            major_x.store(x);
        }

        double get_major_x(){
            set_major_x(this->get_x());

            for(auto& element: elements){
                if(element->get_x() > major_x.load()){
                    set_major_x(element->get_x());
                }
            }

            return major_x.load();
        }

        void update(double delta) override{

            for(auto& element : elements){
                element->set_x(this->get_x());
                element->set_y(this->get_y());

                element->set_x(get_major_x() + get_grid_offset());
                element->set_y(this->get_y() + get_grid_offset());

                if(get_auto_resize()){

                }

                element->update(delta);
            }

        }

        std::atomic<double> major_x;
    };

    class vertical_group: public grid, public widget{

    public:
        vertical_group(): major_y(0.0){

            textures.clear(); //Removing default textures.


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

        void set_major_y(double y){
            major_y.store(y);
        }

        double get_major_y(){
            set_major_y(this->get_real_y());

            for(auto& element: elements){
                if(element->get_real_y() > major_y.load()){
                    set_major_y(element->get_real_y());
                }
            }

            return major_y.load();
        }

        void init(std::shared_ptr<init_flags> flags = nullptr){
        }

        void update(double delta) override{

            for(auto& element : elements){

                std::function<double(double, double)> get_coordinate = [](double percent, double dimension){

                    return dimension * percent;

                };

                double x_cord = get_coordinate(element->get_real_x(), this->get_width());
                double y_cord = get_coordinate(element->get_real_y(), this->get_height());


                element->set_x(this->get_x() + get_grid_offset() + x_cord);
                element->set_y(this->get_y() + get_grid_offset() + this->get_major_y() + y_cord);

                element->update(delta);
            }

        }

    private:
        std::atomic<double> major_y;
    };

    class panel: public grid, public widget, public gui_element{

    public:
        panel(){
            switch_texture("current", texture_pool::loadTexture("panel.png", get_width(), get_height(), get_theme() + "/" + "panel"));
            switch_texture("previous", get_texture("current"));
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


    };

}