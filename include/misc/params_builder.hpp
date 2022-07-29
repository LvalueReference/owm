#pragma once

#include "params.hpp"

#include <string>

namespace owm{
    enum class wtag{city_name, city_id, geo_coords};

    template <wtag Type>
    struct params_builder{};

    template<>
    struct params_builder<wtag::city_name>{
        template <class... Args>
        static params create(Args&&...);
    };

    template<>
    struct params_builder<wtag::city_id>{
        template <class... Args>
        static params create(Args&&...);
    };

    template<>
    struct params_builder<wtag::geo_coords>{
        template <class... Args>
        static params create(Args&&...);
    };
}

template<class... Args>
owm::params owm::params_builder<owm::wtag::city_name>::create(Args&&... args){
    return [](std::string_view city) -> owm::params{
        return {{"q", std::string{city}}};
    }(std::forward<Args>(args)...);
}

template<class... Args>
owm::params owm::params_builder<owm::wtag::city_id>::create(Args&&... args){
    return [](int32_t id) -> owm::params{
        return {{"q", std::to_string(id)}};
    }(std::forward<Args>(args)...);
}

template<class... Args>
owm::params owm::params_builder<owm::wtag::geo_coords>::create(Args&&... args){
    return [](double lat, double lon) -> owm::params{
        return {{"lat", std::to_string(lat)},
                {"lon", std::to_string(lon)}};
    }(std::forward<Args>(args)...);
}