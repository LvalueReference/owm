#include "owm/token.hpp"
#include "owm/weather.hpp"
#include "fmt/format.h"

#include <iostream>

int main(int argc, char** argv){
    owm::token token{"API key", owm::units::metric, owm::lang::en};
    owm::weather<owm::hourly> forecast{token};

    if (argc != 2){
        std::cerr << "Using ./example <city_name>" << std::endl;
        return EXIT_FAILURE;
    }

    try{
        auto json = forecast.by<owm::city_name>(std::string{argv[1]}).fetch();

        std::cout << "Weather for: " << argv[1] << std::endl;

        for (auto list : json["list"].get_array()){
            std::string_view dt_txt = list["dt_txt"];
            double temp = list["main"]["temp"];
            double feels_like = list["main"]["feels_like"];
            double temp_min = list["main"]["temp_min"];
            double temp_max = list["main"]["temp_max"];
            std::string_view main = list["weather"].at(0)["main"];
            std::string_view description = list["weather"].at(0)["description"];
            double wind_speed = list["wind"]["speed"];

            fmt::print("\nDate: {}\n", dt_txt);
            fmt::print("Temperature: {}°C (min: {}°C / max: {}°C)\n", temp, temp_min, temp_max);
            fmt::print("Feels like: {}°C\n", feels_like);
            fmt::print("Weather: {} ({})\n", main, description);
            fmt::print("Wind speed: {} mps\n", wind_speed);
        }
    } catch(const std::exception& exc){
        std::cerr << exc.what() << std::endl;
    }

    return EXIT_SUCCESS;
}