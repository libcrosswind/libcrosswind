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




namespace cw{
namespace scripting{

namespace {

	float c_clamp(const float& value, const float& min_value, const float& max_value){
		return glm::clamp(value, min_value, max_value);
	}

	float c_radians(const float& degrees){
		return glm::radians(degrees);
	}

	float c_sin(const float& value){
		return glm::sin(value);
	}

}// anonymous namespace

}// namespace scripting
}// namespace cw

cw::scripting::interpreter::interpreter(): 
chai(new chaiscript::ChaiScript(chaiscript::Std_Lib::library())){

	bind_glm();
	bind_settings();
	bind_engine();
	bind_filesystem();
	bind_input();
	bind_video();
	bind_sound();
	bind_graphical();
	bind_composition();

}

void cw::scripting::interpreter::eval_file(const std::string& filename){

	try {

		chai->eval_file(filename);

	} catch(std::runtime_error& err) {

		std::cout << err.what() << std::endl;

	}

}


void cw::scripting::interpreter::bind_glm(){

	// data types
	// vec2
	chai->add(chaiscript::user_type<glm::vec2>(), "vec2" );
	chai->add(chaiscript::constructor<glm::vec2()>(), "vec2");
	chai->add(chaiscript::constructor<glm::vec2(float, float)>(), "vec2");
	chai->add(chaiscript::fun(&glm::vec2::x), "x");
	chai->add(chaiscript::fun(&glm::vec2::y), "y");

	// vec3
	chai->add(chaiscript::user_type<glm::vec3>(), "vec3" );
	chai->add(chaiscript::constructor<glm::vec3()>(), "vec3");
	chai->add(chaiscript::constructor<glm::vec3(float, float, float)>(), "vec3");
	chai->add(chaiscript::fun(&glm::vec3::x), "x");
	chai->add(chaiscript::fun(&glm::vec3::y), "y");
	chai->add(chaiscript::fun(&glm::vec3::z), "z");

	// vec4
	chai->add(chaiscript::user_type<glm::vec4>(), "vec4" );
	chai->add(chaiscript::constructor<glm::vec4()>(), "vec4");
	chai->add(chaiscript::constructor<glm::vec4(float, float, float, float)>(), "vec4");
	chai->add(chaiscript::fun(&glm::vec4::x), "x");
	chai->add(chaiscript::fun(&glm::vec4::y), "y");
	chai->add(chaiscript::fun(&glm::vec4::z), "z");
	chai->add(chaiscript::fun(&glm::vec4::w), "w");

	// i32vec2
	chai->add(chaiscript::user_type<glm::i32vec2>(), "i32vec2" );
	chai->add(chaiscript::constructor<glm::i32vec2()>(), "i32vec2");
	chai->add(chaiscript::constructor<glm::i32vec2(int, int)>(), "i32vec2");
	chai->add(chaiscript::fun(&glm::i32vec2::x), "x");
	chai->add(chaiscript::fun(&glm::i32vec2::y), "y");

	// functions
	chai->add(chaiscript::fun(&c_clamp), "clamp");
	chai->add(chaiscript::fun(&c_radians), "radians");
	chai->add(chaiscript::fun(&c_sin), "sin");

}

void cw::scripting::interpreter::bind_settings(){

	// constructor
	chai->add(chaiscript::user_type<cw::configuration::settings>(), "settings" );
	chai->add(chaiscript::constructor<cw::configuration::settings()>(), "settings");

	// members
	chai->add(chaiscript::fun(&cw::configuration::settings::window), "window");
	chai->add(chaiscript::fun(&cw::configuration::settings::window_settings::title), "title");
//	chai->add(chaiscript::fun(&cw::configuration::settings::video_settings::window_position), "window_position");
	chai->add(chaiscript::fun(&cw::configuration::settings::window_settings::resolution), "resolution");
//	chai->add(chaiscript::fun(&cw::configuration::settings::video_settings::fps), "fps");
	chai->add(chaiscript::fun(&cw::configuration::settings::window_settings::resizable), "resizable");

}

