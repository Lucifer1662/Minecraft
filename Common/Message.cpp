#include "Message.h"
#include "MessageResolver.h"
#include "tcp_connection.h"
#include "World.h"
#include <future>
#include <streambuf>
#include "BlockSerialisation.h"

std::future<std::shared_ptr<Chunk>> GetChunkMessage::send(
	tcp_connection& connection)
{
	auto chunk = std::make_shared<std::promise<std::shared_ptr<Chunk>>>();
	auto& resolver = connection.getMessageResolver();

	messageID = resolver.addRequest([=](tcp_connection& connection) {
		chunk->set_value(GetChunkMessage::getChunk(connection, chunkPos));
	});

	connection.getMutexWrite().lock();
	connection.write(MessageClass::Request);
	connection.write(MessageType::GetChunk);
	connection.write(*this);
	connection.getMutexWrite().unlock();

	//auto c = chunk->get_future().get();
	
	return chunk->get_future();
}

std::shared_ptr<Chunk> GetChunkMessage::getChunk(tcp_connection& connection, const glm::ivec3 position)
{
	auto chunk = std::make_shared<Chunk>(position);
	auto& blocks = chunk->getBlocks();
	auto& is = connection.stream();
	auto&& guard = connection.getGuardRead();
	for (auto& block : blocks) {
		
		is >> block;
		//std::cout << connection.read<size_t>();
	}

	return chunk;
}


void GetChunkMessage::respond(tcp_connection& connection)
{
	auto chunk = World::mainWorld->getChunkAt(chunkPos);
	auto& blocks = chunk->getBlocks();

	connection.write(MessageClass::Response);
	connection.write(messageID);
	
	auto& os = connection.stream();

	for (auto& block : blocks) {
		//connection.write(block->blockId());
		os << block;
	}	
}

