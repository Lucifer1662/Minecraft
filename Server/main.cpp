#include "tcp_server.h"
#include <World.h>
#include <udp_server.h>
#include "Player.h"
#include "bits.h"
#include "StreamWorldToClients.h"
#include "MessageResolver.h"
#include <PlayerMovedMessage.h>
#include "ConnectMessage.h"


int main(){

    auto worldGen = std::make_shared<WorldGenerator>();
    auto chunkLoader = std::make_shared<ChunkLoader>(worldGen);
    World::mainWorld = std::make_shared<World>(chunkLoader);
    boost::asio::io_service io_service;

    auto udp_socket = udp_socket::create(io_service);

    auto worldStreamer = std::make_shared<StreamWorldToClients>(World::mainWorld, udp_socket);




    MessageResolver resolver;
    resolver.reserveMaxResolvers(4);
    resolver.addResolver<(size_t)MessageType::GetChunk, GetChunkMessage>();
    resolver.addResolver<(size_t)MessageType::PlayerMovedDirection, PlayerMovedMessage>();

    resolver.resolvers[(size_t)MessageType::Connect] = [=](auto& connection) {
        auto message = connection.read<ConnectMessage>();
        worldStreamer->endpoints.emplace_back(message.address, message.udp_port);

        World::mainWorld->addPlayer(std::make_shared<Player>(World::mainWorld, glm::vec3(0, 5, 0)));
    };
    resolver.addResolver<(size_t)MessageType::PlayerJumped, PlayerJumpedMessage>();




   
    auto worldRun = std::make_shared<bool>(true);

    std::thread worldThread([=]() {
        while (*worldRun) {
            World::mainWorld->update();
            worldStreamer->stream();
        }
    });

    try
    {
        
        int port = 6767;

        tcp_server server(io_service, port);
        server.streamToClients = worldStreamer;
        server.start_accept();

        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    *worldRun = false;
    worldThread.join();

    return 0;
}