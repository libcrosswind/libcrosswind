#pragma once

#include <CImg/CImg.h>

#include <string>
#include <memory>
#include <mutex>

#include <crosswind/core/concurrent/mutexed_property.hpp>
#include <Crosswind/standard/drawing/rgb.hpp>

namespace cw{
namespace standard{
namespace drawing{
    template<class T>
    class texture;

}// namespace drawing
}// namespace standard
}// namespace cw

template<class T>
class cw::standard::drawing::texture{
public:
    texture(double width, double height, double depth = 1, double bpp = 4){
        
        data = cimg_library::CImg<T>(width, height, depth, bpp, 255);
        clear_buffer = cimg_library::CImg<T>(width, height, depth, bpp, 255);

    }

    texture(std::string path, double width, double height){
        data = cimg_library::CImg<T>();
        clear_buffer = cimg_library::CImg<T>();

        data.acquire().assign(path.c_str());
        clear_buffer.acquire().assign(path.c_str());
        
        data.release();
        clear_buffer.release();
    }
 

    void clear(){

        auto& local_texture = data.acquire();
        auto& buffer = clear_buffer.acquire();

        local_texture.fill(0);
        buffer.fill(0);

        data.release();
        clear_buffer.release();

    }


    void draw_text(double x, double y, std::string text, std::shared_ptr<rgb> color){

        auto& local_texture = data.acquire();
        auto& buffer = clear_buffer.acquire();

        local_texture = buffer;

        auto imgtext =
                cimg_library::CImg<T>().draw_text(0,0,text.c_str(), color->array().data(), NULL).
                        resize(-100,-100, 1, 4);

        //@TODO implement alignment.
        local_texture.draw_image  (x - imgtext.width()/2,
                                   y - imgtext.height()/2,
                                   0,
                                   0,
                                   imgtext,
                                   imgtext.get_channel(3),
                                   1,
                                   255);

        data.release();
        clear_buffer.release();

    }

    void resize(double width, double height){

        auto& local_texture = data.acquire();
        auto& buffer  = clear_buffer.acquire();

        local_texture.resize(width, height, -100, -100, 3); //Linear interpolation works best for PNG
        buffer.resize(width, height, -100, -100, 3);

        data.release();
        clear_buffer.release();

    }

    void render_to_target(double x, double y, texture& target){

        auto& target_texture = target.data.acquire();
        auto& local_texture = data.acquire();

        target_texture.draw_image(x, y, 0, 0, local_texture);

        data.release();
        target.data.release();

    }


    core::concurrent::mutexed_property<std::string> name;
    core::concurrent::mutexed_property<cimg_library::CImg<T> > data;

private:
    core::concurrent::mutexed_property<cimg_library::CImg<T> > clear_buffer;

};// class texture
