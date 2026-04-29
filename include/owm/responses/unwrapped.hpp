#pragma once

#include "unwrapped_result.hpp"

#include <cstddef>
#include <stdexcept>
#include <string>
#include <optional>
#include <type_traits>
#include <unordered_map>
#include <variant>
#include <vector>
#include <owm/exception.hpp>

#include <simdjson.h>

namespace owm {
    namespace concepts {
        template <typename T, typename Variant>
        concept OneOfVariant = requires(Variant v){
            requires requires
            {
                std::holds_alternative<T>(v);
            };

            []<typename... Types>(std::variant<Types...>&) consteval requires (std::is_same_v<T, Types> || ...){}(v);
        };
    }

    class unwrapped;

    namespace misc {
        using object_t = std::unordered_map<std::string, unwrapped>;
        using array_t  = std::vector<unwrapped>;
    }

    class unwrapped {
    public:
        using value_t = std::variant<
            std::nullptr_t,
            std::string,
            int64_t,
            double,
            bool,
            misc::object_t,
            misc::array_t
        >;

        unwrapped(value_t value);
        unwrapped(const std::string& json_str);

        unwrapped operator[](std::string_view) const;
        unwrapped operator[](size_t) const;

        template <typename T>
        std::optional<T> get() const {
            return static_cast<T>(std::get<T>(value_));
        }

        std::optional<misc::array_t> get_array() const;
        std::optional<misc::object_t> get_object() const;
        std::optional<std::string> get_string() const;
        std::optional<int64_t> get_int64_t() const;
        std::optional<double> get_double() const;
        std::optional<bool> get_bool() const;

        template <typename T>
        constexpr operator T() &&{
            using U = std::decay_t<T>;

            if constexpr (std::is_same_v<U, std::string>){
                if (auto v = std::get_if<std::string>(&value_))
                    return std::move(*v);

                throw owm::exception{"owm: Bad cast"};
            } 
            
            else if constexpr (std::is_arithmetic_v<U>){
                if (auto v = std::get_if<U>(&value_))
                    return *v;

                if constexpr (std::is_floating_point_v<U>){
                    if (auto v = std::get_if<int64_t>(&value_))
                        return static_cast<U>(*v);
                }

                if constexpr (std::is_integral_v<U>) {
                    if (auto v = std::get_if<double>(&value_))
                        return static_cast<U>(*v);
                }

                throw owm::exception{"owm: bad numeric cast"};
            }

            else if constexpr (std::is_same_v<U, bool>){
                if (auto v = std::get_if<bool>(&value_))
                    return *v;

                throw owm::exception{"owm: bad cast to bool"};
            }
        }
    private:
        value_t value_;

        static value_t parse_element_(const simdjson::dom::element& json);
        static misc::object_t parse_object_(const simdjson::dom::object& obj);
        static misc::array_t parse_array_(const simdjson::dom::array& arr);
    };
}
