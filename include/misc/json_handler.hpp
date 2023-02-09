#pragma once

#include "simdjson.h"

#include <string>
#include <string_view>

namespace owm{
    class json_handler{
    private:
        simdjson::dom::parser m_parser;
        simdjson::dom::element m_json;
        std::string m_json_str;
    public:
        json_handler(std::string);
    public:
        simdjson::dom::element operator[](std::string_view) const;
    };
}