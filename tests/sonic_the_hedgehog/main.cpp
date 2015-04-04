#include <iostream>
#include <memory>

#include <chaiscript/chaiscript.hpp>

#include <crosswind/engine.hpp>

//#include <scenes/title.hpp>
//#include <scenes/green_hill_zone.hpp>


int main(int argc, char **argv) {

    chaiscript::ChaiScript chai;


    chai.add(chaiscript::user_type<cw::interface::settings>(), "settings" );
    chai.add(chaiscript::constructor<cw::interface::settings()>(), "settings");
    chai.add(chaiscript::fun(&cw::interface::settings::video), "video");
    chai.add(chaiscript::fun(&cw::interface::settings::video_settings::window_title), "window_title");

    chai.add(chaiscript::user_type<cw::engine>(), "engine" );
    chai.add(chaiscript::constructor<cw::engine(cw::interface::settings)>(), "engine");
    chai.add(chaiscript::fun(&cw::engine::run), "run");

    try
    {
        chai.eval("auto configuration := settings()");
        chai.eval("configuration.video.window_title = \"Sonic the Hedgehog HD\"");
        chai.eval("auto nucleus := engine(configuration)");
//        chai.eval("v_engine.core.filesystem.add_directory(\"assets\", true)");
        chai.eval("nucleus.run()");
    }
    catch(std::runtime_error& err)
    {
        std::cout << err.what() << std::endl;
    }

   // engine->core->video->set_window_icon(engine->core->filesystem->get_file_path("sonic_icon.png"));

/*    auto title = engine->stage->create_scene<game::scenes::title>();
    auto green_hill_zone = engine->stage->create_scene<game::scenes::green_hill_zone>();
*/
    //engine->stage->add_scene("title", title);
  //  engine->stage->load_scene("title");*/

  //  engine->stage->add_scene("green_hill_zone", green_hill_zone);
   // engine->stage->load_scene("green_hill_zone");

    //engine->stage->swap_scene("current", "green_hill_zone");

/*    engine->run();
*/
    return 0;
}