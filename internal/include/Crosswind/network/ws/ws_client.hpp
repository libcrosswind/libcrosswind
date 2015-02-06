#pragma once 

#include <Crosswind/crypto/base64.hpp>
#include <Crosswind/crypto/sha1.hpp>

#include <asio.hpp>

#include <unordered_map>
#include <iostream>
#include <regex>
#include <random>
#include <atomic>
#include <string>

namespace cw {
   namespace network{
   		namespace ws {

	    	class ws_message {

	        public:
                ws_message(): data(&data_buffer) {}

                std::istream data;
	            size_t length;
	            unsigned char fin_rsv_opcode;
	            asio::streambuf data_buffer;
	        };


   			class ws_client_base{


		    protected:
		        class ws_connection {
	 
			        public:
			            std::unordered_map<std::string, std::string> header;
			            asio::ip::address remote_endpoint_address;
			            unsigned short remote_endpoint_port;

			            ws_connection(asio::ip::tcp::socket* socket): socket(socket), closed(false) {}

			            void read_remote_endpoint_data() {
			                try {
			                    remote_endpoint_address=socket->lowest_layer().remote_endpoint().address();
			                    remote_endpoint_port=socket->lowest_layer().remote_endpoint().port();
			                }
			                catch(const std::exception& e) {
			                    std::cerr << e.what() << std::endl;
			                }
			            }

                    std::unique_ptr<asio::ip::tcp::socket> socket;
                    std::atomic<bool> closed;

		        };
            std::thread th_run;

			public:
				void start() {

                    th_run = std::thread([this](){
                        connect();

                        asio_io_service.run();
                    });
		        }

		        void stop() {
		            asio_io_service.stop();

                    th_run.join();
		        }

		        void send(std::iostream& stream, const std::function<void(const asio::error_code&)>& callback=nullptr,
		                unsigned char fin_rsv_opcode=129) {
		            //Create mask
		            std::vector<unsigned char> mask;
		            mask.resize(4);
		            std::uniform_int_distribution<unsigned char> dist;
		            std::random_device rd;
		            for(int c=0;c<4;c++) {
		                mask[c]=dist(rd);
		            }

		            std::shared_ptr<asio::streambuf> write_buffer(new asio::streambuf);
		            std::ostream response(write_buffer.get());

		            stream.seekp(0, std::ios::end);
		            size_t length=stream.tellp();
		            stream.seekp(0, std::ios::beg);

		            response.put(fin_rsv_opcode);
		            //masked (first length byte>=128)
		            if(length>=126) {
		                int num_bytes;
		                if(length>0xffff) {
		                    num_bytes=8;
		                    response.put(127+128);
		                }
		                else {
		                    num_bytes=2;
		                    response.put(126+128);
		                }

		                for(int c=num_bytes-1;c>=0;c--) {
		                    response.put((length>>(8*c))%256);
		                }
		            }
		            else
		                response.put(length+128);

		            for(int c=0;c<4;c++) {
		                response.put(mask[c]);
		            }

		            for(size_t c=0;c<length;c++) {
		                response.put(stream.get()^mask[c%4]);
		            }

		            //Need to copy the callback-function in case its destroyed
		            asio::async_write(*connection->socket, *write_buffer,
		                    [this, write_buffer, callback](const asio::error_code& ec, size_t bytes_transferred) {
		                if(callback) {
		                    callback(ec);
		                }
		            });
		        }

		        void send_close(int status, const std::string& reason="") {
		            //Send close only once (in case close is initiated by client)
		            if(connection->closed.load()) {
		                return;
		            }
		            connection->closed.store(true);

		            std::stringstream response;

		            response.put(status>>8);
		            response.put(status%256);

		            response << reason;

		            //fin_rsv_opcode=136: message close
		            send(response, [](const asio::error_code& ec){}, 136);
		        }

		    protected: 

