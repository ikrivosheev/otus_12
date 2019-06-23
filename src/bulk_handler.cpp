#include "bulk_handler.h"

BulkProtocol::BulkProtocol(const int& bulk): _bulk(bulk) {}

void BulkProtocol::connection_made(std::shared_ptr<Session> session) {
    async::connect(std::move(_handler));
}


void BulkProtocol::data_received(char* data, std::size_t size) {
}

void BulkProtocol::connection_lost() {
}

