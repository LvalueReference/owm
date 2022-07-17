#include "owm/exception.hpp"
#include "simdjson/dom/element.h"
#include "magic_enum.hpp"

#include <charconv>
#include <cstdint>
#include <iostream>
#include <string>

owm::exception::exception(std::string resp) noexcept
    : _response(std::move(resp))
{
    _json = _parser.parse(_response);
    _message = _json["message"];
    
    auto code_to_int = [](auto json) -> int64_t{
        int64_t res;

        if (json.is_string()){
        auto svc = json.get_string().value();

        std::from_chars(svc.data(), svc.data() + svc.size(), res);
        } else{
            res = json.get_int64();
        }

        return res;
    };

    _code = code_to_int(_json["cod"]);
}

const char* owm::exception::what() const noexcept{
    using namespace std::string_literals;

    static std::string res;
    res = std::to_string(_code) + ":" += _message;

    return res.c_str();
}

std::string_view owm::exception::show_json() const noexcept{
    return _response;
}

std::string_view owm::exception::error_message() const noexcept{
    return _message;
}

int64_t owm::exception::error_code() const noexcept{
    return _code;
}

bool owm::exception::is_error_code(const std::string& resp){
    simdjson::dom::parser parser;
    simdjson::dom::element json = parser.parse(resp);

    return json["cod"].is_string();
}