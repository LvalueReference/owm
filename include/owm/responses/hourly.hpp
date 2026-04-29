#pragma once

#include "base_response.hpp"

namespace owm{
    struct hourly : base_response{
        explicit hourly(std::string) noexcept;

        static constexpr std::string_view target_url = "pro.openweathermap.org/data/2.5/forecast/hourly";
    };
}