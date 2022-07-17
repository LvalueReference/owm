#pragma once

#include "misc/params.hpp"
#include "misc/params_builder.hpp"
#include "misc/url_builder.hpp"
#include "owm/response.hpp"
#include "owm/responses/current_weather_response.hpp"
#include "responses/hourly_forecast_response.hpp"
#include "network/network.hpp"
#include "token.hpp"
#include "exception.hpp"

#include <string_view>
#include <type_traits>

template <class T>
concept ResponseConcept = std::same_as<T, owm::current_weather_response> ||
                          std::same_as<T, owm::hourly_forecast_response>;

namespace owm{
    template <ResponseConcept Response>
    class weather{
    private:
        network _nclient;
        token _data;
    public:
        weather(token) noexcept;
    public:
        template <wtag Type, class... Args>
        Response by(Args&&...);
    private:
        [[nodiscard]] params_t&& append(params_t&&) const noexcept;
    };
}

template <ResponseConcept Response>
owm::weather<Response>::weather(owm::token token) noexcept
    : _data(token){}

template <ResponseConcept Response>
template<owm::wtag Type, class... Args>
Response owm::weather<Response>::by(Args&&... args){
    _nclient.request(owm::make_url<Response>(), 
                     append(owm::params<Type>::create(std::forward<Args>(args)...)));

    auto resp = _nclient.response();

    if(exception::is_error_code(resp))
        throw exception{resp};

    return Response{std::move(resp)};
}

template <ResponseConcept Response>
owm::params_t&& owm::weather<Response>::append(owm::params_t&& params) const noexcept{
    params.emplace_back("appid", _data.get_token());
    params.emplace_back("lang", _data.get_lang());
    params.emplace_back("units", _data.get_units());

    return std::move(params);
}