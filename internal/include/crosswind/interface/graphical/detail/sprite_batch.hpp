#pragma once

#include <map>
#include <memory>
#include <string>
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
public:
	sprite_batch(){
	}

	virtual void clear() = 0;

	virtual void upload(const std::map<std::string, std::shared_ptr<sprite> >& sprite_map) = 0;
	virtual void create() = 0;
	virtual void draw() = 0;

protected:
	virtual void create_vertex_array() = 0;

	virtual void create_batch_list() = 0;

	std::vector<std::shared_ptr<render_batch> > batch_list;
	std::vector<std::shared_ptr<sprite> > 		sprite_list;
};