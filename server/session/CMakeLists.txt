add_library(session STATIC
        PixelGrid.cpp
        PixelGrid.h
        Session.cpp
        Session.h
        SessionHolder.cpp
        SessionHolder.h
        Color.h
        
)

target_include_directories(session PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)