		    	void handshake() {

		            connection->read_remote_endpoint_data();

		            std::shared_ptr<asio::streambuf> write_buffer(new asio::streambuf);

		            std::ostream request(write_buffer.get());

		            request << "GET " << path << " HTTP/1.1" << "\r\n";
		            request << "Host: " << host << "\r\n";
		            request << "Upgrade: websocket\r\n";
		            request << "Connection: Upgrade\r\n";

		            //Make random 16-byte nonce
		            std::string nonce;
		            nonce.resize(16);
		            std::uniform_int_distribution<unsigned char> dist;
		            std::random_device rd;
		            for(int c=0;c<16;c++)
		                nonce[c]=dist(rd);

		            std::string nonce_base64=crypto::base64::encode(nonce);
		            request << "Sec-WebSocket-Key: " << nonce_base64 << "\r\n";
		            request << "Sec-WebSocket-Version: 13\r\n";
		            request << "\r\n";

		            //test this to base64::decode(Sec-WebSocket-Accept)
 
		            std::shared_ptr<std::string> accept_sha1(new std::string(crypto::sha1::compress(nonce_base64+ws_magic_string)));

		            asio::async_write(*connection->socket, *write_buffer,
		                    [this, write_buffer, accept_sha1]
		                    (const asio::error_code& ec, size_t bytes_transferred) {
		                if(!ec) {
		                    std::shared_ptr<ws_message> message(new ws_message());

		                    asio::async_read_until(*connection->socket, message->data_buffer, "\r\n\r\n",
		                            [this, message, accept_sha1]
		                            (const asio::error_code& ec, size_t bytes_transferred) {
		                        if(!ec) {
		                            parse_handshake(message->data);
		                            if(crypto::base64::decode(connection->header["Sec-WebSocket-Accept"])==*accept_sha1) {
                                        on_open();
		                                read_message(message);
		                            }
		                            else
		                                throw std::invalid_argument("WebSocket handshake failed");
		                        }
		                    });
		                }
		                else
		                    throw std::invalid_argument("Failed sending handshake");
		            });
		        }

		        void parse_handshake(std::istream& stream) const {
		            std::smatch sm;

		            //Not parsing the first line
		            std::string line;
		            getline(stream, line);
		            line.pop_back();

		            bool matched;
		            std::regex e("^([^:]*): ?(.*)$");
		            //Parse the rest of the header
		            do {
		                getline(stream, line);
		                line.pop_back();
		                matched=std::regex_match(line, sm, e);
		                if(matched) {
		                    connection->header[sm[1]]=sm[2];
		                }

		            } while(matched==true);
		        }

		        void read_message(std::shared_ptr<ws_message> message) {
		            asio::async_read(*connection->socket, message->data_buffer, asio::transfer_exactly(2),
		                    [this, message](const asio::error_code& ec, size_t bytes_transferred) {
		                if(!ec) {
		                    std::vector<unsigned char> first_bytes;
		                    first_bytes.resize(2);
		                    message->data.read((char*)&first_bytes[0], 2);

		                    message->fin_rsv_opcode=first_bytes[0];

		                    //Close connection if masked message from server (protocol error)
		                    if(first_bytes[1]>=128) {
		                        const std::string reason="message from server masked";
		                        send_close(1002, reason);
                                on_close(1002, reason);
		                        return;
		                    }

		                    size_t length=(first_bytes[1]&127);

		                    if(length==126) {
		                        //2 next bytes is the size of content
		                        asio::async_read(*connection->socket, message->data_buffer, asio::transfer_exactly(2),
		                                [this, message]
		                                (const asio::error_code& ec, size_t bytes_transferred) {
		                            if(!ec) {
		                                std::vector<unsigned char> length_bytes;
		                                length_bytes.resize(2);
		                                message->data.read((char*)&length_bytes[0], 2);

		                                size_t length=0;
		                                int num_bytes=2;
		                                for(int c=0;c<num_bytes;c++)
		                                    length+=length_bytes[c]<<(8*(num_bytes-1-c));

		                                message->length=length;
		                                read_message_content(message);
		                            }
		                            else {
                                        on_error(ec);
		                            }
		                        });
		                    }
		                    else if(length==127) {
		                        //8 next bytes is the size of content
		                        asio::async_read(*connection->socket, message->data_buffer, asio::transfer_exactly(8),
		                                [this, message]
		                                (const asio::error_code& ec, size_t bytes_transferred) {
		                            if(!ec) {
		                                std::vector<unsigned char> length_bytes;
		                                length_bytes.resize(8);
		                                message->data.read((char*)&length_bytes[0], 8);

		                                size_t length=0;
		                                int num_bytes=8;
		                                for(int c=0;c<num_bytes;c++)
		                                    length+=length_bytes[c]<<(8*(num_bytes-1-c));

		                                message->length=length;
		                                read_message_content(message);
		                            }
		                            else {

                                        on_error(ec);
		                            }
		                        });
		                    }
		                    else {
		                        message->length=length;
		                        read_message_content(message);
		                    }
		                }
		                else {
                           on_error(ec);
		                }
		            });
		        }

