#ifndef CIALLOO_NETWORK_WEBSOCKET_CLIENT_HPP
#define CIALLOO_NETWORK_WEBSOCKET_CLIENT_HPP

#include <iostream>
#include <functional>
#include <string>
#include <boost/asio.hpp>
#include <boost/beast.hpp>

namespace cialloo {
namespace network {

class websocket_client
{
public:
    websocket_client(std::string hostname, int port, std::string handshake_path);
    ~websocket_client();

    websocket_client(const websocket_client&) = delete;
    websocket_client& operator=(const websocket_client&) = delete;

public:
    void run();
    void on_received_text(std::function<void(std::string)> callback);

private:
    void do_handshake();
    void do_read();

private:
    std::function<void(std::string)> receive_text_callback_;

private:
    int port_;
    std::string hostname_;
    std::string handshake_path_;
    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::endpoint endpoint_;
    boost::beast::flat_buffer buffer_;
    boost::beast::websocket::stream<boost::beast::tcp_stream> client_;
};

inline void websocket_client::run()
{
    io_context_.run();
}

inline void websocket_client::on_received_text(std::function<void(std::string)> callback)
{
    receive_text_callback_ = callback;
}

inline void websocket_client::do_read()
{
    client_.async_read(buffer_, [this](boost::beast::error_code ec, std::size_t bytes_transferred) {
        if(ec)
            std::cout << "There is an error with do_read: "
                      << ec.what()
                      << std::endl;

        if(receive_text_callback_ != nullptr)
            receive_text_callback_(boost::beast::buffers_to_string(buffer_.data()));

        buffer_.clear();
        do_read();
    });
}

inline void websocket_client::do_handshake()
{
    client_.async_handshake(hostname_, handshake_path_, [this](boost::beast::error_code ec) {
        if(ec)
            std::cout << "There is an error with handshake: "
                      << ec.what()
                      << std::endl;
        else
            do_read();
    });
}

inline websocket_client::websocket_client(std::string hostname, int port, std::string handshake_path)
    : hostname_(hostname),
      port_(port),
      handshake_path_(handshake_path),
      receive_text_callback_(nullptr),
      endpoint_(boost::asio::ip::address::from_string(hostname), port),
      client_(io_context_)
{
    client_.next_layer().async_connect(endpoint_, [this](const boost::system::error_code& error) {
        if(error)
            std::cout << "There is an error with websocket_client connect: "
                      << error.what()
                      << std::endl;
        else
            do_handshake();
    });
}

inline websocket_client::~websocket_client()
{
}


} // namespace network
} // namespace cialloo

#endif