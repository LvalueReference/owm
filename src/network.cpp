#include "network/network.hpp"

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;
namespace ssl = asio::ssl;
using tcp = asio::ip::tcp;

owm::network::network()
    : ssl_ctx_(ssl::context::tls_client)
    , resolver_(ctx_)
    , stream_(ctx_, ssl_ctx_)
{
    ssl_ctx_.set_default_verify_paths();
}

owm::network::~network() noexcept {
    beast::error_code err;
    stream_.shutdown(err);
}

void owm::network::request(std::string_view url, misc::params_t&& params) {
    auto [host, target] = split_url_(url.data());

    std::string final_target = [](std::string&& target, misc::params_t&& params) -> std::string {
        std::string result;
        result.reserve(params.size() * 4);

        result = target + '?';

        for (const auto& [key, value] : params) {
            result.append(key);
            result.append("=");
            result.append(value);
            result.append("&");
        }

        result.pop_back();

        return result;
    }(std::move(target), std::move(params));

    auto resolved = resolver_.resolve(host, "443");
    beast::get_lowest_layer(stream_).connect(resolved);
    stream_.handshake(ssl::stream_base::client);

    http::request<http::string_body> req{http::verb::get, final_target, 11};
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    req.keep_alive(true);

    http::write(stream_, req);

    beast::flat_buffer buffer;
    http::response<http::string_body> response;

    http::read(stream_, buffer, response);

    response_ = std::move(response).body();
}

std::string&& owm::network::response() && noexcept {
    return std::move(response_);
}

std::string owm::network::response() const noexcept {
    return response_;
}

inline std::pair<std::string, std::string> owm::network::split_url_(const std::string& url) noexcept {
    auto slash = url.find('/');

    auto host = url.substr(0, slash);
    auto target = std::string{
        slash == std::string::npos ? "/" : url.substr(slash)
    };

    return {host, target};
}