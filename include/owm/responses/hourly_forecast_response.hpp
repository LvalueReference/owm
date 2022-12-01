#pragma once

#include "simdjson.h"
#include "hourly_forecast_list.hpp"

#include <string_view>
#include <vector>

namespace owm{
    class hourly{
    private:
        simdjson::dom::element _json;
        simdjson::dom::parser _parser;
    public:
        explicit hourly(const std::string&);
    public:
        static constexpr std::string_view target_url = "https://pro.openweathermap.org/data/2.5/forecast/hourly?";

        std::vector<hourly_list> list() const noexcept;
        int64_t city_id() const noexcept;
        std::string_view city_name() const noexcept;
        double lat() const noexcept;
        double lon() const noexcept;
        std::string_view country() const noexcept;
        int64_t population() const noexcept;
        int64_t timezone() const noexcept;
        int64_t sunrise() const noexcept;
        int64_t sunset() const noexcept;
        int64_t cod() const noexcept;
        int64_t message() const noexcept;
        int64_t cnt() const noexcept;

    };
}