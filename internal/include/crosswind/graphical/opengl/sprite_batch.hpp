#pragma once

#include <vector>
#include <memory>

// forward declarations
namespace cw{
namespace graphical{
namespace opengl{
	
	class render_batch;

}// namespace opengl
}// namespace graphical
}// namespace cw

namespace cw{
namespace graphical{
namespace object{
	
	class sprite;

}// namespace object
}// namespace graphical
}// namespace cw

namespace cw{
namespace graphical{
namespace opengl{

class sprite_batch{
public:
	sprite_batch();

	void clear();

	void upload(std::shared_ptr<object::sprite> render_sprite);

	void create();

	void draw();

private:
	void create_vertex_array();

	void create_batch_list();

	std::vector<std::shared_ptr< render_batch   > > batch_list;
	std::vector<std::shared_ptr< object::sprite > > sprite_list;

	uint32_t vao_id;
	uint32_t vbo_id;
};


}// namespace opengl
}// namespace graphical
}// namespace cw
