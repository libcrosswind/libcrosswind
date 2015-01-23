#include <iostream>
#include <sstream>

#include <Crosswind/network/websockets/client_ws.hpp>

#include <asio/impl/src.hpp>

#include <thread>


class Application{
public:
    Application(): ws_client("192.168.1.65:8000/echo"),  running(true){
        ws_thread = std::thread(std::bind(&Application::ws, this));
    }

    ~Application(){
        ws_thread.join();
    }

    void run(){
        while(running.load());

    }

private:

    void ws(){

        ws_client.onmessage=[&](auto message) {
            std::stringstream data_ss;
            data_ss << message->data.rdbuf();
            std::cout << "Client: Message received: \"" << data_ss.str() << "\"" << std::endl;
        };

        ws_client.onopen=[&]() {
     
        };

        ws_client.onclose=[](int status, const std::string& reason) {
            std::cout << "Client: Closed connection with status code " << status << std::endl;

        };

        //See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
        ws_client.onerror=[](const asio::error_code& ec) {
            std::cout << "Client: Error: " << ec << ", error message: " << ec.message() << std::endl;
        };

        ws_client.start();
    }

  

    void exit(){
        this->running.store(false);
    }

private:
    std::thread ws_thread;
    std::mutex ws_mutex;

    cw::network::websockets::SocketClient<cw::network::websockets::WS> ws_client;
    std::atomic<bool> running;


};

#if defined(WIN32)
int main(int argc, char* argv[])
#elif defined(__ANDROID__)
//void android_main(struct android_app* state)
#endif
{


//    struct engine engine;
Application app;
app.run();


}
