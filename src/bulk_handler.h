#ifndef BULK_HANDLER_H
#define BULK_HANDLER_H

#include <memory>
#include <string>
#include "lib/state_machine.h"
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
        std::string _buffer;
        StateMachine _state;
};

#endif // BULK_HANDLER_H
