#include "owm/token.hpp"

#include "magic_enum.hpp"

using namespace magic_enum;

owm::token::token(std::string_view token, owm::units units, owm::lang lang) noexcept
    : appid(token)
{
    this->units = enum_name(units);
    this->lang = enum_name(lang);
}