#include "owm/responses/hourly_forecast_list.hpp"

using list = owm::hourly_list;

list::hourly_list(simdjson::dom::element json) noexcept{
    _json = json;
}

int64_t list::dt() const noexcept{
    return _json["dt"];
}

double list::temp() const noexcept{
    return _json["main"]["temp"];
}

double list::feels_like() const noexcept{
    return _json["main"]["feels_like"];
}

double list::temp_min() const noexcept{
    return _json["main"]["temp_min"];
}

double list::temp_max() const noexcept{
    return _json["main"]["temp_max"];
}

int64_t list::pressure() const noexcept{
    return _json["main"]["pressure"];
}

int64_t list::sea_level() const noexcept{
    return _json["main"]["sea_level"];
}

int64_t list::grnd_level() const noexcept{
    return _json["main"]["grnd_level"];
}

int64_t list::humidity() const noexcept{
    return _json["main"]["humidity"];
}

int64_t list::temp_kf() const noexcept{
    return _json["main"]["temp_kf"];
}

int64_t list::id() const noexcept{
    return _json["weather"].at(0)["id"];
}

std::string_view list::main() const noexcept{
    return _json["weather"].at(0)["main"];
}

std::string_view list::description() const noexcept{
    return _json["weather"].at(0)["description"];
}

std::string_view list::icon() const noexcept{
    return _json["weather"].at(0)["icon"];
}

int64_t list::clouds_all() const noexcept{
    return _json["clouds"]["all"];
}

double list::wind_speed() const noexcept{
    return _json["wind"]["speed"];
}

int64_t list::wind_deg() const noexcept{
    return _json["wind"]["deg"];
}

double list::wind_gust() const noexcept{
    return _json["wind"]["gust"];
}

int64_t list::visibility() const noexcept{
    return _json["visibility"];
}

int64_t list::pop() const noexcept{
    return _json["pop"];
}

std::string_view list::sys_pod() const noexcept{
    return _json["sys"]["pod"];
}

std::string_view list::dt_txt() const noexcept{
    return _json["dt_txt"];
}