cmake_minimum_required(VERSION ${CMAKE_VERSION})
project(owm
        VERSION 1.2
        LANGUAGES CXX
        DESCRIPTION "OpenWeatherMap API client on C++"
        HOMEPAGE_URL "https://github.com/LvalueReference/owm"
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(OWM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(OWM_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

if (NOT OWM_BUILD_TYPE)
    set(OWM_BUILD_TYPE_V STATIC)
else()
    set(OWM_BUILD_TYPE_V SHARED)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif ()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O2 -g -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

message(STATUS "OWM Build type: ${CMAKE_BUILD_TYPE}")

set(OWM_BUILD_EXAMPLES ON)

if (OWM_BUILD_EXAMPLES)
    message(STATUS "OWM: Build examples option is ON!")
    add_subdirectory(examples)
endif()

add_subdirectory(external/fmt)
add_subdirectory(external/simdjson)
add_subdirectory(external/magic_enum)

file(GLOB_RECURSE OWM_HEADERS CONFIGURE_DEPENDS
    include/owm/*.hpp
)

file(GLOB_RECURSE OWM_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED COMPONENTS SSL Crypto)

add_library(owm ${OWM_BUILD_TYPE_V} ${OWM_SOURCES})
add_library(owm::owm ALIAS owm)

target_link_libraries(
        owm PRIVATE
        Boost::system
        OpenSSL::SSL
        OpenSSL::Crypto
        simdjson::simdjson
        magic_enum::magic_enum
)

target_include_directories(
        owm PRIVATE
        $<BUILD_INTERFACE:${OWM_INCLUDE_DIR}/owm>
        $<INSTALL_INTERFACE:include/owm>
)

target_include_directories(
        owm PUBLIC
        $<BUILD_INTERFACE:${OWM_INCLUDE_DIR}>
        $<INSTALL_INTERFACE:include>
)