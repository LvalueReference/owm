cmake_minimum_required(VERSION 3.20)
project(example CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(example example.cpp)

target_link_libraries(example PRIVATE owm simdjson::simdjson)