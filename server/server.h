#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/core/noncopyable.hpp>

#include "session.h"
#include "protocol.h"

using boost::asio::ip::tcp;


class Server: public boost::noncopyable {
    public:
        Server(boost::asio::io_service& ios, short port):
            _ios(ios), _acceptor(_ios, tcp::endpoint(tcp::v4(), port)) {}; 
        ~Server() = default;

        template<typename T, typename ...Args>
        void start_accept(const Args&... args) {
            static_assert(std::is_base_of<Protocol, T>::value, "Handler must be extend Protocol");
             _acceptor.async_accept([this, args...](const boost::system::error_code& error, tcp::socket socket) {
                if (!error) {        
                    std::unique_ptr<Protocol> handler = std::make_unique<T>(std::forward<const Args&>(args)...);
                    std::shared_ptr<Session> session = std::make_shared<Session>(
                    std::move(socket), 
                    std::move(handler)
                );
                session->start_read();
                }
                else {
                    std::cerr << "Error on accept" << error.message() << std::endl;
                }
                start_accept<T, Args...>(std::forward<const Args&>(args)...);
            });
        }

    private:
        boost::asio::io_service& _ios;
        tcp::acceptor _acceptor;
};

#endif // SERVER_H
