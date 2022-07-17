#pragma once

#include "responses/current_weather_response.hpp"
#include "responses/hourly_forecast_response.hpp"

namespace owm{
    using current = owm::current_weather_response;
    using hourly = owm::hourly_forecast_response;
}