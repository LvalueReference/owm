#include "owm/exception.hpp"
#include "simdjson.h"

#include <charconv>
#include <sstream>

static int64_t code_to_int(auto json) noexcept{
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
    : response_(std::move(resp))
{
    simdjson::dom::parser parser;
    simdjson::dom::element json = parser.parse(response_);

    message_ = json["message"];
    code_ = code_to_int(json["cod"]);
}

const char* owm::exception::what() const noexcept{
    std::stringstream res;
    res << "owm: " << std::to_string(code_) << ":" << message_;

    what_ = std::move(res).str();

    return what_.data();
}

std::string_view owm::exception::error_message() const noexcept{
    return message_;
}

int64_t owm::exception::error_code() const noexcept{
    return code_;
}

bool owm::exception::is_error_code(const std::string& resp){
    simdjson::dom::parser parser;
    simdjson::dom::element json = parser.parse(resp);

    int64_t code = code_to_int(json["cod"]);

    return code >= 400;
}