#include <sstream>
#include "async.h"

namespace async {
    AsyncProxy::AsyncProxy(std::size_t bulk, const char* sep, std::size_t size): 
        _sep(sep, size), _state(bulk) {}

    void AsyncProxy::update(const char* data, std::size_t size) {
        if (!size) {
            return;
        }
        _buffer.append(data, size);
        std::string::size_type prev_pos = 0, pos = 0;
        while ((pos = _buffer.find(_sep, pos)) != std::string::npos) {
            _state.push_command(_buffer.substr(prev_pos, pos-prev_pos));
            pos += _sep.size();
            prev_pos = pos; 
        }
        _buffer = _buffer.substr(prev_pos, pos-prev_pos);
    }

    handle_t connect(std::size_t bulk, const char* sep, std::size_t size) {
        return new AsyncProxy(bulk, sep, size);
    }

    void receive(handle_t handle, const char *data, std::size_t size) {
        handle->update(data, size);
    }

    void disconnect(handle_t handle) {
        delete handle;
    }

}
