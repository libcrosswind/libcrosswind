#pragma once 

#include <Crosswind/gui/widgets/detail/widget.h>

namespace cw{
	
	class button: public widget{

    public:
        void load(std::string filename = std::string(settings::path::ui + "button/button_off.png"),
                int w = 20, int h = 20,
                int x = 50, int y = 50, int z = 0){

            width = w;
            height = h;
            position = std::shared_ptr<pointXYZ>(new pointXYZ(x, y, z));

            data.assign(filename.c_str());
            data.resize(width, height);

            on_mouse_down += [&](int button){
                data.assign(std::string(settings::path::ui + "button/button_on.png").c_str());
                data.resize(width, height);
            };

            on_mouse_up += [&]{
                data.assign(std::string(settings::path::ui + "button/button_off.png").c_str());
                data.resize(width, height);
            };

        }

        button(){ load(); }
	};

}