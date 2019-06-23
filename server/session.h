#ifndef SESSION_H
#define SESSION_H

#include <memory>
#include <array>
#include <boost/asio.hpp>
#include <boost/core/noncopyable.hpp>
#include "protocol.h"

using boost::asio::ip::tcp;

class Manager;

class Session: 
    public std::enable_shared_from_this<Session>, 
    public boost::noncopyable {
    public:
        explicit Session(tcp::socket socket, Manager& manager, std::unique_ptr<Protocol>);
        ~Session() = default;
       
        const tcp::socket& socket() const;
        void start();
        void stop();
        void start_read();
    private:
        tcp::socket _socket;
        Manager& _manager;
        std::unique_ptr<Protocol> _handler;
        std::array<char, 2048> _buffer;
};

#endif // SESSION_H
