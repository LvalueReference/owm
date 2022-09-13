#pragma once

#include "simdjson.h"

#include <string_view>

namespace owm{
    class current{
    private:
        simdjson::dom::element _json;
        simdjson::dom::parser _parser;
    public:
        explicit current(const std::string&) noexcept;
    public:
        static constexpr std::string_view target_url = "https://api.openweathermap.org/data/2.5/weather?";

        double lon() const noexcept;
        double lat() const noexcept;
        int64_t weather_id() const noexcept;
        std::string_view main() const noexcept;
        std::string_view description() const noexcept;
        std::string_view icon() const noexcept;
        std::string_view base() const noexcept;
        double temp() const noexcept;
        double feels_like() const noexcept;
        double temp_min() const noexcept;
        double temp_max() const noexcept;
        int64_t pressure() const noexcept;
        int64_t humidity() const noexcept;
        int64_t visibility() const noexcept;
        double wind_speed() const noexcept;
        int64_t wind_deg() const noexcept;
        int64_t clouds_all() const noexcept;
        int64_t dt() const noexcept;
        int64_t sys_type() const noexcept;
        int64_t sys_id() const noexcept;
        std::string_view sys_country() const noexcept;
        int64_t sys_sunrise() const noexcept;
        int64_t sys_sunset() const noexcept;
        int64_t timezone() const noexcept;
        int64_t id() const noexcept;
        std::string_view name() const noexcept;
        int64_t cod() const noexcept;
    };
}