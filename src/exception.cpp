#include "owm/exception.hpp"
#include "simdjson/dom/element.h"
#include "magic_enum.hpp"

#include <charconv>
#include <sstream>
#include <array>

inline int64_t code_to_int(auto json) noexcept{
    int64_t res;

    if (json.is_string()){
        std::string_view svc = json.get_string();

        std::from_chars(svc.data(), svc.data() + svc.size(), res);
    } else{
        res = json.get_int64();
    }

    return res;
}

owm::exception::exception(std::string&& resp) noexcept
    : _response(std::move(resp))
{
    _json = _parser.parse(_response);
    _message = _json["message"];
    _code = code_to_int(_json["cod"]);
}

const char* owm::exception::what() const noexcept{
    std::stringstream res;
    res << "owm: " << std::to_string(_code) << ":" << _message;

    _m_what = std::move(res).str();

    return _m_what.data();
}

[[maybe_unused]] 
std::string_view owm::exception::show_json() const noexcept{
    return _response;
}

[[maybe_unused]] 
std::string_view owm::exception::error_message() const noexcept{
    return _message;
}

int64_t owm::exception::error_code() const noexcept{
    return _code;
}

bool owm::exception::is_error_code(const std::string& resp){
    simdjson::dom::parser parser;
    simdjson::dom::element json = parser.parse(resp);

    int64_t code = code_to_int(json["cod"]);

    return code > 400;
}