include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(session_tests session_tests.cpp)
target_link_libraries(session_tests PRIVATE session GTest::gtest_main)
gtest_discover_tests(session_tests)

add_executable(commands_tests commands_tests.cpp)
target_link_libraries(commands_tests PRIVATE commands session GTest::gtest_main)
gtest_discover_tests(commands_tests)


#add_executable(network_tests network_tests.cpp)
#target_link_libraries(network_tests PRIVATE network GTest::gtest_main)
#gtest_discover_tests(network_tests)

target_include_directories(session_tests PRIVATE ${PROJECT_SOURCE_DIR})
target_include_directories(commands_tests PRIVATE ${PROJECT_SOURCE_DIR})
#target_include_directories(network_tests PRIVATE ${PROJECT_SOURCE_DIR})