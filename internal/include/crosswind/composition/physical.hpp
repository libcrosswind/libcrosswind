/*#pragma once

#include <string>
#include <memory>
#include <map>
#include <glm/glm.hpp>

#include "tileson.hpp"

#include "crosswind/geometry/rectangle.hpp"

// forward declarations
namespace cw {
	namespace simulation {
		namespace detail {
			class body;
			class character;
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

		class physical {
			typedef std::map<std::string, std::shared_ptr<simulation::detail::body> > body_map;
			typedef std::map<std::string, std::shared_ptr<simulation::detail::character> >  character_map;

		public:
			physical(std::shared_ptr<core> core, const std::string& name);
			~physical();

			void add_rigid_body(const std::string& body_name,
								const glm::vec3& origin,
								const glm::vec3& size,
								const float& mass);

			virtual std::shared_ptr<simulation::detail::body> get_rigid_body(const std::string& body_name);
			
			virtual void remove_rigid_body(const std::string& body_name);

			virtual void add_character(const std::string& character_name,
				const glm::vec3& origin,
				const glm::vec2& size,
				const float& step_height);

			virtual std::shared_ptr<simulation::detail::character> get_character(const std::string& character_name);

			virtual void remove_character(const std::string& character_name);

		public:
			std::string name;

			cw::geometry::rectangle bbox;


		private:
			std::shared_ptr<core> core;
		protected:
			body_map        bodies;
			character_map   characters;

		};// class tilemap

	}// namespace composition
}// namespace cw
*/