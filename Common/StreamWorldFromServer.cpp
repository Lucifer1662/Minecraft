#include "StreamWorldFromServer.h"
#include "UdpPackets.h"
#include "bits.h"

void StreamWorldFromServer::recieve()
{

	auto type = udp->read<PacketTypes>();
	if (type == PacketTypes::PlayerPosition) {

		auto playerPos = udp->read<PlayerPosition>();
		world->getPlayerOfId(playerPos.id)->getPosition() = playerPos.position;
	}

	
	
}

StreamWorldFromServer::StreamWorldFromServer(std::shared_ptr<World> world, std::shared_ptr<udp_socket> udp) 
	: world(world), udp(udp)
{
}
