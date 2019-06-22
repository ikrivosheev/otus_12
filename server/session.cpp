#include "session.h"


Session::Session(tcp::socket socket, IHandler* handler): 
    _socket(std::move(socket)), _handler(handler) {}

Session::~Session() {
    delete _handler;
}

tcp::socket& Session::socket() {
    return _socket;
}

void Session::start_read() {
    auto self(shared_from_this());
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
                _socket.close();
            }
    });
}

