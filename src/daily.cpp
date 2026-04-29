#include "owm/responses/daily.hpp"

owm::daily::daily(std::string json) noexcept
    : base_response{std::move(json)}
{}