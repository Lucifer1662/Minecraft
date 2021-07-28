#include "udp_server.h"
#include <boost/interprocess/streams/vectorstream.hpp>
#include "Message.h"
#include "bits.h"

udp_server::udp_server(boost::asio::io_context& io_context, int port)
    : socket_(io_context, udp::endpoint(udp::v4(), port))
{
}

void udp_server::start_receive()
{
    socket_.async_receive_from(
        boost::asio::buffer(recv_buffer_), remote_endpoint_,
        boost::bind(&udp_server::handle_receive, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void udp_server::handle_receive(const boost::system::error_code& error, std::size_t)
{
    if (!error)
    {        
        auto isVec = boost::interprocess::basic_ivectorstream<std::vector<char>>(recv_buffer_, std::ios_base::binary);
        MessageType type;
        isVec >> bits(type);
        responses[(size_t)type](isVec);


        boost::shared_ptr<std::string> message(new std::string());

        socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_,
            boost::bind(&udp_server::handle_send, this, message,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));

        start_receive();
    }
}

void udp_server::handle_send(boost::shared_ptr<std::string>, const boost::system::error_code&, std::size_t)
{
}
