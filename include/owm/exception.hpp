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
        exception(std::string&&) noexcept;
    public:
        enum class codes: int64_t{
            bad_api_key = 401,
            bad_api_request = 404,
            limit_error = 429,
            server_error1 = 500,
            server_error2 = 502,
            server_error3 = 503,
            server_error4 = 504
        };
    public:
        const char* what() const noexcept override;
        static bool is_error_code(const std::string&);
        std::string_view show_json() const noexcept;
        std::string_view error_message() const noexcept;
        int64_t error_code() const noexcept;
    };
}