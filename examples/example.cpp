#include "owm/weather.hpp"

#include <print>

int main(int argc, char** argv){
    owm::token token{"TOKEN", owm::units::metric, owm::lang::en};
    owm::weather<owm::current> forecast{token};

    if (argc != 2){
        std::cerr << "Using ./example <city_name>" << std::endl;
        return EXIT_FAILURE;
    }

    try{
        auto unwrapped = forecast.by<owm::city_name>(std::string{argv[1]}).fetch();

        auto coord = unwrapped["coord"];
        auto weather = unwrapped["weather"][0];
        auto main = unwrapped["main"];
        auto wind = unwrapped["wind"];
        auto sys = unwrapped["sys"];
        std::string city_name = unwrapped["name"];

        auto [lon, lat] = std::make_pair(*coord["lon"].get_double(), *coord["lat"].get_double());
        std::string weather_main = weather["main"];
        std::string description = weather["description"];
        int64_t temp = static_cast<int64_t>(*main["temp"].get_double());
        int64_t temp_min = static_cast<int64_t>(*main["temp_min"].get_double());
        int64_t temp_max = static_cast<int64_t>(*main["temp_max"].get_double());
        double wind_speed = wind["speed"];
        std::string country = sys["country"];

        // Easy print
        std::print("Weather for {}, {} (lon: {}, lat: {})", city_name, country, lon, lat);
        std::print("==== [{} | {}] ====", weather_main, description);
        std::print("Temperature: {}°C (min: {}°C, max: {}°C)", temp, temp_min, temp_max);
        std::print("Wind speed: {}m/s", wind_speed);
    } catch(const owm::exception& exc){
        std::cerr << "[OWM:error] - " << exc.what() << std::endl;
    }

    return EXIT_SUCCESS;
}