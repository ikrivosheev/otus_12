add_executable(bulk_server main.cpp)

set_target_properties(bulk_server PROPERTIES
   CXX_STANDARD 14
   CXX_STANDARD_REQUIRED ON
   COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

target_link_libraries(bulk_server async server)

