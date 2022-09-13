#include "owm/responses/current_weather_response.hpp"

#include <string>
#include <charconv>

using response = owm::current;

response::current(const std::string& json_string) noexcept{
    _json = _parser.parse(json_string);
}

double response::lon() const noexcept{
    return _json["coord"]["lon"];
}

double response::lat() const noexcept{
    return _json["coord"]["lat"];
}

int64_t response::weather_id() const noexcept{
    return _json["weather"].at(0)["id"];
}

std::string_view response::main() const noexcept{
    return _json["weather"].at(0)["main"];
}

std::string_view response::description() const noexcept{
    return _json["weather"].at(0)["description"];
}

std::string_view response::icon() const noexcept{
    return _json["weather"].at(0)["icon"];
}

std::string_view response::base() const noexcept{
    return _json["base"];
}

double response::temp() const noexcept{
    return _json["main"]["temp"];
}

double response::feels_like() const noexcept{
    return _json["main"]["feels_like"];
}

double response::temp_min() const noexcept{
    return _json["main"]["temp_min"];
}

double response::temp_max() const noexcept{
    return _json["main"]["temp_max"];
}

int64_t response::pressure() const noexcept{
    return _json["main"]["pressure"];
}

int64_t response::humidity() const noexcept{
    return _json["main"]["humidity"];
}

int64_t response::visibility() const noexcept{
    return _json["visibility"];
}

double response::wind_speed() const noexcept{
    return _json["wind"]["speed"];
}

int64_t response::wind_deg() const noexcept{
    return _json["wind"]["deg"];
}

int64_t response::clouds_all() const noexcept{
    return _json["clouds"]["all"];
}

int64_t response::dt() const noexcept{
    return _json["dt"];
}

int64_t response::sys_type() const noexcept{
    return _json["sys"]["type"];
}

int64_t response::sys_id() const noexcept{
    return _json["sys"]["id"];
}

std::string_view response::sys_country() const noexcept{
    return _json["sys"]["country"];
}

int64_t response::sys_sunrise() const noexcept{
    return _json["sys"]["sunrise"];
}

int64_t response::sys_sunset() const noexcept{
    return _json["sys"]["sunset"];
}

int64_t response::timezone() const noexcept{
    return _json["timezone"];
}

int64_t response::id() const noexcept{
    return _json["id"];
}

std::string_view response::name() const noexcept{
    return _json["name"];
}

int64_t response::cod() const noexcept{
    if (_json["cod"].is_string()){
        std::string_view cod = _json["cod"].get_string();
        int64_t res = 0;
        
        std::from_chars(cod.data(), cod.data() + cod.size(), res);

        return res;
    }

    return _json["cod"];
}