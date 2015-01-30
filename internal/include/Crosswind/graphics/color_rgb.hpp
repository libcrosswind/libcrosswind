#include <array> 

namespace cw{
	class color_rgb{
	public:
		color_rgb(unsigned char r, unsigned char g, unsigned char b){
			color = {r, g, b};
		}

		unsigned char* data(){ return color.data(); }

	private:	
		std::array<unsigned char, 3> color;
	};
}