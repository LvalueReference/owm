#pragma once

#include "simdjson.h"

#include <string_view>

namespace owm{
    class hourly{
    private:
        simdjson::dom::element _json;
        simdjson::dom::parser _parser;
    public:
        explicit hourly(const std::string&);
    public:
        double temp_max() const noexcept;
        //under development
    };
}