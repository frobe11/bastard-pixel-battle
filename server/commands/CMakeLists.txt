add_library(commands STATIC        
        Command.cpp
        Command.h
)

target_link_libraries(commands PRIVATE session)


target_include_directories(commands PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)
