#ifndef BULK_HANDLER_H
#define BULK_HANDLER_H

#include <memory>
#include "async.h"
#include "protocol.h"
#include "session.h"


class BulkProtocol: public Protocol {
    public:
        BulkHandler(const int&);
        void connection_made(std::shared_ptr<Session>) override;
        void data_received(char*, std::size_t) override;
        void connection_lost() override;

        ~BulkHandler() = default;

    private:
        int _bulk;
        async::handle_t _handler;
};

#endif // BULK_HANDLER_H
