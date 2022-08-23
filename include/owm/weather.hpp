#pragma once

#include "misc/params.hpp"
#include "misc/params_builder.hpp"
#include "misc/url_builder.hpp"
#include "response.hpp"
#include "network/network.hpp"
#include "token.hpp"
#include "exception.hpp"

#include <string_view>

namespace owm{
    template <class T>
    concept ResponseConcept = std::same_as<T, owm::current> ||
                              std::same_as<T, owm::hourly>;

    template <ResponseConcept Response>
    class weather{
    private:
        token _data;
    public:
        weather(token) noexcept;
    public:
        template <wtag Type, class... Args>
        Response by(Args&&...);
    private:
        [[nodiscard]] params&& append(params&&) const noexcept;
    };
}

template <owm::ResponseConcept Response>
owm::weather<Response>::weather(owm::token token) noexcept
    : _data(token){}

template <owm::ResponseConcept Response>
template <owm::wtag Type, class... Args>
Response owm::weather<Response>::by(Args&&... args) const noexcept{
    owm::network _nclient;
    
    _nclient.request(owm::make_url<Response>(), 
                     append(owm::params_builder<Type>::create(std::forward<Args>(args)...)));

    auto resp = std::move(_nclient).response();

    if(exception::is_error_code(resp))
        throw exception{std::move(resp)};

    return Response{std::move(resp)};
}

template <owm::ResponseConcept Response>
owm::params&& owm::weather<Response>::append(owm::params&& params) const noexcept{
    params.emplace_back("appid", _data.appid);
    params.emplace_back("lang",  _data.lang);
    params.emplace_back("units", _data.units);

    return std::move(params);
}
