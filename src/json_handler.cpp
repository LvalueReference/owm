#include "misc/json_handler.hpp"

owm::json_handler::json_handler(std::string json_str)
    : m_json_str{std::move(json_str)}
{
    m_json = m_parser.parse(m_json_str);
}

simdjson::dom::element owm::json_handler::operator[](std::string_view key) const{
    return m_json[key];
}