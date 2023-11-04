#pragma once

#include <cstddef>
#include <type_traits>
#include <utility>

namespace AD::Forward {

    template <typename T>
    struct Dual;

    template<typename Op, typename T>
    struct UnaryExpression;

    namespace internal {
        template <typename T>
        struct IsDual {
            constexpr static bool value = false;
        };

        template <typename T>
        struct IsDual<Dual<T>> {
            constexpr static bool value = true;
        };

        template<typename T>
        struct IsUnaryExpression {
            constexpr static bool value = false;
        };

        template<typename Op, typename T>
        struct IsUnaryExpression<UnaryExpression<Op, T>> {
            constexpr static bool value = true;
        };
    }  // namespace internal

    template <typename T>
    using PlainType = std::remove_cv_t<std::remove_reference_t<T>>;

    template <typename T>
    constexpr auto IsArithmetic = std::is_arithmetic_v<PlainType<T>>;

    template<typename T>
    concept IsDual = internal::IsDual<PlainType<T>>::value;

    template<typename T>
    concept IsUnaryExpression = internal::IsUnaryExpression<PlainType<T>>::value;

    template<typename T>
    concept IsExpression = IsDual<T> or IsUnaryExpression<T>;

    template <typename T, typename Other>
    constexpr void assign(Dual<T>& dual, Other&& other);

    template<typename T>
    constexpr auto Zero = T(0);

    template<typename T>
    constexpr auto One = T(1);
}  // namespace AD::Forward
