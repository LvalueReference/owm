cmake_minimum_required(VERSION ${CMAKE_VERSION})
project(example CXX)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
)

FetchContent_MakeAvailable(fmt)

add_executable(example example.cpp)

target_link_libraries(example PRIVATE owm)
target_link_libraries(example PRIVATE fmt::fmt)