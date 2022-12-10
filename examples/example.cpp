#include "owm/weather.hpp"
#include "fmt/format.h"

#include <cstdlib>
#include <iostream>
#include <cmath>

std::ostream& operator<<(std::ostream& stream, const owm::hourly& w){
    stream << fmt::format("City: {}", w.city_name()) << std::endl;
    stream << fmt::format("Country: {}", w.country()) << std::endl;

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const owm::hourly_list& list){
    stream << "[" << list.dt_txt() << "]" << std::endl;
    stream << "Weather: " << list.main() << " (" << list.description() << ")" << std::endl;
    stream << "Temperature: " << std::round(list.temp()) << " (min: " << list.temp_min() << " | max: " << list.temp_max() << ")"
                                                                                           << std::endl;
    stream << "Wind speed: " << list.wind_speed() << " m/s";

    return stream;
}

auto forecast(const owm::hourly& hourly, int hours){
    std::vector<owm::hourly_list> result;

    for (int i = 0; i < hours; ++i){
        result.push_back(hourly.list().at(i));
    }

    return result;
}

int main(int argc, char** argv){
    owm::token token{"Your token", owm::units::metric, owm::lang::en};
    owm::weather<owm::hourly> weather{token};
    
    if (argc != 3){
        std::cerr << "Usage: ./example <City name> <hours>" << std::endl;

        return EXIT_FAILURE;
    }

    try{
        auto city = weather.by<owm::city_name>(std::string{argv[1]});

        std::cout << city << std::endl;
        std::cout << "Forecast for " << argv[2] << " hours:" << std::endl;

        for (const auto& elem : forecast(city, std::stoi(std::string{argv[2]}))){
            std::cout << elem << std::endl;
            std::cout << std::endl;
        }
    } catch(const owm::exception& exc){
        std::cerr << exc.what() << std::endl;
    }

    return EXIT_SUCCESS;
}