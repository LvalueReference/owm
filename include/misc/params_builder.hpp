#pragma once

#include "params.hpp"
#include "owm/response.hpp"

#include <string>

namespace owm{
    enum class wtag{city_name, city_id, geo_coords};

    template <wtag Type>
    struct params{};

    template<>
    struct params<wtag::city_name>{
        template <class... Args>
        static params_t create(Args&&...);
    };

    template<>
    struct params<wtag::city_id>{
        template <class... Args>
        static params_t create(Args&&...);
    };

    template<>
    struct params<wtag::geo_coords>{
        template <class... Args>
        static params_t create(Args&&...);
    };
}

template<class... Args>
owm::params_t owm::params<owm::wtag::city_name>::create(Args&&... args){
    return [](std::string_view city) -> owm::params_t{
        return {{"q", std::string{city}}};
    }(std::forward<Args>(args)...);
}

template<class... Args>
owm::params_t owm::params<owm::wtag::city_id>::create(Args&&... args){
    return [](int32_t id) -> owm::params_t{
        return {{"q", std::to_string(id)}};
    }(std::forward<Args>(args)...);
}

template<class... Args>
owm::params_t owm::params<owm::wtag::geo_coords>::create(Args&&... args){
    return [](double lat, double lon) -> owm::params_t{
        return {{"lat", std::to_string(lat)},
                {"lon", std::to_string(lon)}};
    }(std::forward<Args>(args)...);
}