set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED system)

add_executable(bulk_server main.cpp bulk_handler.cpp)

set_target_properties(bulk_server PROPERTIES
   CXX_STANDARD 14
   CXX_STANDARD_REQUIRED ON
   COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

target_link_libraries(bulk_server async server ${Boost_SYSTEM_LIBRARY} Threads::Threads)
target_include_directories(bulk_server INTERFACE ${Boost_INCLUDE_DIR})
target_include_directories(bulk_server PUBLIC ${CMAKE_SOURCE_DIR})
