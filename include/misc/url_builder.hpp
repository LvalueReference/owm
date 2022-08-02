#pragma once

#include <string>
#include <type_traits>
#include <concepts>

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