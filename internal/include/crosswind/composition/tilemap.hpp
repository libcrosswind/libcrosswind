#pragma once

#include <string>
#include <memory>
#include <map>

#include "tileson.hpp"

// forward declarations
namespace cw {
	namespace graphical {
		namespace opengl {
			class renderer;
			class texture;
		}
	}
}

namespace cw {
	namespace graphical {
		namespace object {
			class sprite;
		}
		
	}
}

// forward declarations
namespace cw {
	namespace composition {

		class core;

	}// namespace composition
}// namespace cw



namespace cw {
	namespace composition {

		class tilemap {
		public:
			tilemap(std::shared_ptr<core> core, const std::string& path);
			~tilemap();

			virtual void draw(std::shared_ptr<cw::graphical::opengl::renderer> renderer);

		public:
			std::vector<tson::Object> objects;
			std::unique_ptr<tson::Map> map;

		private:
			std::shared_ptr<core> core;
			std::vector<std::shared_ptr<cw::graphical::object::sprite>> sprites;
			std::map<std::string, std::shared_ptr<cw::graphical::opengl::texture> > textures;
		};// class tilemap

	}// namespace composition
}// namespace cw