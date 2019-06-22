#ifndef CONSOLE_HANDLER_H
#define CONSOLE_HANDLER_H

#include <memory>
#include <mutex>
#include "handler.h"


class ConsoleHandler: public IHandler {
    public:
        void flush() override;
        void emit(const Record&) override;
        ~ConsoleHandler();

    private:
        std::mutex _mutex;
};

#endif // CONSOLE_HANDLER_H
