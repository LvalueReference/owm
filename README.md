[![Linux](https://github.com/LvalueReference/openweathermap/actions/workflows/Linux.yml/badge.svg?branch=master)](https://github.com/LvalueReference/openweathermap/actions/workflows/Linux.yml)
[![Windows](https://github.com/LvalueReference/openweathermap/actions/workflows/Windows.yml/badge.svg?branch=master)](https://github.com/LvalueReference/openweathermap/actions/workflows/Windows.yml)
[![MacOS](https://github.com/LvalueReference/openweathermap/actions/workflows/MacOs.yml/badge.svg)](https://github.com/LvalueReference/openweathermap/actions/workflows/MacOs.yml)
[![CodeFactor](https://www.codefactor.io/repository/github/lvaluereference/openweathermap/badge/master)](https://www.codefactor.io/repository/github/lvaluereference/openweathermap/overview/master)

OpenWeatherMap
==================================

Quick Start
-----------

This library is easy to assemble using the Cmake project

* Copy the repository to your project

  ```sh
  git clone --recursive https://github.com/LvalueReference/openweathermap
  ```
* Include library to your CMake project<br>
  For example:

  ```cmake
  cmake_minimum_required(VERSION 3.16)
  project(test)

  add_subdirectory(openweathermap)

  add_executable(test main.cpp)
  target_link_libraries(test owm)
  ```

  Ready!

How to use
----------

Read the [Documentation](./doc/basics.md)