#pragma once

#include "simdjson.h"

#include <string>
#include <string_view>

namespace owm{
    class hourly_list{
    private:
        simdjson::dom::element _json;
    public:
        explicit hourly_list(simdjson::dom::element json) noexcept;
    public:
        int64_t dt() const noexcept;
        double temp() const noexcept;
        double feels_like() const noexcept;
        double temp_min() const noexcept;
        double temp_max() const noexcept;
        int64_t pressure() const noexcept;
        int64_t sea_level() const noexcept;
        int64_t grnd_level() const noexcept;
        int64_t humidity() const noexcept;
        int64_t temp_kf() const noexcept;
        int64_t id() const noexcept;
        std::string_view main() const noexcept;
        std::string_view description() const noexcept;
        std::string_view icon() const noexcept;
        int64_t clouds_all() const noexcept;
        double wind_speed() const noexcept;
        int64_t wind_deg() const noexcept;
        double wind_gust() const noexcept;
        int64_t visibility() const noexcept;
        int64_t pop() const noexcept;
        std::string_view sys_pod() const noexcept;
        std::string_view dt_txt() const noexcept;
    };
}