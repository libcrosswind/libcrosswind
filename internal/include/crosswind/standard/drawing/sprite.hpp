#pragma once

namespace cw{
namespace standard{
namespace graphics{

	class sprite;

}// namespace graphics
}// namespace standard
}// namespace cw

class cw::standard::graphics::sprite{
public:

    sprite(){
        
    }

protected:
    cacheable<std::shared_ptr<texture> > textures;
};// class sprite
