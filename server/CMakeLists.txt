# cmake_minimum_required(VERSION 3.10)
# project(BastardPixelBattle VERSION 1.0.0 LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(Boost COMPONENTS thread REQUIRED)

# file(GLOB_RECURSE SOURCES
#         "commands/*.cpp"
#         "commands/*.h"
#         # "network/*.h"
#         # "network/*.cpp"
#         "session/*.h"
#         "session/*.cpp"
#         "utility/*.h"
#         "main.cpp"
#         # "*.h"
# )

# add_executable(${PROJECT_NAME}
#         ${SOURCES}
# )

# target_include_directories(${PROJECT_NAME} PRIVATE
#         ${CMAKE_CURRENT_SOURCE_DIR}/commands
#         ${CMAKE_CURRENT_SOURCE_DIR}/utility
#         # ${CMAKE_CURRENT_SOURCE_DIR}/network
#         ${CMAKE_CURRENT_SOURCE_DIR}/session
#         ${Boost_INCLUDE_DIRS}
# )


# target_link_libraries(
#         ${PROJECT_NAME}
#         Boost::thread
# )

cmake_minimum_required(VERSION 3.14)
project(BastardPixelBattle VERSION 1.0.0 LANGUAGES CXX)



set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(nlohmann_json REQUIRED)
find_package(Boost COMPONENTS thread REQUIRED)

add_subdirectory(session)
add_subdirectory(commands)
add_subdirectory(network)



add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PRIVATE session network commands Boost::thread)

enable_testing()
add_subdirectory(tests)


target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/commands
        ${CMAKE_CURRENT_SOURCE_DIR}/utility
        ${CMAKE_CURRENT_SOURCE_DIR}/session
        ${Boost_INCLUDE_DIRS}
)