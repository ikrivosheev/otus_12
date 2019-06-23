#ifndef HANDLER_H
#define HANDLER_H

#include <cstddef>
#include <memory>

class Session;

class Protocol {
    public:
        virtual void connection_made(std::shared_ptr<Session>) = 0;
        virtual void data_received(char*, std::size_t) = 0;
        virtual void connection_lost() = 0;
        virtual ~Protocol() = default;
};


#endif // HANDLER_H
