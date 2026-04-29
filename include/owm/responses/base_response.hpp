#pragma once

#include "unwrapped.hpp"

#include <string>

namespace owm{
    class base_response{
    public:
        explicit base_response(std::string str) noexcept;

        [[nodiscard]]
        unwrapped fetch() const noexcept;
        [[nodiscard]]
        std::string fetch_json_str() const noexcept;
    private:
        std::string json_str_;
    };
}