#pragma once

#include "Declarations.h"

namespace AD::Forward {

    template <typename T>
    struct Dual {
        T a{};
        T b{};

        Dual() {}

        template <typename Other>
        Dual(Other&& other) {
            assign(*this, std::forward<Other>(other));
        }

        template <typename Other>
        Dual& operator=(Other&& other) {
            Dual temp;
            assign(temp, std::forward<Other>(other));
            assign(*this, temp);
            return *this;
        }
    };


    /* Assignment operations */

    template <typename T, typename Other>
    constexpr void assign(Dual<T>& dual, Other&& other) {
        if constexpr (IsArithmetic<Other>) {
            dual.a = other;
            dual.b = Zero<T>;
        } else if constexpr (IsDual<Other>) {
            dual.a = other.a;
            dual.b = other.b;
        }
    }

    /* Seed values */

    template <typename T, typename U>
    constexpr void seed(Dual<T>& dual, U&& seedValue) {
        dual.b = static_cast<T>(seedValue);
    }

    template <typename T>
    constexpr void seed(Dual<T>& dual) {
        dual.b = One<T>;
    }

    template <typename T>
    constexpr void unseed(Dual<T>& dual) {
        dual.b = Zero<T>;
    }
}  // namespace AD::Forward
