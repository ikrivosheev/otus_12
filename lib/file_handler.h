#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>
#include <mutex>
#include <fstream>
#include "handler.h"


class FileHandler: public IHandler {
    public:
        FileHandler(const std::string&);
        FileHandler(const std::string&, const std::string&);
        void flush() override;
        void emit(const Record&) override;
        ~FileHandler();

    private:
        std::mutex _mutex;
        std::string _base_dir;
        std::string _prefix;
        std::ofstream _stream;
};

#endif // FILE_HANDLER_H
