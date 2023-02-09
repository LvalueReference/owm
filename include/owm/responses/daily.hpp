#pragma once

#include "owm/responses/base_response.hpp"

namespace owm{
    struct daily : public owm::base_response{
        explicit daily(std::string) noexcept;

        static constexpr std::string_view target_url = "api.openweathermap.org/data/2.5/forecast/daily?";
    };
}