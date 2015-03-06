#pragma once

#include <memory>

/*
#include <crosswind/concurrent/mutex_container.hpp>
#include <crosswind/simulation/detail/mapping/animation_mapping.hpp>
#include <crosswind/simulation/detail/mapping/sprite_mapping.hpp>
#include <crosswind/simulation/detail/mapping/texture_mapping.hpp>
*/

namespace cw{
namespace simulation{
namespace detail{

	class graphical_actor;

}// namespace detail
}// namespace simulation
}// namespace cw

class cw::simulation::detail::graphical_actor{
public:
	graphical_actor(){

	}

	virtual void draw() = 0;

	template<typename T, typename U>
    void store_graphical_item(T& mm, const std::string& name, std::shared_ptr<U> new_Item){
/*        auto& container = mm.data.acquire();

        container[name] = new_Item;

        mm.data.release();*/
    }

   	template<typename T>
    void swap_graphical_item(T& mm, const std::string& previous_item, const std::string& new_Item){
/*        auto& container = mm.data.acquire();

        if(container[previous_item] != container[new_Item]){
            container[previous_item] = container[new_Item];
        }

        mm.data.release();*/
    }

//    concurrent::mutex_map<std::string, std::shared_ptr< detail::animation_mapping > > animations;
//    concurrent::mutex_map<std::string, std::shared_ptr< detail::sprite_mapping    > > sprites;
//    concurrent::mutex_map<std::string, std::shared_ptr< detail::texture_mapping   > > textures;
};// class graphical_actor
