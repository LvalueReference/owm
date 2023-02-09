#pragma once

#include <string_view>
#include <string>

namespace owm{
    class exception: public std::exception{
    private:
        std::string m_response;
        std::string m_message;
        mutable std::string m_what;
        int64_t m_code;
    public:
        explicit exception(std::string&&) noexcept;
    public:
        const char* what() const noexcept override;
        static bool is_error_code(const std::string&);
        std::string_view error_message() const noexcept;
        int64_t error_code() const noexcept;
    };
}