void cw::scripting::interpreter::bind_engine(){
	// constructor
	chai->add(chaiscript::user_type<cw::engine>(), "engine" );
	chai->add(chaiscript::constructor<cw::engine(const cw::configuration::settings&)>(), "engine");

	// methods
	chai->add(chaiscript::fun(&cw::engine::run), "run");

	//members
	chai->add(chaiscript::fun(&cw::engine::core),  "core");
	chai->add(chaiscript::fun(&cw::engine::stage), "stage");

}

void cw::scripting::interpreter::bind_filesystem(){

	// filesystem
	chai->add(chaiscript::fun(&cw::composition::core::filesystem), "filesystem");
	chai->add(chaiscript::fun(&cw::platform::filesystem::add_directory), "add_directory");
	chai->add(chaiscript::fun(&cw::platform::filesystem::get_file_path), "get_file_path");
	chai->add(chaiscript::fun(&cw::platform::filesystem::get_cwd), "get_cwd");
	chai->add(chaiscript::fun(&cw::platform::filesystem::get_folder_content), "get_folder_content");
	chai->add(chaiscript::fun(&cw::platform::filesystem::is_file), "is_file");
	chai->add(chaiscript::fun(&cw::platform::filesystem::is_dir), "is_dir");

}

void cw::scripting::interpreter::bind_input(){

	// input
	chai->add(chaiscript::fun(&cw::composition::core::input), "input");
	chai->add(chaiscript::fun(&cw::platform::input::is_key_down), "is_key_down");
	chai->add(chaiscript::fun(&cw::platform::input::get_mouse_coordinates), "get_mouse_coordinates");

}

void cw::scripting::interpreter::bind_video(){

	// video
	chai->add(chaiscript::fun(&cw::composition::core::video), "video");
	chai->add(chaiscript::fun(&cw::graphical::video::set_window_icon), "set_window_icon");
	chai->add(chaiscript::fun(&cw::graphical::video::load_model), "load_model");
	chai->add(chaiscript::fun(&cw::graphical::video::window), "window");
	chai->add(chaiscript::fun(&cw::graphical::opengl::window::get_size), "get_size");
//	chai->add(chaiscript::fun(&cw::graphical::opengl::window::set_clear_color), "set_clear_color");

}

void cw::scripting::interpreter::bind_sound(){
	
	// sound
//	chai->add(chaiscript::fun(&cw::composition::core::mixer), "mixer");

//	chai->add(chaiscript::fun(&cw::sound::mixer::load_music), "load_music");
//	chai->add(chaiscript::fun(&cw::sound::mixer::play_music), "play_music");
//	chai->add(chaiscript::fun(&cw::sound::mixer::load_effect), "load_effect");
//	chai->add(chaiscript::fun(&cw::sound::mixer::play_effect), "play_effect");

}

void cw::scripting::interpreter::bind_graphical(){

	// model
	chai->add(chaiscript::fun(&cw::graphical::object::model::change_animation), "change_animation");
//	chai->add(chaiscript::fun(&cw::graphical::object::model::set_origin), "set_origin");
//	chai->add(chaiscript::fun(&cw::graphical::object::model::get_origin), "get_origin");
//	chai->add(chaiscript::fun(&cw::graphical::object::model::get_size), "get_size");

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
	chai->add(chaiscript::fun(&cw::composition::group::add_actor), "add_actor");
	chai->add(chaiscript::fun(&cw::composition::group::get_actor), "get_actor");
	chai->add(chaiscript::fun(&cw::composition::group::remove_actor), "remove_actor");

	// actor
	chai->add(chaiscript::fun(&cw::composition::actor::add_text), "add_text");
	chai->add(chaiscript::fun(&cw::composition::actor::remove_text), "remove_text");

	chai->add(chaiscript::fun(&cw::composition::actor::add_model), "add_model");
	chai->add(chaiscript::fun(&cw::composition::actor::get_model), "get_model");

}
