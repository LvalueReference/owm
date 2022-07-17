#pragma once

#include "simdjson.h"

#include <string_view>

namespace owm{
    class hourly_forecast_response{
    private:
        simdjson::dom::element _json;
        simdjson::dom::parser _parser;
    public:
        explicit hourly_forecast_response(const std::string&);
    public:
        double temp_max() const noexcept;
        //under development
    };
}