
#include <Crosswind/gui/widgets/window.hpp>
#include <Crosswind/gui/widgets/button.hpp>
#include <Crosswind/gui/widgets/textbox.hpp>

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
    std::shared_ptr<cw::textbox> textbox(new cw::textbox());

    std::shared_ptr<cw::panel> panel(new cw::panel());

    window->set_text("A window");
    window->set_width(640);
    window->set_height(480);
    window->init([](){
        std::shared_ptr<cw::widget::init_flags> flags(new cw::widget::init_flags());
        //  flags->set<cw::window::window_flags>(cw::window::window_flags::MULTITHREADED);
        return flags;
    }());

    vertical_group->set_grid_offset(0.2);
    horizontal_group->set_grid_offset(0.05);

    button->set_theme("green");
    button->set_width(90);
    button->set_height(40);
    button->set_text("Hello world");

    textbox->set_width(90);
    textbox->set_height(40);
    textbox->set_text("This textbox");

    panel->set_theme("blue");
    panel->set_x(0.2);
    panel->set_y(0.2);

    panel->set_width(400);
    panel->set_height(200);

    vertical_group->set_width(panel->get_width());
    vertical_group->set_height(panel->get_height());

    horizontal_group->set_width(panel->get_width());
    horizontal_group->set_height(panel->get_height());

    horizontal_group->attach(button);
    horizontal_group->attach(textbox);

    vertical_group->attach(horizontal_group);
    panel->attach(vertical_group);
    window->attach(panel);

    window->show();

    return 0;

}