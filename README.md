[![Linux](https://github.com/LvalueReference/openweathermap/actions/workflows/Linux.yml/badge.svg?branch=master)](https://github.com/LvalueReference/openweathermap/actions/workflows/Linux.yml)
[![Windows](https://github.com/LvalueReference/openweathermap/actions/workflows/Windows.yml/badge.svg?branch=master)](https://github.com/LvalueReference/openweathermap/actions/workflows/Windows.yml)
[![MacOS](https://github.com/LvalueReference/owm/actions/workflows/MacOs.yml/badge.svg)](https://github.com/LvalueReference/owm/actions/workflows/MacOs.yml)
[![CodeFactor](https://www.codefactor.io/repository/github/lvaluereference/owm/badge)](https://www.codefactor.io/repository/github/lvaluereference/owm)
![OWM](./owm_logo.png)

OWM
==================================
`OWM` is a C++ implementation of the OpenWeatherMap API

Quick Start
-----------

This library is easy to assemble using the Cmake project

* Copy the repository to your project

  ```sh
  git clone --recursive https://github.com/LvalueReference/owm
  ```
* Include library to your CMake project<br>
  For example:

  ```cmake
  cmake_minimum_required(VERSION 3.16)
  project(test)

  add_subdirectory(owm)

  add_executable(test main.cpp)
  target_link_libraries(test owm)
  ```

  Ready!

How to use
----------

Read the [Documentation](./doc/basics.md)

Minimum requirements
--------------------

|C++ Standard |   Clang  |   GCC  |        MSVC        |
|:-----------:|:--------:|:------:|:------------------:|
|    C++20    | clang-14 | gcc-10 | MSVC 19.32.31332.0 |

Note
----

Getting weather via `owm::hourly` is not yet available due to ~~lack of money for a subscription~~ complex implementation