cmake_minimum_required(VERSION ${CMAKE_VERSION})
project(example CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(fmt) #fmt::format

add_executable(example example.cpp)

target_link_libraries(example PRIVATE owm)
target_link_libraries(example PRIVATE fmt::fmt)