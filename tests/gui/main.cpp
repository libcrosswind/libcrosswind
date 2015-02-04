
#include <Crosswind/gui/widgets/window.hpp>
#include <Crosswind/gui/widgets/button.hpp>
#include <Crosswind/gui/widgets/textbox.hpp>
#include <Crosswind/gui/widgets/label.hpp>

#include <Crosswind/gui/widgets/panel.hpp>
#include <Crosswind/util/var.hpp>
#include <Crosswind/network/ws/ws_client.hpp>
#include <Crosswind/util/filesystem.hpp>
#include <string>

#include <asio/impl/src.hpp> //TODO move this to common network header.

#include <memory>

int main(int argc, char **argv) {

    cw::filesystem::add_directory("assets", true);

    std::shared_ptr<cw::widget> window(new cw::window([](){
        std::shared_ptr<cw::util::flag_container> flags(new cw::util::flag_container());
        //  flags->set<cw::window::window_flags>(cw::window::window_flags::MULTITHREADED);
        return flags;
    }()));


    std::shared_ptr<cw::vertical_group> vertical_group(new cw::vertical_group());
    std::shared_ptr<cw::horizontal_group> horizontal_group(new cw::horizontal_group());
    std::shared_ptr<cw::widget> panel(new cw::panel());
    std::shared_ptr<cw::widget> button(new cw::button());
    std::shared_ptr<cw::widget> info_label(new cw::label());
    std::shared_ptr<cw::widget> textbox(new cw::textbox());

    std::shared_ptr<cw::network::ws::ws_client> ws_client(new cw::network::ws::ws_client("192.168.1.67:8000/echo"));

    ws_client->on_message += [](auto message) {
        std::stringstream data_ss;
        data_ss << message->data.rdbuf();
        std::cout << "Client: Message received: \"" << data_ss.str() << "\"" << std::endl;
    };

    ws_client->on_open += []() {

    };

    ws_client->on_close +=[](int status, const std::string& reason) {
        std::cout << "Client: Closed connection with status code " << status << std::endl;
    };

    ws_client->on_error +=[](const asio::error_code& ec) {
        std::cout << "Client: Error: " << ec << ", error message: " << ec.message() << std::endl;
    };

    ws_client->start();


    window->set_text("Main window");
    window->set_absolute_width(640.0);
    window->set_absolute_height(480.0);


    panel->set_theme("blue");
    panel->set_x(0.3);
    panel->set_y(0.2);
    panel->set_width(0.3);
    panel->set_height(0.3);

    vertical_group->set_grid_offset(0.2);
    horizontal_group->set_grid_offset(0.05);

    info_label->set_width(0.05);
    info_label->set_height(0.025);
    info_label->set_text("Text to send");

    textbox->set_width(0.05);
    textbox->set_height(0.025);
    textbox->set_text("Text");

    button->set_theme("green");
    button->set_x(0.1);
    button->set_y(0.2);
    button->set_width(0.4);
    button->set_height(0.3);
    button->set_text("Send Message");
    button->on_clicked += [ws_client, textbox](){

        std::stringstream data_ss;
        data_ss << textbox->get_text();

        ws_client->send(data_ss);

    };



    //horizontal_group->attach(info_label); //Pending until we can draw as alpha masked.
    //horizontal_group->attach(textbox);
  //  horizontal_group->attach(button);

    vertical_group->attach(button);

    panel->attach(vertical_group);
    window->attach(panel);


    window->on_hide += [ws_client](){
        ws_client->stop();
    };

    window->show();

    return 0;

}