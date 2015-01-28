#pragma once

#include <CImg/CImg.h>

#include <string>
#include <memory>
#include <mutex>

#include <Crosswind/gui/widgets/detail/display_target.hpp>
#include <Crosswind/graphics/color_rgb.hpp>

namespace cw{

	class texture{
    public:

        texture(double width, double height, double depth, double bpp){
            texture_data = std::shared_ptr<cimg_library::CImg<unsigned char> >
                    (new cimg_library::CImg<unsigned char>(width, height, depth, bpp, 0));
        }

        texture(std::string path, double width, double height){
            texture_data = std::shared_ptr<cimg_library::CImg<unsigned char> >
                    (new cimg_library::CImg<unsigned char>());
            texture_data->assign(path.c_str());
            texture_data->resize(width, height);
        }

        void draw_text(double x, double y, std::string text, std::shared_ptr<color_rgb> color){
            std::lock_guard<std::mutex> lock(texture_mutex);
            (*texture_data).draw_text(x, y, text.c_str(), color->data()); //TODO check if guard protects pointer or variable inside.

        }

        void resize(double width, double height){
            std::lock_guard<std::mutex> lock(texture_mutex);
            (*texture_data).resize(width, height); //TODO check if guard protects pointer or variable inside.
        }

        void render_to_target(double x, double y, std::shared_ptr<texture> target){

            std::lock_guard<std::mutex> lock(texture_mutex);
            target->texture_data->draw_image(x, y, *texture_data);
        }

        void render_to_display(std::shared_ptr<display_target> target){
            std::lock_guard<std::mutex> lock(texture_mutex);
            target->display(*texture_data);
        }

	private:
        std::mutex texture_mutex;
		std::shared_ptr<cimg_library::CImg<unsigned char> > texture_data; //Check if can be used with atomic.
	};

}
	