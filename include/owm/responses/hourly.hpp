#pragma once

#include "base_response.hpp"

namespace owm{
    struct hourly : public owm::base_response{
        explicit hourly(std::string) noexcept;

        static constexpr std::string_view target_url = "https://pro.openweathermap.org/data/2.5/forecast/hourly?";
    };
}