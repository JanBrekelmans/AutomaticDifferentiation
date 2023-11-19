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

    template <typename Op, typename L, typename R>
    struct BinaryExpression {
        L l;
        R r;
    };

    template <typename Op, typename L, typename R>
    auto left(const BinaryExpression<Op, L, R>& expression) -> const L {
        return expression.l;
    }

    template <typename Op, typename L, typename R>
    auto right(const BinaryExpression<Op, L, R>& expression) -> const R {
        return expression.r;
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
            apply(UnaryOperatorType<Other>{}, dual);
        } else if constexpr (IsBinaryExpression<Other>) {
            if constexpr (IsAdditionExpression<Other>) {
                Dual<T> temp = left(other);
                assign(dual, right(other));

                dual.a += temp.a;
                dual.b += temp.b;
            } else if constexpr (IsMultiplicationExpression<Other>) {
                Dual<T> temp = left(other);
                assign(dual, right(other));

                const T v = dual.a;
                dual.a *= temp.a;
                dual.b = v * temp.b + dual.b * temp.a;
            } else if constexpr (IsDivisionExpression<Other>) {
                Dual<T> temp = right(other);
                assign(dual, left(other));

                const T v = dual.a;
                dual.a /= temp.a;
                dual.b = (dual.b * temp.a - v * temp.b) / (temp.a * temp.a);
            }
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

    template <typename Expr>
        requires IsExpression<Expr>
    constexpr auto sin(Expr&& expr) {
        return SinExpression<DualType<Expr>>{expr};
    }

    template <typename Expr>
        requires IsExpression<Expr>
    constexpr auto cos(Expr&& expr) {
        return CosExpression<DualType<Expr>>{expr};
    }

    template <typename Expr>
        requires IsExpression<Expr>
    constexpr auto tan(Expr&& expr) {
        return TanExpression<DualType<Expr>>{expr};
    }

    template <typename Expr>
        requires IsExpression<Expr>
    constexpr auto asin(Expr&& expr) {
        return AsinExpression<DualType<Expr>>{expr};
    }

    template <typename Expr>
        requires IsExpression<Expr>
    constexpr auto acos(Expr&& expr) {
        return AcosExpression<DualType<Expr>>{expr};
    }

    template <typename Expr>
        requires IsExpression<Expr>
    constexpr auto atan(Expr&& expr) {
        return AtanExpression<DualType<Expr>>{expr};
    }

    template <typename Expr>
        requires IsExpression<Expr>
    constexpr auto sinh(Expr&& expr) {
        return SinhExpression<DualType<Expr>>{expr};
    }

    template <typename Expr>
        requires IsExpression<Expr>
    constexpr auto cosh(Expr&& expr) {
        return CoshExpression<DualType<Expr>>{expr};
    }

    template <typename Expr>
        requires IsExpression<Expr>
    constexpr auto tanh(Expr&& expr) {
        return TanhExpression<DualType<Expr>>{expr};
    }

    template <typename Expr>
        requires IsExpression<Expr>
    constexpr auto exp(Expr&& expr) {
        return ExpExpression<DualType<Expr>>{expr};
    }

    template <typename Expr>
        requires IsExpression<Expr>
    constexpr auto log(Expr&& expr) {
        return LogExpression<DualType<Expr>>{expr};
    }

    template <typename Expr>
        requires IsExpression<Expr>
    constexpr auto sqrt(Expr&& expr) {
        return SqrtExpression<DualType<Expr>>{expr};
    }

    template <typename T>
    constexpr void apply(NegativeOperator, Dual<T>& dual) {
        dual.a = -dual.a;
        dual.b = -dual.b;
    }

    template <typename T>
    constexpr void apply(SinOperator, Dual<T>& dual) {
        dual.b *= cos(dual.a);
        dual.a = sin(dual.a);
    }

    template <typename T>
    constexpr void apply(CosOperator, Dual<T>& dual) {
        dual.b *= -sin(dual.a);
        dual.a = cos(dual.a);
    }

    template <typename T>
    constexpr void apply(TanOperator, Dual<T>& dual) {
        dual.b *= 1 / (cos(dual.a) * cos(dual.a));
        dual.a = tan(dual.a);
    }

    template <typename T>
    constexpr void apply(AsinOperator, Dual<T>& dual) {
        dual.b *= One<T> / sqrt(One<T> - dual.a * dual.a);
        dual.a = asin(dual.a);
    }

    template <typename T>
    constexpr void apply(AcosOperator, Dual<T>& dual) {
        dual.b *= -One<T> / sqrt(One<T> - dual.a * dual.a);
        dual.a = acos(dual.a);
    }

    template <typename T>
    constexpr void apply(AtanOperator, Dual<T>& dual) {
        dual.b *= One<T> / (One<T> + dual.a * dual.a);
        dual.a = atan(dual.a);
    }

    template <typename T>
    constexpr void apply(SinhOperator, Dual<T>& dual) {
        dual.b *= cosh(dual.a);
        dual.a = sinh(dual.a);
    }

    template <typename T>
    constexpr void apply(CoshOperator, Dual<T>& dual) {
        dual.b *= sinh(dual.a);
        dual.a = cosh(dual.a);
    }

    template <typename T>
    constexpr void apply(TanhOperator, Dual<T>& dual) {
        dual.b *= 1 / (cosh(dual.a) * cosh(dual.a));
        dual.a = tanh(dual.a);
    }

    template <typename T>
    constexpr void apply(ExpOperator, Dual<T>& dual) {
        dual.a = exp(dual.a);
        dual.b *= dual.a;
    }

    template <typename T>
    constexpr void apply(LogOperator, Dual<T>& dual) {
        dual.b *= One<T> / dual.a;
        dual.a = log(dual.a);
    }

    template <typename T>
    constexpr void apply(SqrtOperator, Dual<T>& dual) {
        dual.a = sqrt(dual.a);
        dual.b *= 0.5 / dual.a;
    }

    // Binary Expressions
    template <typename L, typename R>
        requires IsOperable<L, R>
    constexpr auto operator+(L&& l, R&& r) {
        if constexpr (IsArithmetic<R>) {
            return std::forward<R>(r) + std::forward<L>(l);
        } else {
            return AdditionExpression<DualType<L>, DualType<R>>{l, r};
        }
    }

    template <typename L, typename R>
        requires IsOperable<L, R>
    constexpr auto operator-(L&& l, R&& r) {
        if constexpr (IsArithmetic<R>) {
            return std::forward<R>(r) + std::forward<L>(l);
        } else {
            return std::forward<L>(l) + (-std::forward<R>(r));
        }
    }

    template <typename L, typename R>
        requires IsOperable<L, R>
    constexpr auto operator*(L&& l, R&& r) {
        if constexpr (IsArithmetic<R>) {
            return std::forward<R>(r) * std::forward<L>(l);
        } else {
            return MultiplicationExpression<DualType<L>, DualType<R>>{l, r};
        }
    }

    template <typename L, typename R>
        requires IsOperable<L, R>
    constexpr auto operator/(L&& l, R&& r) {
        if constexpr (IsArithmetic<R>) {
            return (1 / r) * std::forward<L>(l);
        } else {
            return DivisionExpression<DualType<L>, DualType<R>>{l, r};
        }
    }
}  // namespace AD::Forward
