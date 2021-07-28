#pragma once
#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;

#include "tcp_connection.h"
#include "StreamWorldToClients.h"

class tcp_server
{

    tcp::acceptor acceptor_;
    boost::asio::io_service& io_service;
    
public:
    std::shared_ptr<StreamWorldToClients> streamToClients;
   
    tcp_server(boost::asio::io_service& io_service, int port);
    void start_accept();
private:
   

    void handle_accept(tcp_connection::pointer new_connection,
        const boost::system::error_code& error);

};


