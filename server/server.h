#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "session.h"

using boost::asio::ip::tcp;


class Server {
    public:
        Server(boost::asio::io_service&, short); 
        ~Server() = default;

        template<typename T, typename ...Args>
        void start_accept(Args... args) {
            static_assert(std::is_base_of<IHandler, T>::value, "Handler must be extend IHandler");
            _acceptor.async_accept([this, args](const boost::system::error_code& error, tcp::socket socket) {
                if (!error) {        
                    std::shared_ptr<Session> session = std::make_shared<Session>(
                    std::move(socket), 
                    T(std::forward<Args>(args)...)
                );
                session->start_read();
                }
                else {
                    std::cerr << "Error on accept" << error.message() << std::endl;
                }
                start_accept<T, Args...>(args...);
            });
        }

    private:
        Server& operator=(const Server&) = delete;
        Server(const Server&) = delete;
        
        boost::asio::io_service& _ios;
        tcp::acceptor _acceptor;
};

#endif // SERVER_H
