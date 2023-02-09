#pragma once

#include "misc/params_builder.hpp"
#include "misc/url_builder.hpp"
#include "network/network.hpp"
#include "owm/responses/daily.hpp"
#include "responses.hpp"
#include "token.hpp"
#include "exception.hpp"

#include <string_view>
#include <utility>

namespace owm{
    template <class T>
    concept ResponseConcept = std::same_as<T, owm::current> ||
                              std::same_as<T, owm::hourly> ||
                              std::same_as<T, owm::daily>;

    template <ResponseConcept Response>
    class weather{
    private:
        token m_token;
    public:
        explicit weather(token) noexcept;
    public:
        template <wtag Type, class... Args>
        [[nodiscard]] Response by(Args&&...) const;
    private:
        [[nodiscard]] params&& append(params&&) const noexcept;
    };
}

template <owm::ResponseConcept Response>
owm::weather<Response>::weather(owm::token token) noexcept
    : m_token(token){}

template <owm::ResponseConcept Response>
template <owm::wtag Type, class... Args>
Response owm::weather<Response>::by(Args&&... args) const{
    owm::network network;
    auto params = owm::params_builder<Response, Type>::create(std::forward<Args>(args)...);

    network.request(owm::make_url<Response>(), append(std::move(params)));

    auto response = std::move(network).response();

    if(owm::exception::is_error_code(response))
        throw owm::exception{std::move(response)};

    return Response{std::move(response)};
}

template <owm::ResponseConcept Response>
owm::params&& owm::weather<Response>::append(owm::params&& params) const noexcept{
    params.emplace_back("appid", m_token.m_appid);
    params.emplace_back("lang",  m_token.m_lang);
    params.emplace_back("units", m_token.m_units);

    return std::move(params);
}