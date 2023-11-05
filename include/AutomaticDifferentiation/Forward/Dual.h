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

        Dual alias() { return Dual(this); }
    };

    template <typename Op, typename T>
    struct UnaryExpression {
        T t;
    };


    template <typename Op, typename T>
    auto operand(const UnaryExpression<Op, T>& expression) -> const T {
        return expression.t;
    }

    /* Assignment operations */

    template <typename T, typename Other>
    constexpr void assign(Dual<T>& dual, Other&& other) {
        if constexpr (IsArithmetic<Other>) {
            dual.a = other;
            dual.b = Zero<T>;
        } else if constexpr (IsDual<Other>) {
            dual.a = other.a;
            dual.b = other.b;
        } else if constexpr (IsUnaryExpression<Other>) {
            assign(dual, other.t);
            apply(UnaryOperatorType<Other> {} ,dual);
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

    // Unary expressions
    template <typename Expr>
        requires IsExpression<Expr>
    auto operator+(Expr&& expr) {
        return std::forward<Expr>(expr);
    }

    template <typename Expr>
        requires IsExpression<Expr>
    constexpr auto operator-(Expr&& expr) {
        if constexpr (IsNegativeExpression<Expr>) {
            return operand(expr);
        } else {
            return NegativeExpression<DualType<Expr>>{expr};
        }
    }

    template<typename Expr> requires IsExpression<Expr>
    constexpr auto sin(Expr&& expr) {
        return SinExpression<DualType<Expr>>{expr};
    }

    template<typename Expr> requires IsExpression<Expr>
    constexpr auto cos(Expr&& expr) {
        return CosExpression<DualType<Expr>>{expr};
    }

    template <typename T>
    constexpr void apply(NegativeOperator, Dual<T>& dual) {
        dual.a = -dual.a;
        dual.b = -dual.b;
    }

    template<typename T>
    constexpr void apply(SinOperator, Dual<T>& dual) {
        dual.b *= cos(dual.a);
        dual.a = sin(dual.a);
    }

    template<typename T>
    constexpr void apply(CosOperator, Dual<T>& dual) {
        dual.b *= -sin(dual.a);
        dual.a = cos(dual.a);
    }
}  // namespace AD::Forward
