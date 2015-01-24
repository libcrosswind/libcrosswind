
#include <Crosswind/gui/window.h>
#include <Crosswind/gui/widgets/button.h>
#include <Crosswind/logic/movementLogicModule.h>
#include <Crosswind/system/settings.h>

/*#include <Crosswind/textures/Texture.hpp>
#include <Crosswind/textures/TextureManager.hpp>*/
#include <Crosswind/util/filesystem.hpp>

#include <iostream>

int main(int argc, char **argv) {

    cw::filesystem::addDirectory("assets", true);
    if(cw::filesystem::exists("click1.ogg")){std::cout<<"Exists"<<std::endl;};
    if(!cw::filesystem::exists("shouldNot")){std::cout<<"Does not"<<std::endl;}

    std::cout<<cw::filesystem::get_file_path("click2.ogg")<<std::endl;
    std::shared_ptr<cw::window> window(new cw::window(640, 480, "GUI test"));

    std::shared_ptr<cw::button> button(new cw::button(true));
    //button->draggable() = true;
    std::shared_ptr<cw::widget> button_replica1 = button->replicate<cw::button>();
    std::shared_ptr<cw::widget> button_replica2 = button_replica1->replicate<cw::button>();

    button->on_mouse_down += [](int button){
      std::cout<<button<<std::endl;
    };

    window->attach(button);
    window->attach(button_replica1);
    window->attach(button_replica2);
    window->on_closed += [&](){
      std::cout<<"Nice"<<std::endl;
    };

    window->on_closed += [&](){
      std::cout<<"Uber nice"<<std::endl;
    };

    window->show();

    return 0;

}