#include <sstream>
#include "state_machine.h"


StateMachine::StateMachine(std::size_t bulk_size): _bulk_size(bulk_size) {}

STATE StateMachine::current_state() {
    return _cstate;
}

void StateMachine::push_command(const std::string& command) {
    switch(_cstate) {
        case STATE::COMMAND:
            if (command == "{") {
                _stack.push('{');
                execute();
                _cstate = STATE::BLOCK;
            }
            else {
                _commands.push_back(command);
                if (_commands.size() == 1) {
                    time(&_time);
                }
                if (_commands.size() == _bulk_size) {
                    execute();
                }
            }
            break;
        case STATE::BLOCK:
            if (command == "{") {
                _stack.push('{');
                break;
            }
            else if (command == "}") {
                _stack.pop();
                if (_stack.empty()) {
                    _cstate = STATE::COMMAND;
                    execute();
                }
            }
            else {
                _commands.push_back(command);
            }
            break;
    }
}

void StateMachine::execute() {
    if (!_commands.size()) return;
    std::stringstream ss;
    ss << "bulk: ";
    for (auto it = _commands.cbegin(); it != _commands.cend(); ++it) {
        if ( it != _commands.cbegin()) {
            ss << ", ";
        }
        ss  << (*it);
    }
    Logger::get().log(ss.str(), _time);
    _commands.clear();
}
