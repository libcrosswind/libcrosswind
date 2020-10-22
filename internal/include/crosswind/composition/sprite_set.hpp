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

		class sprite_set {
		public:
			sprite_set(std::shared_ptr<core> core, const std::string& path);
			~sprite_set();

			virtual void logic(const float& delta) = 0;

			virtual void draw(std::shared_ptr<cw::graphical::opengl::renderer> renderer) = 0;

		private:
			std::shared_ptr<core> core;
			std::unique_ptr<tson::Map> map;
			std::map<std::string, std::shared_ptr<cw::graphical::opengl::texture> > textures;
		protected:
			std::vector<std::shared_ptr<cw::graphical::object::sprite>> sprites;
			
		};// class tilemap

	}// namespace composition
}// namespace cw