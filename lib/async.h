#pragma once

#include <cstddef>
#include <memory>
#include "logger.h"
#include "state_machine.h"
#include "console_handler.h"
#include "file_handler.h"

namespace async {
    
    class AsyncProxy {
        public:
            AsyncProxy(std::size_t bulk, const char*, std::size_t);
            AsyncProxy(const AsyncProxy&) = default;
            AsyncProxy(AsyncProxy&&) = default;
            
            AsyncProxy& operator = (const AsyncProxy&) = default;
            AsyncProxy& operator = (AsyncProxy&&) = default;
            ~AsyncProxy() = default;

            void update(const char* data, std::size_t size);

        private:
            std::string _sep;
            std::string _buffer;
            StateMachine _state;
    };

    using handle_t = AsyncProxy*;

    handle_t connect(std::size_t bulk, const char*, std::size_t);
    void receive(handle_t handle, const char *data, std::size_t size);
    void disconnect(handle_t handle);
}
