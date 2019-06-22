#include <csignal>
#include <functional>
#include "logger.h"


Logger::Logger(bool signal) {
    if (signal) {
        std::unique_lock<std::mutex> u_lock(_mutex);
        if (! _signal) {
            std::signal(SIGINT, Logger::signal);
            std::signal(SIGTERM,Logger::signal);
            _signal = true;
        }
    }
}

void Logger::log(const Record& record) {
    for (auto& handler: _handlers) {
        handler.get()->emit(record);
    }
}

void Logger::log(const std::string& str) {
    Record record(str);
    log(record);
}

void Logger::log(const std::string& str, const std::time_t& time) {
    Record record(str, time);
    log(record);
}

void Logger::shutdown(int signum) {
    {
        std::unique_lock<std::mutex> u_lock(_mutex);
        _handlers.clear();
    }
}
