#pragma once
#include <memory>
#include "World.h"
#include "boost/asio.hpp"
#include "udp_connection.h"

class StreamWorldToClients
{
	std::shared_ptr<World> world;
	
	std::shared_ptr<udp_socket> udp;
public:
	std::vector<boost::asio::ip::udp::endpoint> endpoints;
	void stream();

	StreamWorldToClients(std::shared_ptr<World> world, std::shared_ptr<udp_socket> socket);
	StreamWorldToClients(const StreamWorldToClients&) = default;
	StreamWorldToClients(StreamWorldToClients&&) = default;
};

