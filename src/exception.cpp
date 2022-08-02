#include "owm/exception.hpp"
#include "simdjson/dom/element.h"
#include "magic_enum.hpp"

#include <charconv>
#include <ranges>

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

    static constexpr error_codes codes[] = {
        error_codes::bad_api_key,
        error_codes::bad_api_request,
        error_codes::limit_error,
        error_codes::server_error1,
        error_codes::server_error2,
        error_codes::server_error3,
        error_codes::server_error4
    };

    return std::ranges::find(codes, static_cast<error_codes>(code_to_int(json["cod"]))) 
           != std::end(codes);
}