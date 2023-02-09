#include "owm/token.hpp"
#include "magic_enum.hpp"
#include <variant>
#include <optional>

using namespace magic_enum;

template <class Enum, class... VariantArgs>
static constexpr Enum get_arg(const std::variant<VariantArgs...>& v) noexcept{
    if constexpr (std::is_same_v<Enum, owm::lang>){
        return std::holds_alternative<owm::lang>(v) ? std::get<owm::lang>(v) : owm::lang::en;
    } else{
        return std::holds_alternative<owm::units>(v) ? std::get<owm::units>(v) : owm::units::standard;
    }
}

owm::token::token(std::string_view key, owm::units units, owm::lang lang) noexcept
    : m_appid{key},
      m_units{magic_enum::enum_name(units)},
      m_lang{magic_enum::enum_name(lang)}
{}

owm::token::token(std::string_view key, std::variant<owm::units, owm::lang> data) noexcept
    : m_appid{key},
      m_units{magic_enum::enum_name(get_arg<owm::units>(data))},
      m_lang{magic_enum::enum_name(get_arg<owm::lang>(data))}
{}