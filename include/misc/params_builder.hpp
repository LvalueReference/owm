#pragma once

#include "owm/responses/daily.hpp"
#include "params.hpp"
#include "owm/responses.hpp"

#include <string>
#include <tuple>

namespace owm{
    enum wtag{city_name, city_id, geo_coords};

    template <class Response, wtag Type>
    struct params_builder;

    template<class Response>
    struct params_builder<Response, city_name>{
        template <class... Args>
        static misc::params_t create(Args&&...) noexcept;
    };

    template<class Response>
    struct params_builder<Response, city_id>{
        template <class... Args>
        static misc::params_t create(Args&&...) noexcept;
    };

    template<class Response>
    struct params_builder<Response, geo_coords>{
        template <class... Args>
        static misc::params_t create(Args&&...) noexcept;
    };
}

template <class Response>
template <class... Args>
owm::misc::params_t owm::params_builder<Response, owm::wtag::city_name>::create(Args&&... args) noexcept{
    constexpr size_t pack_size = sizeof...(Args);

    misc::params_t result;
    result.reserve(pack_size * 4);

    auto pack = std::make_tuple(std::forward<Args>(args)...);

    result.emplace_back("q", std::get<0>(pack));

    if constexpr (
        (std::is_same_v<Response, daily> or
        std::is_same_v<Response, hourly>)
        and pack_size == 2
        )
    {
        int32_t cnt = std::get<1>(pack);

        result.emplace_back("cnt", std::to_string(cnt));
    }

    return result;
}

template <class Response>
template <class... Args>
owm::misc::params_t owm::params_builder<Response, owm::wtag::city_id>::create(Args&&... args) noexcept{
    constexpr size_t pack_size = sizeof...(Args);

    misc::params_t result;
    result.reserve(pack_size * 4);

    auto pack = std::make_tuple(std::forward<Args>(args)...);

    result.emplace_back("id", std::to_string(std::get<0>(pack)));

    if constexpr ((std::is_same_v<Response, daily> or std::is_same_v<Response, hourly>) and pack_size == 2){
        int32_t cnt = std::get<1>(pack);

        result.emplace_back("cnt", std::to_string(cnt));
    }

    return result;
}

template <class Response>
template <class... Args>
owm::misc::params_t owm::params_builder<Response, owm::wtag::geo_coords>::create(Args&&... args) noexcept{
    constexpr size_t pack_size = sizeof...(Args);

    misc::params_t result;
    result.reserve(pack_size * 4);

    auto pack = std::make_tuple(std::forward<Args>(args)...);

    result.emplace_back("lat", std::to_string(std::get<0>(pack)));
    result.emplace_back("lon", std::to_string(std::get<1>(pack)));

    if constexpr ((std::is_same_v<Response, daily> or std::is_same_v<Response, hourly>) and pack_size == 3){
        int32_t cnt = std::get<2>(pack);

        result.emplace_back("cnt", std::to_string(cnt));
    }

    return result;
}