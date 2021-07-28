#include "MessageResolver.h"
#include "tcp_connection.h"
#include "Message.h"
#include "PlayerMovedMessage.h"

std::vector<std::function<void(tcp_connection&)>> MessageResolver::resolvers;
size_t MessageResolver::nextId;


MessageResolver::MessageResolver()
{
}

void MessageResolver::resolveMessage(tcp_connection& connection) {

	connection.getMutexRead().lock();
	auto messageClass = connection.read<MessageClass>();
	if (messageClass == MessageClass::Request) {
		auto messageType = connection.read<MessageType>();
		connection.getMutexRead().unlock();
		MessageResolver::resolvers[(size_t)messageType](connection);
	}
	//if is a response
	else  {
		auto messageID = connection.read<MessageID>();
		connection.getMutexRead().unlock();

		
		auto it = responseHandlers.find(messageID);
		if (it != responseHandlers.end()) {
			connection.getMutexWrite().lock();
			it->second(connection);
			connection.getMutexWrite().unlock();
		}
	}

}

MessageID MessageResolver::addRequest(std::function<void(tcp_connection&)>&& responseHandler)
{
	responseHandlers.insert_or_assign(nextId, responseHandler);
	nextId++;
	return nextId - 1;
}

void MessageResolver::initResolvers()
{
	
}


