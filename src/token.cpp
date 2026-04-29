#include "owm/token.hpp"
#include <magic_enum/magic_enum.hpp>
#include <variant>

using namespace magic_enum;

template <class Enum, class... VariantArgs>
static constexpr Enum get_arg(const std::variant<VariantArgs...>& v) noexcept{
    if constexpr (std::is_same_v<Enum, owm::lang>){
        return std::holds_alternative<owm::lang>(v) ? std::get<owm::lang>(v) : owm::lang::en;
    } else{
        return std::holds_alternative<owm::units>(v) ? std::get<owm::units>(v) : owm::units::standard;
    }
}

owm::token::token(std::string_view key, units units, lang lang) noexcept
    : appid_{key}
    , units_{enum_name(units)}
    , lang_{enum_name(lang)}
{}

owm::token::token(std::string_view key, std::variant<units, lang> data) noexcept
    : appid_{key}
    , units_{enum_name(get_arg<units>(data))}
    , lang_{enum_name(get_arg<lang>(data))}
{}