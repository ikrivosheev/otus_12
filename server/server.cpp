#include <type_traits>
#include "server.h"
#include "handler.h"

Server::Server(boost::asio::io_service& ios, short port):
    _ios(ios), _acceptor(_ios, tcp::endpoint(tcp::v4(), port)) {}