		        void read_message_content(std::shared_ptr<ws_message> message) {
		            asio::async_read(*connection->socket, message->data_buffer, asio::transfer_exactly(message->length),
		                    [this, message]
		                    (const asio::error_code& ec, size_t bytes_transferred) {
		                if(!ec) {
		                    //If connection close
		                    if((message->fin_rsv_opcode&0x0f)==8) {
		                        int status=0;
		                        if(message->length>=2) {
		                            unsigned char byte1=message->data.get();
		                            unsigned char byte2=message->data.get();
		                            status=(byte1<<8)+byte2;
		                        }

		                        std::stringstream reason_ss;
		                        reason_ss << message->data.rdbuf();
		                        std::string reason=reason_ss.str();

		                        send_close(status, reason);
                                on_close(status, reason);
		                        return;
		                    }
		                    //If ping
		                    else if((message->fin_rsv_opcode&0x0f)==9) {
		                        //send pong
		                        std::stringstream empty_ss;
		                        send(empty_ss, nullptr, message->fin_rsv_opcode+1);
		                    }
		                    else {
                                on_message(message);
		                    }

		                    //Next message
		                    std::shared_ptr<ws_message> next_message(new ws_message());
		                    read_message(next_message);
		                }
		                else {
                            on_error(ec);
		                }
		            });
		        }

		    protected:
				ws_client_base(std::string host_port_path, unsigned short default_port = 80): asio_resolver(asio_io_service) {
                    const std::string pattern("^(ws)://([^:/]+):?([0-9]*)(.*)$");

					std::smatch sm;

					if(std::regex_match(host_port_path, sm, e)) {
						host=sm[1];
						path=sm[3];
						port=default_port;
					if(sm[2]!="")
						port=(unsigned short)std::stoul(sm[2]);
						asio_endpoint=asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port);
					}
					else {
						throw std::invalid_argument("Error parsing host_port_path");
					}
				}

				virtual void connect() = 0;

			public: 
		        delegate<void> on_open;
                delegate<void, std::shared_ptr<ws_message> > on_message;
		        delegate<void, const asio::error_code&> on_error;
		        delegate<void, int, const std::string&> on_close;
		  
		    protected:
		        const std::string ws_magic_string="258EAFA5-E914-47DA-95CA-C5AB0DC85B11";

		        asio::io_service asio_io_service;
		        asio::ip::tcp::endpoint asio_endpoint;
		        asio::ip::tcp::resolver asio_resolver;

		        std::string host;
		        unsigned short port;
		        std::string path; 

		        std::unique_ptr<ws_connection> connection;
   			};


			class ws_client: public ws_client_base{
				public:
					ws_client(const std::string& host_port_path, unsigned short default_port = 80) :
                            ws_client_base(host_port_path, default_port)
					{

						
					}

		        private:
			        void connect() {
			            asio::ip::tcp::resolver::query query(host, std::to_string(port));

			            asio_resolver.async_resolve(query, [this]
			                    (const asio::error_code &ec, asio::ip::tcp::resolver::iterator it){
			                if(!ec) {
			                    connection=std::unique_ptr<ws_connection>(new ws_connection(new asio::ip::tcp::socket(asio_io_service)));

			                    asio::async_connect(*connection->socket, it, [this]
			                            (const asio::error_code &ec, asio::ip::tcp::resolver::iterator it){
			                        if(!ec) {
			                            handshake();
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
 
  
   		} //namespace ws
   } //namespace network
} //namespace cw
