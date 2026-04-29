#include "responses/base_response.hpp"

owm::base_response::base_response(std::string json) noexcept
    : json_str_{std::move(json)}
{}

owm::unwrapped owm::base_response::fetch() const noexcept{
    return unwrapped{json_str_};
}

std::string owm::base_response::fetch_json_str() const noexcept {
    return json_str_;
}
