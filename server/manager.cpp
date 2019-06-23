#include "manager.h"

void Manager::start(std::shared_ptr<Session> session) {
    _sessions.insert(session);
    session->start();
}

void Manager::stop(std::shared_ptr<Session> session) {
    _sessions.erase(session);
    session->stop();
}

void Manager::stop_all() { 
    for (auto c: _sessions) {
        c->stop();
    }
    _sessions.clear();
}
