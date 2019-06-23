#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/core/noncopyable.hpp>

#include "session.h"

using boost::asio::ip::tcp;


template<typename T, typename ...Args>
class Server: public boost::noncopyable {
    public:
        Server(boost::asio::io_service& ios, short port):
            _ios(ios), _acceptor(_ios, tcp::endpoint(tcp::v4(), port)) {}; 
        ~Server() = default;

        void start_accept(Args... args) {
            static_assert(std::is_base_of<IHandler, T>::value, "Handler must be extend IHandler");
             _acceptor.async_accept([this, args...](const boost::system::error_code& error, tcp::socket socket) {
                if (!error) {        
                    IHandler* handler = new T(args...);
                    std::shared_ptr<Session> session = std::make_shared<Session>(
                    std::move(socket), 
                    handler
                );
                session->start_read();
                }
                else {
                    std::cerr << "Error on accept" << error.message() << std::endl;
                }
                start_accept(args...);
            });
        }

    private:
        boost::asio::io_service& _ios;
        tcp::acceptor _acceptor;
};

#endif // SERVER_H
