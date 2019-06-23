#ifndef BULK_HANDLER_H
#define BULK_HANDLER_H

#include <memory>
#include "lib/async.h"
#include "server/protocol.h"
#include "server/session.h"


class BulkProtocol: public Protocol {
    public:
        BulkProtocol(const int&);
        void connection_made(std::shared_ptr<Session>) override;
        void data_received(char*, std::size_t) override;
        void connection_lost() override;

        ~BulkProtocol() = default;

    private:
        int _bulk;
        async::handle_t _handler;
};

#endif // BULK_HANDLER_H
