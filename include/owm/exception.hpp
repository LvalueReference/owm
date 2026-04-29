#pragma once

#include <string_view>
#include <string>

namespace owm{
    class exception: public std::exception{
    public:
        explicit exception(std::string&&) noexcept;

        const char* what() const noexcept override;
        static bool is_error_code(const std::string&);
        std::string_view error_message() const noexcept;
        int64_t error_code() const noexcept;
    private:
        std::string response_;
        std::string message_;
        mutable std::string what_;
        int64_t code_;
    };
}