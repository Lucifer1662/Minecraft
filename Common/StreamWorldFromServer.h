#pragma once
#include <memory>
#include "World.h"
#include "boost/asio.hpp"
#include "udp_connection.h"

class StreamWorldFromServer
{
	std::shared_ptr<World> world;
	std::shared_ptr<udp_socket> udp;
public:
	void recieve();

	StreamWorldFromServer(std::shared_ptr<World> world, std::shared_ptr<udp_socket> udp);
	StreamWorldFromServer(const StreamWorldFromServer&) = default;
	StreamWorldFromServer(StreamWorldFromServer&&) = default;
};

