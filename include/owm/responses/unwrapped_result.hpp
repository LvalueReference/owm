#pragma once

#include <optional>
#include <stdexcept>

namespace owm {
    template <typename T>
    struct unwrapped_result {
        std::optional<T> value;

        operator T() && noexcept(false) {
            if (!value)
                throw std::runtime_error{"Value does not exist!"};

            return std::move(*value);
        }
    };
}