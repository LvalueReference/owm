#include "owm/responses/hourly_forecast_response.hpp"

#include <iostream>
#include <charconv>

owm::hourly::hourly(const std::string& json_string){
    _json = _parser.parse(json_string);
}

int64_t owm::hourly::cod() const noexcept{
    if (_json["cod"].is_string()){
        std::string_view cod = _json["cod"].get_string();
        int64_t res = 0;
        
        std::from_chars(cod.data(), cod.data() + cod.size(), res);

        return res;
    }

    return _json["cod"];
}

int64_t owm::hourly::message() const noexcept{
    return _json["message"];
}

int64_t owm::hourly::cnt() const noexcept{
    return _json["cnt"];
}

std::vector<owm::hourly_list> owm::hourly::list() const noexcept{
    std::vector<owm::hourly_list> result;

    auto get_list = [](auto json) -> simdjson::dom::array{
        return json["list"].get_array();
    };

    for (auto elem : get_list(_json)){
        result.push_back(owm::hourly_list{elem});
    }

    return result;
}

int64_t owm::hourly::city_id() const noexcept{
    return _json["city"]["id"];
}

std::string_view owm::hourly::city_name() const noexcept{
    return _json["city"]["name"];
}

double owm::hourly::lat() const noexcept{
    return _json["city"]["coord"]["lat"];
}

double owm::hourly::lon() const noexcept{
    return _json["city"]["coord"]["lon"];
}

std::string_view owm::hourly::country() const noexcept{
    return _json["city"]["country"];
}

int64_t owm::hourly::population() const noexcept{
    return _json["city"]["population"];
}

int64_t owm::hourly::timezone() const noexcept{
    return _json["city"]["timezone"];
}

int64_t owm::hourly::sunrise() const noexcept{
    return _json["city"]["sunrise"];
}

int64_t owm::hourly::sunset() const noexcept{
    return _json["city"]["sunset"];
}