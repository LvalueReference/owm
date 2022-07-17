cmake_minimum_required(VERSION 3.16)
project(owm
        LANGUAGES CXX
        DESCRIPTION "OpenWeatherMap API wrapper for C++")

set(CMAKE_CXX_STANDARD 20)

set(OWM_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(OWM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(OWM_BUILD_SHARED_LIBS TRUE)
set(CURL_INCLUDE_DIR ${CURL_SOURCE_DIR}/include)
set(CURL_LIBRARY libcurl)
set(CURLPP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/curlpp/include)

if (${OWM_BUILD_SHARED_LIBS} EQUAL TRUE)
    set(OWM_BUILD_TYPE SHARED)
else()
    set(OWM_BUILD_TYPE STATIC)
endif()

file(GLOB_RECURSE OWM_HEADERS ${OWM_INCLUDE_DIR}/*.hpp)
file(GLOB_RECURSE OWM_SOURCE ${OWM_SOURCE_DIR}/*.cpp)

add_subdirectory(deps)

include_directories(${OWM_INCLUDE_DIR})

add_library(owm ${OWM_BUILD_TYPE} ${OWM_HEADERS} ${OWM_SOURCE})
target_link_libraries(owm PUBLIC 
    CURL::libcurl 
    simdjson::simdjson 
    magic_enum::magic_enum 
    curlpp)
target_include_directories(owm PUBLIC ${CURLPP_INCLUDE_DIR})
target_include_directories(owm PUBLIC ${OWM_INCLUDE_DIR})