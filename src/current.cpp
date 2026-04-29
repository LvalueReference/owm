#include "owm/responses/current.hpp"

owm::current::current(std::string json) noexcept
    : base_response{std::move(json)}
{}