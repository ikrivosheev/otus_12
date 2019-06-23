#include "bulk_handler.h"

BulkProtocol::BulkProtocol(const int& bulk): _bulk(bulk) {}

void BulkProtocol::connection_made(std::shared_ptr<Session> session) {
    _handler = async::connect(_bulk, "\r\n", 2);
}


void BulkProtocol::data_received(char* data, std::size_t size) {
    async::receive(_handler, data, size);
}

void BulkProtocol::connection_lost() {
    async::disconnect(std::move(_handler));
}

