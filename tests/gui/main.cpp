
#include <Crosswind/gui/widgets/window.hpp>
#include <Crosswind/gui/widgets/button.hpp>
#include <Crosswind/gui/widgets/textbox.hpp>

#include <Crosswind/gui/widgets/panel.hpp>
#include <Crosswind/util/var.hpp>
#include <Crosswind/network/ws/ws_client.hpp>
#include <Crosswind/util/filesystem.hpp>
#include <string>

#include <asio/impl/src.hpp> //TODO move this to common network header.

#include <memory>

int main(int argc, char **argv) {

    cw::filesystem::add_directory("assets", true);

    std::shared_ptr<cw::window> window(new cw::window());
    std::shared_ptr<cw::vertical_group> vertical_group(new cw::vertical_group());
    std::shared_ptr<cw::horizontal_group> horizontal_group(new cw::horizontal_group());
    std::shared_ptr<cw::button> button(new cw::button());
    std::shared_ptr<cw::textbox> textbox(new cw::textbox());
    std::shared_ptr<cw::panel> panel(new cw::panel());

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
    button->set_text("Send Message");
    button->on_clicked += [ws_client, textbox](){

        std::stringstream data_ss;
        data_ss << textbox->get_text();
        //
        ws_client->send(data_ss);

    };
    textbox->set_width(90);
    textbox->set_height(40);
    textbox->set_text("Hello World");

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


    window->on_close += [ws_client](){
        ws_client->stop();
    };

    window->show();

    return 0;

}