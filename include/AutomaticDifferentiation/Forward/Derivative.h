#pragma once

#include <array>
#include <tuple>

namespace AD::Forward {

    template <typename... Args>
    struct At {
        std::tuple<Args...> arguments;
    };

    template <typename... Args>
    auto at(Args&&... arguments) {
        return At<Args&&...>{std::forward_as_tuple(std::forward<Args>(arguments)...)};
    }

    template <typename Fun, typename... Args, typename T>
    constexpr auto derivative(const Fun& fun, const At<Args...> at, Dual<T>& wrt) {
        seed(wrt);
        Dual<T> y = std::apply(fun, at.arguments);
        unseed(wrt);
        return std::array<T, 2>{y.a, y.b};
    }
}  // namespace AD::Forward
