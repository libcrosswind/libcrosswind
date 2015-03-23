#pragma once

#include <vector>

#include <crosswind/interface/graphical/detail/sprite.hpp>
#include <crosswind/interface/graphical/detail/render_batch.hpp>

namespace cw{
namespace interface{
namespace graphical{
namespace detail{

	class sprite_batch;

}// namespace detail
}// namespace graphical
}// namespace interface
}// namespace cw

class cw::interface::graphical::detail::sprite_batch{
	typedef std::map<std::string, std::shared_ptr<interface::graphical::detail::sprite> > sprite_map;
public:
	sprite_batch(){
		create_vertex_array();
	}

	void clear() = 0;

	virtual void upload(const sprite_map& render_list) = 0;
	virtual void create() = 0;
	virtual void draw() = 0;

private:
	virtual void create_vertex_array() = 0;

	virtual void create_batch_list() = 0;

	std::vector<std::shared_ptr<interface::graphical::detail::render_batch> > 	batch_list;
	std::vector<std::shared_ptr<interface::graphical::detail::sprite> > 		sprite_list;
};