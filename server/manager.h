#ifndef MANAGER_H
#define MANAGER_H

#include <set>
#include <memory>
#include "session.h"

class Manager {
    public:
        Manager() = default;
        Manager(const Manager&) = delete;
        Manager& operator = (const Manager&) = delete;

        void start(std::shared_ptr<Session>);
        void stop(std::shared_ptr<Session>);
        void stop_all();

    private:
        std::set<std::shared_ptr<Session>> _sessions;
};

#endif // MANAGER_H
