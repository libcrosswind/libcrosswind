
#include <Crosswind/gui/widgets/window.hpp>
#include <Crosswind/gui/widgets/button.hpp>
#include <Crosswind/gui/widgets/panel.hpp>


#include <Crosswind/util/filesystem.hpp>
#include <string>

int main(int argc, char **argv) {

    cw::filesystem::add_directory("assets", true);

    std::shared_ptr<cw::window> windowA(new cw::window());
    std::shared_ptr<cw::window> windowB(new cw::window());

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
    windowA->init();

    windowB->set_text("B window");
    windowB->set_width(640);
    windowB->set_height(480);
    windowB->set_depth(1);
    windowB->init(FlagSet<cw::widget::InitFlags>(cw::widget::InitFlags::IN_NEW_THREAD));

    windowA->attach(button);
    windowB->attach(button);

    windowB->show();
    windowA->show();

    return 0;

}