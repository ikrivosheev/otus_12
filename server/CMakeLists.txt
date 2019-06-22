set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED system)

add_library(server server.cpp session.cpp)

set_target_properties(server PROPERTIES
   CXX_STANDARD 14
   CXX_STANDARD_REQUIRED ON
   COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

