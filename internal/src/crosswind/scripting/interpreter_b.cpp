#include <iostream>
#include <stdexcept>

#include "chaiscript/chaiscript.hpp"
#include "chaiscript/chaiscript_stdlib.hpp"
#include "glm/glm.hpp"

#include "crosswind/scripting/interpreter.hpp"

#include "crosswind/engine.hpp"
#include "crosswind/composition/core.hpp"
#include "crosswind/composition/stage.hpp"
#include "crosswind/composition/scene.hpp"
#include "crosswind/composition/camera.hpp"
#include "crosswind/composition/group.hpp"
#include "crosswind/composition/actor.hpp"
#include "crosswind/platform/application.hpp"
#include "crosswind/platform/filesystem.hpp"
#include "crosswind/platform/input.hpp"
#include "crosswind/graphical/video.hpp"
#include "crosswind/graphical/object/model.hpp"
#include "crosswind/graphical/object/text.hpp"
#include "crosswind/graphical/opengl/renderer.hpp"
#include "crosswind/graphical/opengl/window.hpp"
#include "crosswind/simulation/physics.hpp"

void cw::scripting::interpreter::bind_graphical(){

	// model
	chai->add(chaiscript::fun(&cw::graphical::object::model::change_animation), "change_animation");
//	chai->add(chaiscript::fun(&cw::graphical::object::model::set_origin), "set_origin");
//	chai->add(chaiscript::fun(&cw::graphical::object::model::get_origin), "get_origin");
	chai->add(chaiscript::fun(&cw::graphical::object::model::set_size), "set_size");
//	chai->add(chaiscript::fun(&cw::graphical::object::model::get_size), "get_size");
	chai->add(chaiscript::fun(&cw::graphical::object::text::set_size), "set_size");
	chai->add(chaiscript::fun(&cw::graphical::object::text::get_size), "get_size");
	chai->add(chaiscript::fun(&cw::graphical::object::text::get_text), "get_text");

}

void cw::scripting::interpreter::bind_composition(){

	// inheritance
	// logic_component
	chai->add(chaiscript::fun(&cw::composition::detail::logic_component::construct), "construct");

	// named_component
	chai->add(chaiscript::fun(&cw::composition::detail::named_component::set_name), "set_name");
	chai->add(chaiscript::fun(&cw::composition::detail::named_component::get_name), "get_name");

	// spatial_component
	chai->add(chaiscript::fun(&cw::composition::detail::spatial_component::set_origin), "set_origin");
	chai->add(chaiscript::fun(&cw::composition::detail::spatial_component::get_origin), "get_origin");
	chai->add(chaiscript::fun(&cw::composition::detail::spatial_component::set_size), "set_size");
	chai->add(chaiscript::fun(&cw::composition::detail::spatial_component::get_size), "get_size");
	chai->add(chaiscript::fun(&cw::composition::detail::spatial_component::set_alpha), "set_alpha");
	chai->add(chaiscript::fun(&cw::composition::detail::spatial_component::get_alpha), "get_alpha");


	// inheritance bindings
	// scene
	chai->add(chaiscript::base_class<cw::composition::detail::logic_component, cw::composition::scene>());
	chai->add(chaiscript::base_class<cw::composition::detail::named_component, cw::composition::scene>());

	// group
	chai->add(chaiscript::base_class<cw::composition::detail::named_component,   cw::composition::group>());
	chai->add(chaiscript::base_class<cw::composition::detail::spatial_component, cw::composition::group>());
	chai->add(chaiscript::base_class<cw::composition::detail::logic_component, cw::composition::group>());

	// actor
	chai->add(chaiscript::base_class<cw::composition::detail::named_component, cw::composition::actor>());
	chai->add(chaiscript::base_class<cw::composition::detail::spatial_component, cw::composition::actor>());
	chai->add(chaiscript::base_class<cw::composition::detail::logic_component, cw::composition::actor>());

	// stage
	chai->add(chaiscript::fun(&cw::composition::stage::create_scene), "create_scene");
	chai->add(chaiscript::fun(&cw::composition::stage::create_camera), "create_camera");
	chai->add(chaiscript::fun(&cw::composition::stage::create_actor), "create_actor");
	chai->add(chaiscript::fun(&cw::composition::stage::create_group), "create_group");
	chai->add(chaiscript::fun(&cw::composition::stage::add_scene), "add_scene");
	chai->add(chaiscript::fun(&cw::composition::stage::get_scene), "get_scene");

//	chai->add(chaiscript::fun(&cw::composition::stage::remove_scene), "remove_scene");
//	chai->add(chaiscript::fun(&cw::composition::stage::swap_scene), "swap_scene");
	chai->add(chaiscript::fun(&cw::composition::stage::load_scene), "load_scene");
//	chai->add(chaiscript::fun(&cw::composition::stage::unload_scene), "unload_scene");

	// scene
//	chai->add(chaiscript::fun(&cw::composition::scene::set_bool), "set_bool");
//	chai->add(chaiscript::fun(&cw::composition::scene::get_bool), "get_bool");
//	chai->add(chaiscript::fun(&cw::composition::scene::set_float), "set_float");
//	chai->add(chaiscript::fun(&cw::composition::scene::get_float), "get_float");
//	chai->add(chaiscript::fun(&cw::composition::scene::set_int), "set_int");
//	chai->add(chaiscript::fun(&cw::composition::scene::get_int), "get_int");
	chai->add(chaiscript::fun(&cw::composition::scene::add_camera), "add_camera");
	chai->add(chaiscript::fun(&cw::composition::scene::get_camera), "get_camera");
	chai->add(chaiscript::fun(&cw::composition::scene::add_group), "add_group");
	chai->add(chaiscript::fun(&cw::composition::scene::load_group), "load_group");
	chai->add(chaiscript::fun(&cw::composition::scene::add_actor), "add_actor");
//	chai->add(chaiscript::fun(&cw::composition::scene::get_actor), "get_actor");
//  chai->add(chaiscript::fun(&cw::composition::scene::remove_actor), "remove_actor");
	chai->add(chaiscript::fun(&cw::composition::scene::load_actor), "load_actor");
//	chai->add(chaiscript::fun(&cw::composition::scene::unload_actor), "unload_actor");


	// camera
//	chai->add(chaiscript::fun(&cw::composition::camera::set_position), "set_position");
	chai->add(chaiscript::fun(&cw::composition::camera::convert_screen_to_world), "convert_screen_to_world");

	// group
	chai->add(chaiscript::fun(&cw::composition::group::add_group), "add_group");
	chai->add(chaiscript::fun(&cw::composition::group::add_actor), "add_actor");
	chai->add(chaiscript::fun(&cw::composition::group::get_actor), "get_actor");
	chai->add(chaiscript::fun(&cw::composition::group::remove_actor), "remove_actor");

	// actor
	chai->add(chaiscript::fun(&cw::composition::actor::add_text), "add_text");
	chai->add(chaiscript::fun(&cw::composition::actor::get_text), "get_text");
	chai->add(chaiscript::fun(&cw::composition::actor::remove_text), "remove_text");

	chai->add(chaiscript::fun(&cw::composition::actor::add_model), "add_model");
	chai->add(chaiscript::fun(&cw::composition::actor::get_model), "get_model");

}
