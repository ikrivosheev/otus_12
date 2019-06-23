#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <signal.h>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/core/noncopyable.hpp>

#include "session.h"
#include "protocol.h"
#include "manager.h"

using boost::asio::ip::tcp;


class Server: public boost::noncopyable {
    public:
        Server(boost::asio::io_service& ios, short port):
            _ios(ios), _signals(ios), _acceptor(_ios, tcp::endpoint(tcp::v4(), port)) {

            _signals.add(SIGINT);
            _signals.add(SIGTERM);
            do_await_stop();
        }; 
        ~Server() = default;

        template<typename T, typename ...Args>
        void start_accept(const Args&... args) {
            static_assert(std::is_base_of<Protocol, T>::value, "Handler must be extend Protocol");
             _acceptor.async_accept([this, args...](const boost::system::error_code& error, tcp::socket socket) {
                if (!_acceptor.is_open()) {
                    return;
                }
                if (!error) {        
                    std::unique_ptr<Protocol> handler = std::make_unique<T>(std::forward<const Args&>(args)...);
                    std::shared_ptr<Session> session = std::make_shared<Session>(
                    std::move(socket), 
                    _manager,
                    std::move(handler)
                );
                _manager.start(session);
                }
                else {
                    std::cerr << "Error on accept" << error.message() << std::endl;
                }
                start_accept<T, Args...>(std::forward<const Args&>(args)...);
            });
        }
        
        void do_await_stop() {
            _signals.async_wait(
            [this](boost::system::error_code /*ec*/, int /*signo*/) {
                _acceptor.close();
                _manager.stop_all();
            });
}

    private:
        boost::asio::io_service& _ios;
        boost::asio::signal_set _signals;
        tcp::acceptor _acceptor;
        Manager _manager;
};

#endif // SERVER_H
