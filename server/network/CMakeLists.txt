add_library(network STATIC        
        NetworkService.cpp
        NetworkService.h
)

target_link_libraries(network PRIVATE commands)
target_link_libraries(network PRIVATE session)

target_include_directories(network PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)
