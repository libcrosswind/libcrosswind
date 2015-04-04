#include <iostream>

#include <chaiscript/chaiscript.hpp>

#include <crosswind/engine.hpp>

int main(int argc, char **argv) {

    chaiscript::ChaiScript chai;

    // data types

    // vec2
    chai.add(chaiscript::user_type<glm::vec2>(), "vec2" );
    chai.add(chaiscript::constructor<glm::vec2()>(), "vec2");
    chai.add(chaiscript::constructor<glm::vec2(float, float)>(), "vec2");
    chai.add(chaiscript::fun(&glm::vec2::x), "x");
    chai.add(chaiscript::fun(&glm::vec2::y), "y");

    // vec3
    chai.add(chaiscript::user_type<glm::vec3>(), "vec3" );
    chai.add(chaiscript::constructor<glm::vec3()>(), "vec3");
    chai.add(chaiscript::constructor<glm::vec3(float, float, float)>(), "vec3");
    chai.add(chaiscript::fun(&glm::vec3::x), "x");
    chai.add(chaiscript::fun(&glm::vec3::y), "y");
    chai.add(chaiscript::fun(&glm::vec3::z), "z");

    // vec4
    chai.add(chaiscript::user_type<glm::vec4>(), "vec4" );
    chai.add(chaiscript::constructor<glm::vec4()>(), "vec4");
    chai.add(chaiscript::constructor<glm::vec4(float, float, float, float)>(), "vec4");
    chai.add(chaiscript::fun(&glm::vec4::x), "x");
    chai.add(chaiscript::fun(&glm::vec4::y), "y");
    chai.add(chaiscript::fun(&glm::vec4::z), "z");
    chai.add(chaiscript::fun(&glm::vec4::w), "w");

    // constructor
    chai.add(chaiscript::user_type<cw::interface::settings>(), "settings" );
    chai.add(chaiscript::constructor<cw::interface::settings()>(), "settings");

    // members
    chai.add(chaiscript::fun(&cw::interface::settings::video), "video");
    chai.add(chaiscript::fun(&cw::interface::settings::video_settings::window_title), "window_title");

    // constructor
    chai.add(chaiscript::user_type<cw::engine>(), "engine" );
    chai.add(chaiscript::constructor<cw::engine(cw::interface::settings)>(), "engine");

    // methods
    chai.add(chaiscript::fun(&cw::engine::run), "run");

    //members
    chai.add(chaiscript::fun(&cw::engine::core),  "core");
    chai.add(chaiscript::fun(&cw::engine::stage), "stage");

    //member functions

    // core
    chai.add(chaiscript::fun(&cw::interface::composition::core::filesystem), "filesystem");
    chai.add(chaiscript::fun(&cw::interface::composition::core::video), "video");

    chai.add(chaiscript::fun(&cw::interface::graphical::video::window), "window");
    chai.add(chaiscript::fun(&cw::interface::graphical::detail::window::get_size), "get_size");
    chai.add(chaiscript::fun(&cw::interface::graphical::detail::window::set_clear_color), "set_clear_color");


    chai.add(chaiscript::fun(&cw::interface::graphical::video::set_window_icon), "set_window_icon");
    chai.add(chaiscript::fun(&cw::interface::graphical::video::load_model), "load_model");

    chai.add(chaiscript::fun(&cw::interface::platform::filesystem::add_directory), "add_directory");
    chai.add(chaiscript::fun(&cw::interface::platform::filesystem::get_file_path), "get_file_path");

    // stage
    chai.add(chaiscript::fun(&cw::interface::composition::stage::create_scene), "create_scene");
    chai.add(chaiscript::fun(&cw::interface::composition::stage::add_scene), "add_scene");
    chai.add(chaiscript::fun(&cw::interface::composition::stage::remove_scene), "remove_scene");
    chai.add(chaiscript::fun(&cw::interface::composition::stage::swap_scene), "swap_scene");
    chai.add(chaiscript::fun(&cw::interface::composition::stage::load_scene), "load_scene");
    chai.add(chaiscript::fun(&cw::interface::composition::stage::unload_scene), "unload_scene");

    // scene
    chai.add(chaiscript::fun(&cw::interface::composition::scene::construct), "construct");

    chai.add(chaiscript::fun(&cw::interface::composition::scene::create_actor), "create_actor");
    chai.add(chaiscript::fun(&cw::interface::composition::scene::add_actor), "add_actor");
    chai.add(chaiscript::fun(&cw::interface::composition::scene::get_actor), "get_actor");
    chai.add(chaiscript::fun(&cw::interface::composition::scene::remove_actor), "remove_actor");

    chai.add(chaiscript::fun(&cw::interface::composition::scene::create_camera), "create_camera");
    chai.add(chaiscript::fun(&cw::interface::composition::scene::set_camera), "set_camera");
    chai.add(chaiscript::fun(&cw::interface::composition::scene::get_camera), "get_camera");

    // actor
    chai.add(chaiscript::fun(&cw::interface::composition::actor::construct), "construct");

    chai.add(chaiscript::fun(&cw::interface::composition::actor::init), "init");
    chai.add(chaiscript::fun(&cw::interface::composition::actor::deinit), "deinit");

    chai.add(chaiscript::fun(&cw::interface::composition::actor::add_model), "add_model");

    chai.add(chaiscript::fun(&cw::interface::composition::actor::set_name), "set_name");
    chai.add(chaiscript::fun(&cw::interface::composition::actor::get_name), "get_name");
    chai.add(chaiscript::fun(&cw::interface::composition::actor::set_alpha), "set_alpha");
    chai.add(chaiscript::fun(&cw::interface::composition::actor::get_alpha), "get_alpha");

    try
    {
      chai.eval_file("scripts/main.chai");
    }
    catch(std::runtime_error& err)
    {
        std::cout << err.what() << std::endl;
    }

    return 0;
}