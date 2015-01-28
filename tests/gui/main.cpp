
#include <Crosswind/gui/widgets/window.hpp>
#include <Crosswind/gui/widgets/button.hpp>
#include <Crosswind/gui/widgets/panel.hpp>
#include <Crosswind/util/var.hpp>

#include <Crosswind/util/filesystem.hpp>
#include <string>

#include <memory>

int main(int argc, char **argv) {

    cw::filesystem::add_directory("assets", true);

    std::shared_ptr<cw::window> window(new cw::window());
    std::shared_ptr<cw::vertical_group> vertical_group(new cw::vertical_group());
    std::shared_ptr<cw::horizontal_group> horizontal_group(new cw::horizontal_group());
    std::shared_ptr<cw::button> button(new cw::button());
    std::shared_ptr<cw::panel> panel(new cw::panel());

    window->set_text("A window");
    window->set_width(640);
    window->set_height(480);
    window->set_depth(1);
    window->init([](){
        std::shared_ptr<cw::widget::init_flags> flags(new cw::widget::init_flags());
        //  flags->set<cw::window::window_flags>(cw::window::window_flags::MULTITHREADED);
        return flags;
    }());

    vertical_group->set_grid_offset(30);
    vertical_group->set_x(120);
    vertical_group->set_y(120);

    button->set_theme("green");
    button->set_width(120);
    button->set_height(30);
    button->set_depth(1);
    button->set_text("Hello world");
    button->show();

    panel->set_theme("blue");
    panel->set_x(120);
    panel->set_y(120);
    panel->set_width(240);
    panel->set_height(160);
    panel->set_depth(1);
    panel->show();



    vertical_group->attach(button);


    panel->attach(vertical_group);
    window->attach(panel);

    window->show();

    return 0;

}