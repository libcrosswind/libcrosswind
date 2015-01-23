
#include <Crosswind/gui/window.h>
#include <Crosswind/gui/widgets/button.h>
#include <Crosswind/logic/movementLogicModule.h>
#include <Crosswind/system/settings.h>


std::string cw::settings::path::ui = std::string("assets/ui/blue/");

int main(int argc, char **argv) {


    std::shared_ptr<cw::window> window(new cw::window(640, 480, "Game_test"));
    std::shared_ptr<cw::button> button(new cw::button());

    button->on_mouse_down += [](int button){
        std::cout<<button<<std::endl;
    };

    window->attach(button);

    window->on_closed += [&](){
        std::cout<<"Nice"<<std::endl;
    };

    window->on_closed += [&](){
        std::cout<<"Uber nice"<<std::endl;
    };

    window->show();

    return 0;

}