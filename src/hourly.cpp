#include "owm/responses/hourly.hpp"

owm::hourly::hourly(std::string json) noexcept
    : base_response{std::move(json)}
{}