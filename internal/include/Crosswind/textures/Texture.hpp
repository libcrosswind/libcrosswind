#pragma once

#include <CImg/CImg.h>

#include <string>
#include <memory>


namespace cw{

	class texture{
    public: //TODO disable default constructors, create friendship with texture manager.
        texture(std::string name, int width, int height){
            texturedata = std::shared_ptr<cimg_library::CImg<unsigned char> >
                    (new cimg_library::CImg<unsigned char>());
            texturedata->assign(name.c_str());
            texturedata->resize(width, height);
        }

        int getWidth() { return texturedata->width(); }
        int getHeight() { return texturedata->height(); }

        std::shared_ptr<cimg_library::CImg<unsigned char> > data(){ return texturedata; }
	private:
		std::shared_ptr<cimg_library::CImg<unsigned char> > texturedata;
	};

}
	