#include "owm/responses/current.hpp"

owm::current::current(std::string json) noexcept
    : owm::base_response{std::move(json)}
{}