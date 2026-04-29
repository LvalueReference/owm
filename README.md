[![Linux](https://github.com/LvalueReference/openweathermap/actions/workflows/Linux.yml/badge.svg?branch=master)](https://github.com/LvalueReference/openweathermap/actions/workflows/Linux.yml)
[![Windows](https://github.com/LvalueReference/openweathermap/actions/workflows/Windows.yml/badge.svg?branch=master)](https://github.com/LvalueReference/openweathermap/actions/workflows/Windows.yml)
[![MacOS](https://github.com/LvalueReference/owm/actions/workflows/MacOs.yml/badge.svg)](https://github.com/LvalueReference/owm/actions/workflows/MacOs.yml)
[![CodeFactor](https://www.codefactor.io/repository/github/lvaluereference/owm/badge)](https://www.codefactor.io/repository/github/lvaluereference/owm)
![OWM](./owm_logo.png)

# OWM

OWM is a C++ implementation of the OpenWeatherMap API.

# Before you start

## Access Key

In order to start working with the library, you need to obtain an API key for accessing OpenWeatherMap services. The key can be obtained on [this](https://home.openweathermap.org/api_keys) page. Keep in mind that OpenWeatherMap services operate on a subscription basis and with a free key, you will only have access to retrieving [current](https://openweathermap.org/current) weather.

## Namespace

All classes and methods of the library are in the `owm` namespace.

## Header Files

To start working with the library, you need to include the main header file `weather.hpp`.

```C++
#include "owm/weather.hpp"
```
This file includes all the necessary tools for working with the library.

# Beginning of work

## `owm::token`

First of all, you need to declare an object of class `owm::token`, which will contain your API key and settings for the weather. The designer of the class takes 3 parameters:

1. `std::string_view` - Required parameter that should contain a valid access key to OpenWeatherMap API services

2. `owm::units` - An optional parameter, which is an enum structure and means displayed units of measurement upon receipt of an answer from the API.The following arguments can be indicated:
   * `owm::units::metric` - Data display in the metric system
   * `owm::units::imperial` - Data display in the Imperial system
   * `owm::units::standard` - default parameter
3. `owm::lang` - An optional parameter, which is an enum structure and means displayed language when receiving data.
   * `owm::lang::en` - You can clearly indicate that data in English.Also, if you do not specify the parameter `owm::lang`, will be the default parameter
   * All other languages can be recognized on [this](https://openweathermap.org/current#multi) page. The language code on the page is completely coincided with the code in the enum-structure

Also, the parameters of `owm::units` and `owm::lang` can be indicated separately or not indicate at all.In this case, the default parameters will indicate

```cpp
owm::token token{"API key"}; //OK
owm::token token{"API key", owm::units::metric, owm::lang::en}; //OK
owm::token token{"API key", owm::units::metric}; //Ok
owm::token token{"API key", owm::lang::en}; //Ok
```

## `owm::weather`

The class `owm::weather` is the main class that provides an interface for working with the library. Let's look at his announcement.For example:

```cpp
#include "owm/weather.hpp"

owm::token token{"API key", owm::units::metric};
owm::weather<Response> weather{token};
```

The argument of the `Response` template is a class that can take the type of weather with which you want to work. The type of weather is expressed in the classes `owm::current`,`owm::hourly`, `owm::daily`:

1. `owm::current` - The class that contains the interface for working with [current](https://openweathermap.org/current#one) weather
2. `owm::hourly` - [Hourly](https://openweathermap.org/api/hourly-rence) forecast
3. `owm::daily` - Forecast for [days](https://openweathermap.org/forecast16)

Let's create a class for working with current weather:
```cpp
#include "owm/weather.hpp"

owm::token token{"API key", omw::units::metric};
omw::weather<owm::current> current_weather{token};
```

The designer of the class `owm::weather` takes an object of class `owm::token`.

## Getting weather
In order to get the weather for the requested city, there is a method of `.by()`. Let's look at an example:
```cpp
#include "owm/weather.hpp"

owm::token token{"API key", omw::units::metric};
omw::weather<owm::current> current_weather{token};

auto city = current_weather.by<owm::city_name>("Berlin");
```

In the example above, we requested current weather for the city of Berlin. What is `owm::city_name`? This is an enum structure that indicates that the weather request in the city will be made by the name of the city. In total, 3 types of weather query are available:

1. `owm::city_name` - Weather request in the city by its name
2. `owm::city_id` - Weather request for city id (you can find out all ID [here](https://bulk.openweathermap.org/sample/))
3. `owm::geo_coords` - Weather request for geographical coordinates (lat, lon);
   
For example:
```cpp
#include "owm/weather.hpp"

owm::token token{"API key", omw::units::metric};
omw::weather<owm::current> current_weather{token};

auto by_name = current_weather.by<owm::city_name>("Berlin");
auto by_id = current_weather.by<owm::city_id>(1234);
auto by_coords = current_weather.by<owm::geo_coords>(123.4, 567.8);
```

Please note that in the case of working with `owm::hourly` or `owm::daily`, an optional `cnt` parameter is also available, which indicates how much data on the forecast will display.You can specify this parameter after the city argument.For example:
```cpp
#include "owm/weather.hpp"

owm::token token{"API key", omw::units::metric};
omw::weather<owm::daily> daily_weather{token};

auto by_name = daily_weather.by<owm::city_name>("Berlin", /*cnt:*/ 5);
```

## Working with parsed data
Finally, we came to the moment of receipt of data about the weather. To get data, it is necessary to call the `.fetch()` method, for example:

```cpp
#include "owm/weather.hpp"

owm::token token{"API key", omw::units::metric};
omw::weather<owm::daily> daily_weather{token};

auto json = daily_weather.by<owm::city_name>("Berlin").fetch();
```

The `fetch()` method returns a class-explosive class above the object `owm::unwrapped`.:

```cpp
#include "owm/weather.hpp"

owm::token token{"API key", omw::units::metric};
omw::weather<owm::daily> daily_weather{token};

auto unwrapped = daily_weather.by<owm::city_name>("Berlin").fetch();
auto [lon, lat] = std::make_pair(
   *unwrapped["coord"]["lon"].get_double(),
   *unwrapped["coord"]["lat"].get_double()
);
```

A more specific example can be found in [example](examples/example.cpp)

## Error processing
The library has a class for processing API errors - `owm::exception`, which is inherited from`std::exception`.

Error output format: `"owm: code:error message"`

# Project assembly
```sh
git clone https://github.com/LvalueReference/owm.git --recursive
cd owm
mkdir build
cd build
cmake ..
cmake --build .
```

# Used libraries
* simdjson - https://github.com/simdjson/simdjson
* FMT - https://github.com/fmtlib/fmt.git