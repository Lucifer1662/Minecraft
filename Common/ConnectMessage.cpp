#include "ConnectMessage.h"
#include "tcp_connection.h"

void ConnectMessage::send(tcp_connection& connection)
{
	connection.getMutexWrite().lock();
	connection.write(MessageClass::Request);
	connection.write(MessageType::Connect);
	connection.write(*this);
	connection.getMutexWrite().unlock();
}

void ConnectMessage::respond(tcp_connection& connection)
{
	
}
