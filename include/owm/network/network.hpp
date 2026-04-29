#pragma once

#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/asio/ssl.hpp>

#include <string>
#include <string_view>

#include "misc/params.hpp"

namespace owm {
    class network {
    public:
        network();
        ~network() noexcept;

        void request(std::string_view url, misc::params_t&& params);

        [[nodiscard]]
        std::string&& response() && noexcept;

        [[nodiscard]]
        std::string response() const noexcept;
    private:
        boost::asio::io_context ctx_;
        boost::asio::ssl::context ssl_ctx_;
        boost::asio::ip::tcp::resolver resolver_;
        boost::beast::ssl_stream<boost::beast::tcp_stream> stream_;
        std::string response_;

        static inline std::pair<std::string, std::string> split_url_(const std::string& url) noexcept;
    };
}