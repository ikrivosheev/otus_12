#include <ostream>
#include "console_handler.h"


void ConsoleHandler::flush() {
    std::cout.flush();
}

void ConsoleHandler::emit(const Record& record) {
    {
        std::unique_lock<std::mutex> u_lock(_mutex);
        std::cout << record.str() << ConsoleHandler::TERMINATOR;
    }
}

ConsoleHandler::~ConsoleHandler() {
    flush();
}
