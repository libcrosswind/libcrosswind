#pragma once 
#include "server_ws.hpp"
#include <asio/ssl.hpp>

namespace cw {
    namespace network{
        namespace websockets {

            typedef asio::ssl::stream<asio::ip::tcp::socket> WSS;

            template<>
            class SocketServer<WSS> : public SocketServerBase<WSS> {

            public:
                SocketServer(unsigned short port, size_t num_threads, const std::string& cert_file, const std::string& private_key_file,
                        size_t timeout_request=5, size_t timeout_idle=0,
                        const std::string& verify_file=std::string()) :
                        SocketServerBase<WSS>::SocketServerBase(port, num_threads, timeout_request, timeout_idle),
                        asio_context(asio::ssl::context::sslv23) {
                    asio_context.use_certificate_chain_file(cert_file);
                    asio_context.use_private_key_file(private_key_file, asio::ssl::context::pem);

                    if(verify_file.size()>0)
                        asio_context.load_verify_file(verify_file);
                }

            private:
                asio::ssl::context asio_context;

                void accept() {
                    //Create new socket for this connection (stored in Connection::socket)
                    //Shared_ptr is used to pass temporary objects to the asynchronous functions
                    std::shared_ptr<Connection> connection(new Connection(new WSS(asio_io_service, asio_context)));

                    asio_acceptor.async_accept(connection->socket->lowest_layer(), [this, connection](const asio::error_code& ec) {
                        //Immediately start accepting a new connection
                        accept();

                        if(!ec) {
                            //Set timeout on the following asio::ssl::stream::async_handshake
                            std::shared_ptr<asio::deadline_timer> timer;
                            if(timeout_request>0)
                                timer=set_timeout_on_connection(connection, timeout_request);
                            connection->socket->async_handshake(asio::ssl::stream_base::server,
                                    [this, connection, timer](const asio::error_code& ec) {
                                if(timeout_request>0)
                                    timer->cancel();
                                if(!ec) {
                                    read_handshake(connection);
                                }
                            });
                        }
                    });
                }
            };
        }
    }
}

