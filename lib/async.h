#pragma once

#include <cstddef>
#include "state_machine.h"
#include "logger.h"
#include "console_handler.h"
#include "file_handler.h"

namespace async {
    
    class AsyncProxy {
        public:
            AsyncProxy(std::size_t bulk);
            AsyncProxy(const AsyncProxy&) = default;
            AsyncProxy(AsyncProxy&&) = default;
            
            AsyncProxy& operator = (const AsyncProxy&) = default;
            AsyncProxy& operator = (AsyncProxy&&) = default;
            ~AsyncProxy() = default;

            void update(const char* data, std::size_t size);

        private:
            std::string _buffer;
            StateMachine _state;
    };

    using handle_t = AsyncProxy*;

    handle_t connect(std::size_t bulk);
    void receive(handle_t handle, const char *data, std::size_t size);
    void disconnect(handle_t handle);
}
