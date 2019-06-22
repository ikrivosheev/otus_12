#include "record.h"


Record::Record(const std::string& str) {
    _str = str;
    _time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

Record::Record(const std::string& str, const std::time_t& time) {
    _str = str;
    _time = time;
}

const std::string& Record::str() const {
    return _str;
}

const std::time_t& Record::time() const {
    return _time;
}
