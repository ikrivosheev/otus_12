#ifndef SESSION_H
#define SESSION_H

#include <iostream>
#include <memory>
#include <boost/asio.hpp>
#include <boost/core/noncopyable.hpp>
#include "protocol.h"

using boost::asio::ip::tcp;

class Session: 
    public std::enable_shared_from_this<Session>, 
    public boost::noncopyable {
    public:
        Session(tcp::socket socket, std::unique_ptr<Protocol>);
        ~Session() = default;
       
        const tcp::socket& socket() const;
        void start_read();
    private:
        std::unique_ptr<Protocol> _handler;
        tcp::socket _socket;
        boost::asio::streambuf _buffer;
};

#endif // SESSION_H
