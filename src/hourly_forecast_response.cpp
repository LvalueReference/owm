#include "owm/responses/hourly_forecast_response.hpp"

#include <iostream>

owm::hourly::hourly(const std::string& json_string){
    _json = _parser.parse(json_string);
    std::cout << _json << std::endl;
}

double owm::hourly::temp_max() const noexcept{
    return _json["list"].at(0)["main"]["temp_max"];
}