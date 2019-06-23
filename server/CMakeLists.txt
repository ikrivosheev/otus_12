add_library(server session.cpp manager.cpp)

set_target_properties(server PROPERTIES
   CXX_STANDARD 14
   CXX_STANDARD_REQUIRED ON
   COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

target_include_directories(server PUBLIC ${CMAKE_SOURCE_DIR})
