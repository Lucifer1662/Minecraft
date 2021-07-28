#include "tcp_server.h"

tcp_server::tcp_server(boost::asio::io_service& io_service, int port)
    : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
    io_service(io_service)
{

}

void tcp_server::start_accept()
{
    tcp_connection::pointer new_connection =
        tcp_connection::create(io_service);

    acceptor_.async_accept(new_connection->socket(),
        boost::bind(&tcp_server::handle_accept, this, new_connection,
            boost::asio::placeholders::error));
}

void tcp_server::handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code& error)
{
    if (!error)
    {

        new_connection->start();
           
        start_accept();
    }
}
