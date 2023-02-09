#include "owm/responses/base_response.hpp"
#include "responses/base_response.hpp"

owm::base_response::base_response(std::string json) noexcept
    : m_json_str{std::move(json)}
{}

owm::json_handler owm::base_response::fetch() const noexcept{
    return {std::move(m_json_str)};
}