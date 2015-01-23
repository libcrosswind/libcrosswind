#pragma once 

#include "client_ws.hpp"
#include <asio/ssl.hpp>

namespace cw {
   namespace network{
        namespace websockets {

            typedef asio::ssl::stream<asio::ip::tcp::socket> WSS;

            template<>
            class SocketClient<WSS> : public SocketClientBase<WSS> {
            public:
                SocketClient(const std::string& server_port_path, bool verify_certificate=true,
                        const std::string& cert_file=std::string(), const std::string& private_key_file=std::string(),
                        const std::string& verify_file=std::string()) :
                        SocketClientBase<WSS>::SocketClientBase(server_port_path, 443),
                        asio_context(asio::ssl::context::sslv23) {
                    if(verify_certificate)
                        asio_context.set_verify_mode(asio::ssl::verify_peer);
                    else
                        asio_context.set_verify_mode(asio::ssl::verify_none);

                    if(cert_file.size()>0 && private_key_file.size()>0) {
                        asio_context.use_certificate_chain_file(cert_file);
                        asio_context.use_private_key_file(private_key_file, asio::ssl::context::pem);
                    }

                    if(verify_file.size()>0)
                        asio_context.load_verify_file(verify_file);

                };

            private:
                asio::ssl::context asio_context;

                void connect() {
                    asio::ip::tcp::resolver::query query(host, std::to_string(port));

                    asio_resolver.async_resolve(query, [this]
                            (const asio::error_code &ec, asio::ip::tcp::resolver::iterator it){
                        if(!ec) {
                            connection=std::unique_ptr<Connection>(new Connection(new WSS(asio_io_service, asio_context)));

                            asio::async_connect(connection->socket->lowest_layer(), it, [this]
                                    (const asio::error_code &ec, asio::ip::tcp::resolver::iterator it){
                                if(!ec) {
                                    connection->socket->async_handshake(asio::ssl::stream_base::client,
                                            [this](const asio::error_code& ec) {
                                        if(!ec)
                                            handshake();
                                        else
                                            throw std::invalid_argument(ec.message());
                                    });
                                }
                                else
                                    throw std::invalid_argument(ec.message());
                            });
                        }
                        else
                            throw std::invalid_argument(ec.message());
                    });
                }
            };
        } //namespace websockets
   } //namespace network
} //namespace nana
 