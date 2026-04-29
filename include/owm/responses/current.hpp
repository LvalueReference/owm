#pragma once

#include "base_response.hpp"

namespace owm{
    struct current : base_response{
        explicit current(std::string) noexcept;

        static constexpr std::string_view target_url = "api.openweathermap.org/data/2.5/weather";
    };
}