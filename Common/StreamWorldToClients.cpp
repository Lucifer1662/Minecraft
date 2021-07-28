#include "StreamWorldToClients.h"
#include "UdpPackets.h"


StreamWorldToClients::StreamWorldToClients(std::shared_ptr<World> world, std::shared_ptr<udp_socket> socket):
	world(world), udp(socket)
{
}

void StreamWorldToClients::stream()
{
	for (auto& player : world->getPlayers()) {

		
		Packet<PlayerPosition> packet;
		packet.id = player->getPlayerID();
		packet.position = player->getPosition();
		packet.type = PacketTypes::PlayerPosition;
		if (packet.position != glm::vec3(0, 5, 0)) {
			int w = 0;
		}
		udp->writeToAll(packet, endpoints);
	}
}
