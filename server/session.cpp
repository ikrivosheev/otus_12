#include "manager.h"
#include "session.h"


Session::Session(tcp::socket socket, Manager& manager, std::unique_ptr<Protocol> handler): 
    _socket(std::move(socket)), _manager(manager), _handler(std::move(handler)) {}

const tcp::socket& Session::socket() const {
    return _socket;
}

void Session::start() {
    _handler->connection_made(shared_from_this());
    start_read();
}

void Session::stop() {
    _handler->connection_lost();
    _socket.close();
}

void Session::start_read() {
    auto self(shared_from_this());
    _socket.async_read_some(
        boost::asio::buffer(_buffer), 
        [this, self](
            const boost::system::error_code& error, 
            std::size_t bytes_transferred) {
                if (!error) {
                    self->_handler->data_received(_buffer.data(), bytes_transferred);
                    start_read();
                }
                else if (error != boost::asio::error::operation_aborted) {
                    _manager.stop(shared_from_this());
                }
        });
}

