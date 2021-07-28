#pragma once
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

class udp_server
{
    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    std::vector<char> recv_buffer_;


public:
    std::vector<void(*)(std::istream&)> responses;
    udp_server(boost::asio::io_context& io_context, int port);


    void start_receive();
private:
    void handle_receive(const boost::system::error_code& error,
        std::size_t /*bytes_transferred*/);

    void handle_send(boost::shared_ptr<std::string> /*message*/,
        const boost::system::error_code& /*error*/,
        std::size_t /*bytes_transferred*/);

  
};

