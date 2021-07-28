#include "tcp_connection.h"
#include "MessageResolver.h"

void tcp_connection::read(void* data, int size) {
    auto buffer = boost::asio::buffer(data, size);
    auto open = socket().is_open();
    boost::asio::read(socket(), buffer, boost::asio::transfer_exactly(size));
}

tcp_connection::pointer tcp_connection::create(boost::asio::io_service& io_service)
{
    auto tcp = std::make_shared<tcp_connection>(io_service);
    tcp->self = tcp;
    return tcp;
}

 tcp::socket& tcp_connection::socket()
{
    return (tcp::socket&)stream_.socket();
}

 void tcp_connection::start()
{
     while (true) {
         resolver.resolveMessage(*this);
     }
}

 std::lock_guard<std::mutex>&& tcp_connection::getGuardWrite()
 {
     return std::lock_guard<std::mutex>(mutexWrite);
 }

 std::lock_guard<std::mutex>&& tcp_connection::getGuardRead()
 {
     return std::lock_guard<std::mutex>(mutexRead);
 }

 std::mutex& tcp_connection::getMutexRead()
 {
     return mutexRead;
 }

 std::mutex& tcp_connection::getMutexWrite()
 {
     return mutexWrite;
 }

 MessageResolver& tcp_connection::getMessageResolver()
 {
     return resolver;
 }

 tcp::iostream& tcp_connection::stream()
 {
     return stream_;
 }

 tcp_connection::tcp_connection(boost::asio::io_service& io_service)
    : stream_(std::move(tcp::socket(io_service)))
{
    
}

 
