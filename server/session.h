#ifndef SESSION_H
#define SESSION_H

#include <iostream>
#include <memory>
#include <boost/asio.hpp>
#include <boost/core/noncopyable.hpp>
#include "handler.h"

using boost::asio::ip::tcp;


class Session: 
    public std::enable_shared_from_this<Session>, 
    public boost::noncopyable {
    public:
        Session(tcp::socket socket, IHandler*);
        ~Session();
       
        tcp::socket& socket();
        void start_read();
    private:
        IHandler* _handler;
        tcp::socket _socket;
        boost::asio::streambuf _buffer;
};

#endif // SESSION_H
