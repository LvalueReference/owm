#include "owm/responses/daily.hpp"

owm::daily::daily(std::string json) noexcept
    : owm::base_response{std::move(json)}
{}