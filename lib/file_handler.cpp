#include <sstream>
#include "file_handler.h"


FileHandler::FileHandler(const std::string& base_dir): _base_dir(base_dir) {}

FileHandler::FileHandler(const std::string& base_dir, const std::string& prefix):
    _base_dir(base_dir), _prefix(prefix) {}


void FileHandler::flush() {
    _stream.flush();
}

void FileHandler::emit(const Record& record) {
    {
        std::unique_lock<std::mutex> u_lock(_mutex);
            if (!_stream.is_open()) {
                std::stringstream ss;
                ss << _base_dir << _prefix << record.time() << ".log";
                _stream.open(ss.str());
            }
        _stream << record.str() << FileHandler::TERMINATOR;
    }
    
}

FileHandler::~FileHandler() {
    {
        std::unique_lock<std::mutex> u_lock(_mutex);
        if (_stream.is_open()) {
            flush();
            _stream.close();
        }
    }
}

