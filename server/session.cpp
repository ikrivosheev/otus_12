#include "session.h"


Session::Session(tcp::socket socket, std::unique_ptr<Protocol> handler): 
    _handler(std::move(handler)), _socket(std::move(socket)) {
}

const tcp::socket& Session::socket() const {
    return _socket;
}

void Session::start_read() {
    auto self(shared_from_this());
    _handler->connection_made(self);
    boost::asio::async_read_until(
        _socket, 
        _buffer, 
        '\n', 
        [this, self](const boost::system::error_code& error, std::size_t bytes_transferred) {
            if (!error) {
                if (bytes_transferred) {
                    std::string line;
                    std::istream is(&_buffer);
                    std::getline(is, line);

                    if (!line.empty()) {
                        std::cout << "New line: " << line << std::endl;
                    }
                }
                start_read();
            }
            else {
                std::cerr << "Error on read message: " << error.message() << std::endl;
            }
    });
}

