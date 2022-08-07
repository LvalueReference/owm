#include "owm/exception.hpp"
#include "simdjson/dom/element.h"
#include "magic_enum.hpp"

#include <charconv>
#include <array>

int64_t code_to_int(auto json){
    int64_t res;

    if (json.is_string()){
        std::string_view svc = json.get_string();

        std::from_chars(svc.data(), svc.data() + svc.size(), res);
    } else{
        res = json.get_int64();
    }

    return res;
};

owm::exception::exception(std::string&& resp) noexcept
    : _response(std::move(resp))
{
    _json = _parser.parse(_response);
    _message = _json["message"];

    _code = code_to_int(_json["cod"]);
}

const char* owm::exception::what() const noexcept{
    static std::string res;
    res = "owm: " + std::to_string(_code) + ":" + _message;

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

    auto code = static_cast<error_codes>(code_to_int(json["cod"]));

    constexpr auto codes = magic_enum::enum_values<error_codes>();

    return std::find(codes.begin(), codes.end(), code) != std::end(codes);
}