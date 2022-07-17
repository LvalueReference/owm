#pragma once

#include <string>
#include <string_view>
#include <type_traits>
#include <concepts>

#define URL "https://api.openweathermap.org/data/3.0/onecall?exclude="

namespace owm{
    template <class T>
    concept WeatherResponseConcept = requires{
        T::target_url;
    } && std::constructible_from<std::string, decltype(T::target_url)>;
    
    template <WeatherResponseConcept Response>
    std::string make_url(){
        return std::string{Response::target_url};
    }
}

#undef URL