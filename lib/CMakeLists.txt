add_library(bulk 
    record.cpp 
    logger.cpp 
    console_handler.cpp 
    file_handler.cpp 
    state_machine.cpp
)

set_target_properties(bulk PROPERTIES
   CXX_STANDARD 14
   CXX_STANDARD_REQUIRED ON
   COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

target_include_directories(bulk PUBLIC ${CMAKE_SOURCE_DIR})
