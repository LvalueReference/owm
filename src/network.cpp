#include "owm/network/network.hpp"
#include "curlpp/Options.hpp"
#include "misc/params.hpp"

#include <sstream>

static std::string make_params(owm::params&& params){
    std::string result;
    result.reserve(1024);

    for (const auto& [key, value] : params){
        result += key;
        result += "=";
        result += value;
        result += "&";
    }

    return result;
}

void owm::network::request(std::string_view url, owm::params&& params){
    std::stringstream stream;

    _handle.setOpt(curlpp::Options::Url(std::string{url} + make_params(std::move(params))));
    _handle.setOpt(curlpp::Options::WriteStream(&stream));
    _handle.perform();

    _response = std::move(stream).str();
}

std::string owm::network::response() && noexcept{
    return std::move(_response);
}