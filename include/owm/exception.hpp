#pragma once

#include <string_view>
#include <string>

#include "simdjson.h"

namespace owm{
    class exception: public std::exception{
    private:
        simdjson::dom::element _json;
        simdjson::dom::parser _parser;
        std::string _response;
        std::string _message;
        int64_t _code;
    public:
        explicit exception(std::string) noexcept;
    public:
        const char* what() const noexcept override;
        static bool is_error_code(const std::string&);
        std::string_view show_json() const noexcept;
        std::string_view error_message() const noexcept;
        int64_t error_code() const noexcept;
    };
}