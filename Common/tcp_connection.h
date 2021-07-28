#pragma once
#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;
#include <mutex>
#include <unordered_map>
#include <future>
#include "MessageResolver.h"

class tcp_connection
{
    tcp::iostream stream_;
    std::mutex mutexRead;
    std::mutex mutexWrite;
    std::weak_ptr<tcp_connection> self;
    MessageResolver resolver;

public:
 
    template<typename T>
    T read() {
        T t;           
        auto buffer = boost::asio::buffer((void*)&t, sizeof(T));
        auto open = socket().is_open();
        boost::asio::read(socket(), buffer, boost::asio::transfer_exactly(sizeof(T)));
        return t;
    }

    void read(void* data, int size);

    void writeBuf(boost::asio::streambuf& buffer) {
        boost::asio::write(socket(), buffer);
    }

    template<typename T>
    void write(const T& object) {
        boost::asio::write(socket(), boost::asio::buffer((void*)&object, sizeof(T)));
    }

    typedef std::shared_ptr<tcp_connection> pointer;
    static pointer create(boost::asio::io_service& io_service);

    tcp::socket& socket();

    void start();

    std::lock_guard<std::mutex>&& getGuardWrite();
    std::lock_guard<std::mutex>&& getGuardRead();
    std::mutex& getMutexRead();
    std::mutex& getMutexWrite();

    MessageResolver& getMessageResolver();

    tcp::iostream& stream();
    

    tcp_connection(const tcp_connection&) = default;
    tcp_connection(tcp_connection&&) = default;
    tcp_connection(boost::asio::io_service& io_service);
private:
  
};




