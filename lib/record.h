#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <chrono>
#include <ctime>

class Record {
    public:
        Record(const std::string&);
        Record(const std::string&, const std::time_t&);
        Record(const Record&) = default;

        const std::string& str() const;
        const std::time_t& time() const;
        ~Record() = default;

    private:
        std::string _str;
        std::time_t _time;
};

#endif // RECORD_H
