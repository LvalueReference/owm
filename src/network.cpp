#include "owm/network/network.hpp"
#include "curlpp/Options.hpp"
#include "misc/params.hpp"

#include <sstream>
#include <numeric>

inline auto make_params(owm::params&& params){
    auto make = [](std::string out, const auto& pair){
        out += pair.first;
        out += "=";
        out += pair.second;
        out += "&";

        return out;
    };

    return std::accumulate(params.begin(), params.end(), std::string(), make);
}

void owm::network::request(std::string_view url, owm::params&& params){
    std::stringstream stream;

    _handle.setOpt(curlpp::Options::Url(std::string{url} + make_params(std::move(params))));
    _handle.setOpt(curlpp::Options::WriteStream(&stream));
    _handle.perform();

    _response = std::move(stream).str();
}

std::string&& owm::network::response() && noexcept{
    return std::move(_response);
}