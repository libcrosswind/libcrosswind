
#include <Crosswind/gui/widgets/window.hpp>
#include <Crosswind/gui/widgets/button.hpp>
#include <Crosswind/gui/widgets/panel.hpp>


#include <Crosswind/util/filesystem.hpp>
#include <string>

int main(int argc, char **argv) {

    cw::filesystem::add_directory("assets", true);

    std::shared_ptr<cw::window> windowA(new cw::window());
    std::shared_ptr<cw::panel> panel(new cw::panel());

    std::shared_ptr<cw::button> button(new cw::button());

    button->set_theme("green");
    button->set_width(120);
    button->set_height(30);
    button->set_depth(1);
    button->init();
    button->show();

    windowA->set_text("A window");
    windowA->set_width(640);
    windowA->set_height(480);
    windowA->set_depth(1);
    windowA->init([](){
        std::shared_ptr<cw::widget::init_flags> flags(new cw::widget::init_flags());
      //  flags->set<cw::window::window_flags>(cw::window::window_flags::MULTITHREADED);
        return flags;
    }());

    panel->set_theme("blue");
    panel->set_text("Left Panel");
    panel->set_width(240);
    panel->set_height(160);
    panel->set_depth(1);
    panel->init();
    panel->show();

    panel->attach(button);
    windowA->attach(panel);

    windowA->show();

    return 0;

}