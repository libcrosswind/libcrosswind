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

            texture_clear_buffer = std::shared_ptr<cimg_library::CImg<unsigned char> >
                    (new cimg_library::CImg<unsigned char>(width, height, depth, bpp, 0));

        }

        texture(std::string path, double width, double height){
            texture_data = std::shared_ptr<cimg_library::CImg<unsigned char> >
                    (new cimg_library::CImg<unsigned char>());
            texture_clear_buffer = std::shared_ptr<cimg_library::CImg<unsigned char> >
                    (new cimg_library::CImg<unsigned char>());

            texture_data->assign(path.c_str());
            texture_clear_buffer->assign(path.c_str());
        }

        void clear(){
            std::lock_guard<std::mutex> lock(texture_mutex);
            (*texture_data).fill(0);
            (*texture_clear_buffer).fill(0);

        }


        void draw_text(double x, double y, std::string text, std::shared_ptr<color_rgb> color){
            std::lock_guard<std::mutex> lock(texture_mutex);
            (*texture_data) = (*texture_clear_buffer);

/*            cimg_library::CImg<unsigned char> imgtext; //@TODO draw aligned.
            unsigned char dcolor = 1;

            imgtext.draw_text(0,0,text.c_str(),&dcolor);

            (*texture_data).draw_image(0, 0, imgtext);*/
            (*texture_data).draw_text(x - 5*text.size()/2, y - 4, text.c_str(), color->data()); //Font size is 8x8

        }

        void resize(double width, double height){
            std::lock_guard<std::mutex> lock(texture_mutex);
            (*texture_data).resize(width, height, -100, -100, 3); //Linear interpolation works best for PNG
            (*texture_clear_buffer).resize(width, height, -100, -100, 3);
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
        std::shared_ptr<cimg_library::CImg<unsigned char> > texture_data;
        std::shared_ptr<cimg_library::CImg<unsigned char> > texture_clear_buffer; //Exact copy without modifications.

    };

}
	