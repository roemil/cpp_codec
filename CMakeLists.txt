cmake_minimum_required(VERSION 3.14)
project(codec)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(include)

add_executable(
    codec_test
    #main.cpp
    codec.cpp
    codec_test.cpp
)
target_link_libraries(
  codec_test gtest_main
)
 
include(GoogleTest)
gtest_discover_tests(codec_test)