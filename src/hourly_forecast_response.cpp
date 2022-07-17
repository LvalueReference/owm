#include "owm/responses/hourly_forecast_response.hpp"

#include <iostream>

owm::hourly_forecast_response::hourly_forecast_response(const std::string& json_string){
    _json = _parser.parse(json_string);
    std::cout << _json << std::endl;
}

double owm::hourly_forecast_response::temp_max() const noexcept{
    return _json["list"].at(0)["main"]["temp_max"];
}