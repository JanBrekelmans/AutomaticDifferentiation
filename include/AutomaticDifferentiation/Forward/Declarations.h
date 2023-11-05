#pragma once

#include <cmath>
#include <cstddef>
#include <type_traits>
#include <utility>

namespace AD::Forward {

    template <typename T>
    struct Dual;

    using dual = Dual<double>;

    template <typename Op, typename T>
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

        template <typename T>
        struct IsUnaryExpression {
            constexpr static bool value = false;
        };

        template <typename Op, typename T>
        struct IsUnaryExpression<UnaryExpression<Op, T>> {
            constexpr static bool value = true;
        };
    }  // namespace internal

    template <typename T>
    using PlainType = std::remove_cv_t<std::remove_reference_t<T>>;

    template <typename T>
    constexpr auto IsArithmetic = std::is_arithmetic_v<PlainType<T>>;

    template <typename T>
    concept IsDual = internal::IsDual<PlainType<T>>::value;

    template <typename T>
    concept IsUnaryExpression = internal::IsUnaryExpression<PlainType<T>>::value;

    template <typename T>
    concept IsExpression = IsDual<T> or IsUnaryExpression<T>;

    template <typename T>
    using DualType = std::conditional_t<IsDual<T>, T, PlainType<T>>;

    template <typename T, typename Other>
    constexpr void assign(Dual<T>& dual, Other&& other);

    template <typename Op, typename T>
    constexpr void apply(T& t);

    template <typename T>
    constexpr auto Zero = T(0);

    template <typename T>
    constexpr auto One = T(1);

    /* Unary expressions */
    using std::cos;
    using std::sin;
    using std::tan;

    using std::acos;
    using std::asin;
    using std::atan;

    using std::sinh;
    using std::cosh;
    using std::tanh;

    using std::exp;
    using std::log;

    using std::pow;
    using std::sqrt;

    // Unary operators
    struct PositiveOperator {};

    struct NegativeOperator {};

    struct SinOperator {};

    struct CosOperator {};

    struct TanOperator {};

    struct AcosOperator {};

    struct AsinOperator {};

    struct AtanOperator {};

    template <typename T>
    using PositiveExpression = UnaryExpression<PositiveOperator, T>;

    template <typename T>
    using NegativeExpression = UnaryExpression<NegativeOperator, T>;

    template <typename T>
    using SinExpression = UnaryExpression<SinOperator, T>;

    template<typename T>
    using CosExpression = UnaryExpression<CosOperator,T>;

    template<typename T>
    using TanExpression = UnaryExpression<TanOperator,T>;

    template<typename T>
    using AsinExpression = UnaryExpression<AsinOperator,T>;

    template<typename T>
    using AcosExpression = UnaryExpression<AcosOperator,T>;

    template<typename T>
    using AtanExpression = UnaryExpression<AtanOperator, T>;

    namespace internal {
        template <typename T>
        struct UnaryOperatorType {};

        template <typename Op, typename T>
        struct UnaryOperatorType<UnaryExpression<Op, T>> {
            using type = Op;
        };

        template <typename T>
        struct IsPositiveExpression {
            constexpr static bool value = false;
        };

        template <typename T>
        struct IsPositiveExpression<PositiveExpression<T>> {
            constexpr static bool value = true;
        };

        template <typename T>
        struct IsNegativeExpression {
            constexpr static bool value = false;
        };

        template <typename T>
        struct IsNegativeExpression<NegativeExpression<T>> {
            constexpr static bool value = true;
        };
    }  // namespace internal

    template <typename T>
    using UnaryOperatorType = typename internal::UnaryOperatorType<PlainType<T>>::type;

    template <typename T>
    concept IsPositiveExpression = internal::IsPositiveExpression<PlainType<T>>::value;

    template <typename T>
    concept IsNegativeExpression = internal::IsNegativeExpression<PlainType<T>>::value;

}  // namespace AD::Forward
