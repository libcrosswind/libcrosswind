#include <iostream>
#include <memory>

/*
#include <crosswind/engine.hpp>

#include <scenes/title.hpp>
#include <scenes/green_hill_zone.hpp>
*/

#include <chaiscript/chaiscript.hpp>

class object{

public:
    object(){

    }

    void print(){
        std::cout << "Hello world" << std::endl;
    }
};

double function(int i, double j)
{
    return i * j;
}

std::shared_ptr<object> get_object(){
    return std::make_shared<object>();
}

int main(int argc, char **argv) {

    chaiscript::ChaiScript chai;
    chai.add(chaiscript::fun(&function), "function");

    chai.add(chaiscript::fun(&get_object), "get_object");


    std::cout <<  chai.eval<double>("function(3, 4.75);") << std::endl;

    chai.eval("get_object().print();");

    auto ptr = chai.eval<std::shared_ptr<object> > ("get_object();");
    ptr->print();

/*    auto settings = cw::interface::settings();
    settings.video.window_title = "Sonic the Hedgehog HD";

    auto engine = std::make_shared<cw::engine>(settings);
    engine->core->filesystem->add_directory("assets", true);
   // engine->core->video->set_window_icon(engine->core->filesystem->get_file_path("sonic_icon.png"));

    auto title = engine->stage->create_scene<game::scenes::title>();
    auto green_hill_zone = engine->stage->create_scene<game::scenes::green_hill_zone>();

    engine->stage->add_scene("title", title);
    engine->stage->load_scene("title");

  //  engine->stage->add_scene("green_hill_zone", green_hill_zone);
   // engine->stage->load_scene("green_hill_zone");

    //engine->stage->swap_scene("current", "green_hill_zone");

    engine->run();
*/
    return 0;
}