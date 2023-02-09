#pragma once

#include "misc/json_handler.hpp"

#include <string>
#include <string_view>

#include <iostream>

namespace owm{
    class base_response{
    private:
        std::string m_json_str;
    public:
        explicit base_response(std::string str) noexcept;
    public:
        owm::json_handler fetch() const noexcept;
    };
}