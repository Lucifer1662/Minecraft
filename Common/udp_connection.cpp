#include "udp_connection.h"

std::istream&& udp_socket::read() {
    std::vector<char> data(20);
    boost::asio::ip::udp::endpoint e;
    auto local = socket_.local_endpoint();
    std::cout << local.port() << " " << local.address();
    size_t received = socket_.receive_from(boost::asio::buffer(data), e);
    return boost::interprocess::basic_ivectorstream<std::vector<char>>(data, std::ios_base::binary);
}

boost::asio::ip::port_type  x = 6767;
void udp_socket::writeBuf(const boost::asio::mutable_buffer& b, const boost::asio::ip::udp::endpoint& receiver_endpoint) {
//    auto e = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), x);
   auto sent = socket().send_to(b, receiver_endpoint);
}

void udp_socket::writeBuf(const boost::asio::const_buffer& b, const boost::asio::ip::udp::endpoint& receiver_endpoint) {
    socket().send_to(b, receiver_endpoint);
}

udp_socket::pointer udp_socket::create(boost::asio::io_service& io_service)
{
    auto ptr = std::make_shared<udp_socket>(io_service);
    ptr->self = ptr;
    return ptr;
}

udp::socket& udp_socket::socket()
{
    return socket_;
}

udp_socket::udp_socket(boost::asio::io_service& io_service)
    : socket_(io_service)
{
    socket_.open(udp::v4());
}
