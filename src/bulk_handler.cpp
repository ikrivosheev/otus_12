#include "bulk_handler.h"

BulkProtocol::BulkProtocol(const int& bulk): _state(bulk) {}

void BulkProtocol::connection_made(std::shared_ptr<Session> session) {
}


void BulkProtocol::data_received(char* data, std::size_t size) {
    if (!size) {
        return;
    }
    _buffer.append(data, size);
    std::string::size_type prev_pos = 0, pos = 0;
    while ((pos = _buffer.find("\r\n", pos)) != std::string::npos) {
        _state.push_command(_buffer.substr(prev_pos, pos-prev_pos));
        pos += 2;
        prev_pos = pos; 
    }
    _buffer = _buffer.substr(prev_pos, pos-prev_pos);
}

void BulkProtocol::connection_lost() {
}

