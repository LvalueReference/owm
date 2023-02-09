cmake_minimum_required(VERSION 3.16)
project(owm
        LANGUAGES CXX
        DESCRIPTION "OpenWeatherMap API client on C++"
        HOMEPAGE_URL "https://github.com/LvalueReference/owm")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
    
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    
message(STATUS "OWM: Build type - ${CMAKE_BUILD_TYPE}")

include(FetchContent)

message(STATUS "OWM: Installing libraries...")

FetchContent_Declare(
    curl
    GIT_REPOSITORY https://github.com/curl/curl
)

FetchContent_Declare(
    curlpp
    GIT_REPOSITORY https://github.com/jpbarrette/curlpp
)

FetchContent_Declare(
    simdjson
    GIT_REPOSITORY https://github.com/simdjson/simdjson.git
)

FetchContent_Declare(
    magic_enum
    GIT_REPOSITORY https://github.com/Neargye/magic_enum
)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
)

set(OWM_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(OWM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(OWM_BUILD_SHARED_LIBS TRUE)
set(CURL_LIBRARY libcurl)
set(CURL_INCLUDE_DIR ${CURL_SOURCE_DIR}/include)

FetchContent_MakeAvailable(curl curlpp simdjson magic_enum)

message(STATUS "OWM: Installing libraries... - done")

if (${OWM_BUILD_SHARED_LIBS} EQUAL TRUE)
    set(OWM_BUILD_TYPE SHARED)
else()
    set(OWM_BUILD_TYPE STATIC)
endif()

file(GLOB_RECURSE OWM_HEADERS ${OWM_INCLUDE_DIR}/*.hpp)
file(GLOB_RECURSE OWM_SOURCE ${OWM_SOURCE_DIR}/*.cpp)

add_subdirectory(examples)

include_directories(${OWM_INCLUDE_DIR})

add_library(owm ${OWM_BUILD_TYPE} ${OWM_HEADERS} ${OWM_SOURCE})

target_link_libraries(
    owm PUBLIC 
    CURL::libcurl 
    simdjson::simdjson 
    magic_enum::magic_enum
    curlpp
)

target_include_directories(
        owm PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/owm>
        $<INSTALL_INTERFACE:include/owm>
)

target_include_directories(
        owm PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)