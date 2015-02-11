

#include <Crosswind/util/filesystem.hpp>
//#include <Crosswind/datatypes/msgpack.hpp>

#include <iostream>
//#include <Crosswind/pools/widget_pool.hpp>
//#include <Crosswind/network/ws/ws_client.hpp>

#include <memory>
#include <string>

#include <msgpack.hpp>




int main(int argc, char **argv) {

  /*  cw::filesystem::add_directory("assets", true);
    cw::filesystem::add_directory("tests/gui", true);

    std::cout << cw::datatypes::messagepack::encode("Hello world") << std::endl;


    auto window      = cw::widget_pool::create<cw::window> (0.0, 0.0, 640, 480, "blue");
    auto panel       = cw::widget_pool::create<cw::panel>  (0.3, 0.2, 0.3, 0.3, "blue");
    auto button      = cw::widget_pool::create<cw::button> (0.1, 0.2, 0.4, 0.3, "blue");
    auto info_label  = cw::widget_pool::create<cw::label>  (0.0, 0.0, 0.05, 0.025, "blue");
    auto textbox     = cw::widget_pool::create<cw::textbox>(0.0, 0.0, 0.05, 0.025, "blue");
    std::shared_ptr<cw::network::ws::ws_client> ws_client(new cw::network::ws::ws_client("192.168.1.67:8000/echo"));

    window->set_text("Main window");
    button->set_theme("green");
    button->set_text("Send Message");
    info_label->set_text("Text to send");
    textbox->set_text("Text");

    button->on_clicked += [ws_client, textbox](){

        std::stringstream data_ss;
        data_ss << textbox->get_text();
        ws_client->send(data_ss);

    };

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

    panel->attach(info_label);
    panel->attach(textbox);
    panel->attach(button);
    window->attach(panel);

    window->on_hide += [ws_client](){
        ws_client->stop();
    };

    window->show();
*/
    return 0;

}