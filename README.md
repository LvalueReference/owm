[![Linux](https://github.com/LvalueReference/openweathermap/actions/workflows/Linux.yml/badge.svg?branch=master)](https://github.com/LvalueReference/openweathermap/actions/workflows/Linux.yml)
[![Windows](https://github.com/LvalueReference/openweathermap/actions/workflows/Windows.yml/badge.svg?branch=master)](https://github.com/LvalueReference/openweathermap/actions/workflows/Windows.yml)
[![MacOS](https://github.com/LvalueReference/owm/actions/workflows/MacOs.yml/badge.svg)](https://github.com/LvalueReference/owm/actions/workflows/MacOs.yml)
[![CodeFactor](https://www.codefactor.io/repository/github/lvaluereference/owm/badge)](https://www.codefactor.io/repository/github/lvaluereference/owm)
![OWM](./owm_logo.png)

OWM
==================================
`OWM` is a C++ implementation of the [OpenWeatherMap API](https://openweathermap.org/api)

# Before the beginning
First of all, to start working with the library, you need to get an API key provided by OpenWeatherMap. You can create a key [here](https://home.openweathermap.org/api_keys). It is important to note that with a free subscription, you will only be able to receive the current weather. To get access to all the features of the API, you need to purchase a subscription. After you have received the key, you can start working with the library.

**IMPORTANT!** Access to the OpenWeatherMap API services is provided by a paid subscription and with a free subscription you will not have access to all the functionality of the library. Learn more about subscribing to the service [here](https://openweathermap.org/price).

# Quick start
Include the weather.hpp header file to use the library
```cpp
#include "owm/weather.hpp"
```

## Token
First we need to create an object of the `owm::token` class that will store your API key and settings for the library

```cpp
owm::token token{"API key"};
```
The class can also take 2 optional arguments `owm::units` and `owm::lang`.

`owm::units` is an enum that specifies which temperature scale to use:
* `owm::units::metric` to use Celsius scale
* `owm::units::imperial` to use Fahrenheit scale
* `owm::units::standard` default parameter

`owm::lang` is also an enum that specifies which language will be displayed in the output. For example, `owm::lang::ru` indicates that the Russian language will be used (`owm::lang::en` by default language). All available languages can be found [here](https://openweathermap.org/current#multi) and their code is fully consistent with the code in the enum structure.

So we can get the following code:
```cpp
owm::token token{"API key", owm::units::metric, owm::lang::ru};
```

Each of the parameters can be specified separately, leaving only `owm::units` or `owm::lang`:
```cpp
owm::token token{"API key", owm::units::metric};
```
```cpp
owm::token token{"API key", owm::lang::ru};
```

# How to get weather
## `owm::weather`
To interact with the API, there is a main class `owm::weather`:
```cpp
owm::weather<Response> weather{token};
```

The class takes an object of type `owm::token` as a constructor parameter.

As a template (`Response`), the class accepts one of the structures that contains methods for interacting with the type of weather:
* `owm::current` - indicates that the `owm::weather` class will interact with the current weather
* `owm::hourly` - specifies that the `owm::weather` class will interact with the hourly weather forecast

So you can get the following code:
```cpp
owm::weather<owm::current> current_weather{token};
owm::weather<owm::hourly> hourly_forecast{token};
```

The class contains one single template method `by()`, which returns an object of type Response, which we passed to the class template `owm::weather`

Its signature looks like this:
```cpp
Response owm::weather::by<owm::wtag>(args...);
```
`owm::wtag` is an enum that specifies how we get the city we want to know the weather for.

It can take:
* `owm::city_name` - Specifies that the city will be retrieved by its name
* `owm::city_id` - Specifies that the city will be retrieved by id (city IDs can be found [here](https://bulk.openweathermap.org/sample/))
* `owm::geo_coords` - pecifies that the city will be retrieved by coordinates

The passed function parameter depends on the enum value that we passed to the template. A string for `owm::city_name`, an integer for `owm::city_id` and 2 floats for `owm::geo_coords`, which should represent latitude and longitude (in order).
```cpp
owm::weather<owm::current> weather{token};

auto by_city_name = weather.by<owm::city_name>("New-York");
auto by_id = weather.by<owm::city_id>(1234);
auto by_coords = weather.by<owm::geo_coords>(123.4, 567.8);
```

In case of an API error, the `by()` method will throw an exception of type `owm::exception`, where you can get more specific information about the error.

## Response classes
These classes contain methods that are described in the OpenWeatherMap API documentation

* For `owm::current` [here](https://openweathermap.org/current#:~:text=%3A%20200%0A%7D-,%D0%9F%D0%BE%D0%BB%D1%8F%20%D0%B2%20%D0%BE%D1%82%D0%B2%D0%B5%D1%82%D0%B5%20API,-coord)
* For `owm::hourly` [here](https://openweathermap.org/api/hourly-forecast#:~:text=%3A%201661882248%0A%20%20%7D%0A%7D-,Fields%20in%20API%20response,-cod%20Internal%20parameter)

In addition to the above, the `owm::hourly` class contains the `list()` method, which returns a `std::vector<owm::hourly_list>`, which stores the list methods described in the json string. List methods can be found [here](https://openweathermap.org/api/hourly-forecast#:~:text=this%20API%20call-,list,-list.dt%20Time).
```cpp
owm::weather<owm::hourly> forecast{token};
std::cout << "City: " << forecast.by<owm::city_name>("City").description() << std::endl; //using owm::hourly class methods
std::cout << "Forecast:" << std::endl;

for (const auto& elem : forecast.list()){
  std::cout << elem.temp_max() << std::endl; //using owm::hourly_list class methods
}
```

A better example can be found [here](./examples/example.cpp).

# CMake integration
The project can be easily linked to your cmake project
```cmake
cmake_minimum_required(VERSION ${CMAKE_VERSION})
project(test_proj CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(owm)
add_executable(test_proj main.cpp)

target_link_libraries(test_proj PUBLIC owm)
```
# Building
```sh
# Clone the repository
git clone https://github.com/LvalueReference/owm.git
cd owm

# Build the library
mkdir build
cd build
cmake ..
cmake --build .
```

# License
The project is available under the [MIT](https://opensource.org/licenses/MIT) license.