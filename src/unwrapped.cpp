#include "owm/responses/unwrapped.hpp"

#include <format>

owm::unwrapped::unwrapped(value_t value)
    : value_(std::move(value))
{}

owm::unwrapped::unwrapped(const std::string &json_str) {
    simdjson::dom::parser parser;
    simdjson::dom::element doc = parser.parse(json_str);

    value_ = parse_element_(doc);
}

owm::unwrapped owm::unwrapped::operator[](std::string_view key) const {
    if (auto obj = std::get_if<misc::object_t>(&value_)) {
        auto it = obj->find(std::string{key});

        if (it != obj->end())
            return it->second;
    }

    if (auto arr = std::get_if<misc::array_t>(&value_)) {
        if (!arr->empty()) {
            return (*arr)[0][key];
        }

        throw std::out_of_range{std::format(
            "owm: Bad access to array {} with index {}!\nArray is empty!",
            key,
            0
        )};
    }
    return unwrapped{value_t{nullptr}};
}

owm::unwrapped owm::unwrapped::operator[](size_t index) const {
    if (auto arr = std::get_if<misc::array_t>(&value_)) {
        if (index < arr->size()) {
            return (*arr)[index];
        }

        throw std::out_of_range{std::format(
            "owm: Bad access to array with index {}!\nOut of range!",
            index
        )};
    }

    return unwrapped{value_t{nullptr}};
}

std::optional<owm::misc::array_t> owm::unwrapped::get_array() const {
    if (auto v = std::get_if<misc::array_t>(&value_))
        return *v;

    return std::nullopt;
}

std::optional<owm::misc::object_t> owm::unwrapped::get_object() const {
    if (auto v = std::get_if<misc::object_t>(&value_))
        return *v;

    return std::nullopt;
}

std::optional<std::string> owm::unwrapped::get_string() const {
    if (auto v = std::get_if<std::string>(&value_))
        return *v;

    return std::nullopt;
}

std::optional<int64_t> owm::unwrapped::get_int64_t() const {
    if (auto v = std::get_if<int64_t>(&value_))
        return *v;

    return std::nullopt;
}

std::optional<double> owm::unwrapped::get_double() const {
    if (auto v = std::get_if<double>(&value_))
        return *v;

    return std::nullopt;
}

std::optional<bool> owm::unwrapped::get_bool() const {
    if (auto v = std::get_if<bool>(&value_))
        return *v;

    return std::nullopt;
}

owm::unwrapped::value_t owm::unwrapped::parse_element_(const simdjson::dom::element &json) {
    using simdjson::dom::element_type;

    switch (json.type()) {
        case element_type::ARRAY:
            return parse_array_(json);
        case element_type::OBJECT:
            return parse_object_(json);
        case element_type::INT64:
            return json.get_int64();
        case element_type::DOUBLE:
            return json.get_double();
        case element_type::STRING:
            return std::string{json.get_c_str()};
        case element_type::BOOL:
            return json.get_bool();
        case element_type::NULL_VALUE:
            return nullptr;
        case element_type::UINT64:
            break;
    }

    return nullptr;
}

owm::misc::object_t owm::unwrapped::parse_object_(const simdjson::dom::object &obj) {
    misc::object_t result;

    for (auto [key, value] : obj) {
        result.emplace(
            std::string{key},
            unwrapped{parse_element_(value)}
        );
    }

    return result;
}

owm::misc::array_t owm::unwrapped::parse_array_(const simdjson::dom::array &arr) {
    misc::array_t result;

    for (auto v : arr) {
        result.emplace_back(parse_element_(v));
    }

    return result;
}