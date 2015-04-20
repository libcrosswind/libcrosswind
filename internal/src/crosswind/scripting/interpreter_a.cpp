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

	bind_datatypes();
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


void cw::scripting::interpreter::bind_datatypes(){

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

	chai->add(chaiscript::bootstrap::standard_library::vector_type<std::vector<std::string> >("StringVector"));

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
