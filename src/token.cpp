#include "owm/token.hpp"

#include "magic_enum.hpp"

using namespace magic_enum;

owm::token::token(std::string_view token, owm::units units, owm::lang lang) noexcept
    : _token(token), _lang(lang), _units(units){}

std::string owm::token::get_token() const noexcept{
    return _token;
}

std::string owm::token::get_lang() const noexcept{
    return std::string{enum_name(_lang)};
}

std::string owm::token::get_units() const noexcept{
    return std::string{enum_name(_units)};
}