Documentation
==================

All methods from the library are in the `owm` namespace. The main class for getting weather is the `owm::weather` class.

---

`owm::weather`
--------------
This class is a template class and accepts responses classes as a template: `owm::current_weather_response` (`owm::current` as typedef), `owm::hourly_forecast_response`(`owm::hourly` as typedef).
The class constructor accepts an object of type `owm::token`.

---

`owm::token`
------------
`owm::token` takes as its first parameter an object of type `std::string_view`, which should contain a token that you can get on [official openweathermap site](https://openweathermap.org/). It takes enum `owm::units` as its second parameter, which is the unit of measurement (`owm::units::metric` by default). In total, 3 types of units of measurement are available: `standart`, `metric` and `imperial` (all information can be found [here](https://openweathermap.org/current#data)). As a third parameter, it takes enum `owm::lang` as the third parameter, which means the language in which the data will be displayed (`owm::lang::en` by default) . all available languages can be found [here](https://openweathermap.org/current#multi).

---
So you should end up with a code like this

```cpp
#include "owm/weather.hpp"

owm::token token{"Your token", owm::units::metric, owm::lang::en};
owm::weather<owm::current> weather{token};
```

---

`owm::weather::by`
------------------
The `owm::weather` class has a single template method by that takes as a template enum `owm::wtag` the search type for the location you want to get the weather for. In total, 3 types of search by area are available: by the name of the city (`owm::wtag::city_name`), by its ID (`owm::wtag::city_id`) (you can find the ID [here](http://bulk.openweathermap.org/sample/)) and by its geographical coordinates (`owm::wtag::geo_coords`).
The method takes a template as parameters, which can mean the name of the city, city ID or city coordinates.
```cpp
auto by_name = weather.by<owm::wtag::city_name>("Kyiv");
auto by_id = weather.by<owm::wtag::city_id>(1234);
auto by_geo_coords = weather.by<owm::wtag::geo_coods>(123.45, 678.90);
```
the `by` method returns a structure whose methods completely repeat the json structure, which is described [here](https://openweathermap.org/current#current_JSON)

In case of an error from the API side, the by method will throw `owm::exception`

---

`owm::exception`
----------------
`owm::exception` - a class inherited from `std::exception` that will be thrown in case of errors from the API. The class contains 4 methods for interacting with error codes:

* `owm::exception::what()`
   
   > Virtual method that returns a string with the code and description of the error in the format `owm: code:description`

* `owm::exception::error_message()`
  
  > The method returns a `std::string_view` containing a description of the error

* `owm::exception::error_code()`

  > The method returns an `int64_t` containing the error code

* `owm::exception::show_json()`

  > The method returns `std::string_view` containing json with error description

---

For example, let's write a small code where we will display the maximum temperature of the city of Kyiv
```cpp
#include <iostream>
#include "owm/weather.hpp"

int main(){
    owm::token token{"Your token", owm::units::metric, owm::lang::en};
    owm::weather<owm::current> weather{token};

    auto kyiv = weather.by<owm::wtag::city_name>("Kyiv");

    try{
        std::cout << kyiv.temp_max() << std::endl;
    } catch(owm::exception& exc){
        std::cerr << exc.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
```
**Everything is simple :)**