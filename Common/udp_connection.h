#pragma once
#include <iostream>
#include <string>
#include <boost/asio.hpp>

#include <mutex>
#include "MessageResolver.h"
using boost::asio::ip::udp;
#include <boost/interprocess/streams/vectorstream.hpp>
#include <array>
#include <vector>

class udp_socket
{
    udp::socket socket_;
    std::mutex mutexRead;
    std::mutex mutexWrite;
    std::weak_ptr<udp_socket> self;
public:

    std::istream&& read();

    template<typename T> 
    T read() {
        T t;
        boost::asio::ip::udp::endpoint e;
        socket_.receive_from(boost::asio::buffer(&t, sizeof(T)), e);
        return t;
    }
   
    void writeBuf(const boost::asio::mutable_buffer& b, const boost::asio::ip::udp::endpoint& receiver_endpoint);

    void writeBuf(const boost::asio::const_buffer& b, const boost::asio::ip::udp::endpoint& receiver_endpoint);

    template<typename T>
    void write(const T& object, const boost::asio::ip::udp::endpoint& receiver_endpoint) {
        writeBuf(boost::asio::buffer((void*)&object, sizeof(T)), receiver_endpoint);
    }

    template<typename T, typename Vec>
    void writeToAll(const T& t, const Vec& endpoints) {
        for (auto& endpoint : endpoints) {
            write(t, endpoint);
        }
    }

    typedef std::shared_ptr<udp_socket> pointer;
    static pointer create(boost::asio::io_service& io_service);

    udp::socket& socket();


    udp_socket(const udp_socket&) = default;
    udp_socket(udp_socket&&) = default;
    udp_socket(boost::asio::io_service& io_service);
};


class udp_connection {

    std::shared_ptr<udp_socket> socket;

    boost::asio::ip::udp::endpoint receiver_endpoint;
    boost::asio::ip::udp::endpoint sender_endpoint;

    udp_connection(boost::asio::ip::udp::endpoint receiver_endpoint,
        boost::asio::ip::udp::endpoint sender_endpoint) :
        receiver_endpoint(receiver_endpoint), sender_endpoint(sender_endpoint) {}







};







