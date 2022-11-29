#include "owm/network/network.hpp"
#include "curlpp/Options.hpp"
#include "misc/params.hpp"

#include <sstream>
#include <numeric>

void owm::network::request(const std::string& url, owm::params&& params){
    using namespace std::string_literals;

    std::stringstream stream;

    auto make_params = [](owm::params&& params){
        return std::accumulate(params.begin(), params.end(), ""s, [](std::string out, const auto& pair){
            out += pair.first;
            out += "="s;
            out += pair.second;
            out += "&"s;

            return out;
        });
    };

    _handle.setOpt(curlpp::Options::Url(url + make_params(std::move(params))));
    _handle.setOpt(curlpp::Options::WriteStream(&stream));
    _handle.perform();

    _response = std::move(stream).str();
}

std::string&& owm::network::response() && noexcept{
    return std::move(_response);
}