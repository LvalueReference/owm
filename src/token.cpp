#include "owm/token.hpp"
#include "magic_enum.hpp"

using namespace magic_enum;

owm::token::token(std::string_view key) noexcept
    : _appid{key},
      _units{enum_name(owm::units::standard)},
      _lang{enum_name(owm::lang::en)}
{}

owm::token::token(std::string_view key, owm::units units, owm::lang lang) noexcept
    : _appid{key},
      _units{enum_name(units)},
      _lang{enum_name(lang)}
{}

owm::token::token(std::string_view key, owm::lang lang, owm::units units) noexcept
    : _appid{key},
      _lang{enum_name(lang)},
      _units{enum_name(units)}
{}