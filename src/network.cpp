#include "owm/network/network.hpp"
#include "curlpp/Options.hpp"
#include "curlpp/cURLpp.hpp"
#include "misc/params.hpp"

#include <sstream>
#include <numeric>

void owm::network::request(const std::string& url, owm::params&& params){
    std::stringstream stream;
    
    std::string out;
    out.reserve(params.size());

    for (const auto& [key, value] : params){
        out += key;
        out += "=";
        out += curlpp::escape(value);
        out += "&";
    }

    m_handle.setOpt(curlpp::Options::Url(url + out));
    m_handle.setOpt(curlpp::Options::WriteStream(&stream));
    m_handle.perform();

    m_response = std::move(stream).str();
}

std::string&& owm::network::response() && noexcept{
    return std::move(m_response);
}