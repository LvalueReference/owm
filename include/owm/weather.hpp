#pragma once

#include "misc/params_builder.hpp"
#include "misc/url_builder.hpp"
#include "network/network.hpp"
#include "owm/responses/daily.hpp"
#include "responses.hpp"
#include "token.hpp"
#include "exception.hpp"

#include <utility>

namespace owm{
    namespace concepts {
        template <class T>
        concept ResponseConcept = std::same_as<T, current> ||
                                  std::same_as<T, hourly> ||
                                  std::same_as<T, daily>;
    }

    template <concepts::ResponseConcept Response>
    class weather{
    public:
        explicit weather(token) noexcept;

        template <wtag Type, class... Args>
        [[nodiscard]] Response by(Args&&...) const;
    private:
        token token_;

        [[nodiscard]] misc::params_t&& append(misc::params_t&&) const noexcept;
    };
}

template <owm::concepts::ResponseConcept Response>
owm::weather<Response>::weather(token tok) noexcept
    : token_(tok){}

template <owm::concepts::ResponseConcept Response>
template <owm::wtag Type, class... Args>
Response owm::weather<Response>::by(Args&&... args) const{
    network network;
    auto params = params_builder<Response, Type>::create(std::forward<Args>(args)...);

    network.request(owm::make_url<Response>(), append(std::move(params)));

    auto response = std::move(network).response();

    if(exception::is_error_code(response))
        throw exception{std::move(response)};

    return Response{std::move(response)};
}

template <owm::concepts::ResponseConcept Response>
owm::misc::params_t&& owm::weather<Response>::append(misc::params_t&& params) const noexcept{
    params.emplace_back("appid", token_.appid_);
    params.emplace_back("lang",  token_.lang_);
    params.emplace_back("units", token_.units_);

    return std::move(params);
}