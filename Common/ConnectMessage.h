#pragma once
#include "Message.h"
#include "PlayerID.h"
#include <boost/asio.hpp>

struct ConnectMessage
{
	boost::asio::ip::port_type udp_port;
	boost::asio::ip::address address;
	PlayerID playerId;
	void send(tcp_connection& connection);
	void respond(tcp_connection& connection);
};

